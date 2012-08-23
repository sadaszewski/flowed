#include "femainwindow.h"
#include "ui_femainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QVector2D>
#include <QDataStream>
#include <QProcess>
#include <QMessageBox>
#include <QPushButton>
#include <QWidgetAction>
#include <QLabel>
#include <QTimer>
#include <QColorDialog>
#include <QInputDialog>
#include <QPen>

#include <math.h>

#include "fe_element.h"
#include "fe_flowelement.h"
#include "fe_flowelementhandle.h"
// #include "fe_glwidget.h"
#include "fe_gradientelement.h"
#include "fe_beziercurve.h"

extern "C" {
#include "nn.h"
}

#include "qarrowcue.h"

void Draw_Gouraud_Triangle(QImage &image, /* int w, int h, int pitch, */
            int x0, int y0, float r0, float g0, float b0, float a0,
                  int x1, int y1, float r1, float g1, float b1, float a1,
                  int x2, int y2, float r2, float g2, float b2, float a2);

enum {
	FlowElementsTool,
	GradientElementsTool,
	FlowBrushTool,
	GradientCloningTool,
	EraserTool,
	GradientBrushTool,
    MarkPassiveTool,
    AddBezierCurveTool,
    AddBezierPointTool
};

// Custom QGraphicsItem properties
enum {
    ItemType,
    PenWidth
};

// Values for ItemType
enum {
    BezierCurve
};

FEMainWindow *FEMainWindow::m_Instance;

FEMainWindow* FEMainWindow::instance()
{
    return m_Instance;
}

FEMainWindow::FEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FEMainWindow)
{
    m_Instance = this;
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->installEventFilter(this);
    // ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    connect(ui->action_Load_image, SIGNAL(triggered()), this, SLOT(loadImage()));
    connect(ui->action_Save_flow_field, SIGNAL(triggered()), this, SLOT(saveFlowField()));
    connect(ui->action_Export_flow_map, SIGNAL(triggered()), this, SLOT(exportFlowmap()));
    connect(ui->action_Load_flow_field, SIGNAL(triggered()), this, SLOT(loadFlowField()));
    connect(ui->action_Project, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(ui->action_Flow_field, SIGNAL(triggered()), this, SLOT(newFlowFieldAndPreview()));
    connect(ui->action_Quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->action_Export_flow_map_fast, SIGNAL(triggered()), this, SLOT(exportFlowmapFast()));
    connect(ui->action_Generate_grid, SIGNAL(triggered()), this, SLOT(generateGrid()));
    connect(ui->action_Generate_gradient_grid, SIGNAL(triggered()), this, SLOT(generateGradientGrid()));
    connect(ui->gradientBrush_color, SIGNAL(clicked()), this, SLOT(selectGradientBrushColor()));

    QString ss("padding-left: 30px; font-style: italic;");
    QWidgetAction *a = new QWidgetAction(ui->menuE_xport_flow_map);
    QLabel *w = new QLabel("Quite fast and good quality, but might\nhave artifacts near sharp transitions.\nRequires at least 10 points.", ui->menuE_xport_flow_map);
    w->setStyleSheet(ss);
    a->setEnabled(false);
    a->setDefaultWidget(w);
    ui->menuE_xport_flow_map->insertAction(ui->action_Export_flow_map, a);
    a = new QWidgetAction(ui->menuE_xport_flow_map);
    w = new QLabel("Very fast, but quality can be an issue.", ui->menuE_xport_flow_map);
    w->setStyleSheet(ss);
    a->setEnabled(false);
    a->setDefaultWidget(w);
    ui->menuE_xport_flow_map->insertAction(ui->actionExport_flow_map_AKIMA, a);
    a = new QWidgetAction(ui->menuE_xport_flow_map);
    w = new QLabel("Recommended for final output.\nBest quality, but slow.", ui->menuE_xport_flow_map);
    w->setStyleSheet(ss);
    a->setEnabled(false);
    a->setDefaultWidget(w);
    ui->menuE_xport_flow_map->addAction(a);

    // scene->addRect(0, 0, 100, 100, QPen(Qt::black), Qt::red);

    image = new QGraphicsPixmapItem(0);
    scene->addItem(image);
    image->setZValue(-2);
    // image->setOffset();

    // glwidget = new FE_GLWidget(0);
    // glwidget->setVisible(true);
    // glwidget->setGeometry(0, 0, 800, 600);

    previewBtn = ui->previewBtn;
    ui->fileBtn->setMenu(ui->menu_File);
    ui->menuBar->setVisible(false);

    connect(previewBtn, SIGNAL(toggled(bool)), this, SLOT(bigPreview(bool)));
    connect(ui->expAndSwitchBtn, SIGNAL(clicked()), this, SLOT(expAndSwitch()));
    connect(ui->actionExport_flow_map_AKIMA, SIGNAL(triggered()), this, SLOT(exportFlowmapAkima()));

    lastColor = Qt::gray;
    lastWaveSize = 0;

    m_GradientBrushColor = Qt::gray;

    m_ArrowCue = 0;
}

FEMainWindow::~FEMainWindow()
{
    delete ui;
}

void FEMainWindow::loadImage()
{
	QString fname = QFileDialog::getOpenFileName(this, "Select image", QString(), "Images (*.png *.jpg)");
	if (!fname.isEmpty()) {
		image->setPixmap(QPixmap(fname));
		QFileInfo fi(fname);
		QString autoFFName(fi.absolutePath() + "/" + fi.baseName() + ".ff");
		if (QFile(autoFFName).exists())
			loadFlowField(autoFFName);
	}
}

void FEMainWindow::saveFlowField()
{
	QString fname = QFileDialog::getSaveFileName(this, "Save flow field", QString(), "Flow field (*.ff)");
	if (!fname.isEmpty()) {
		QFile f(fname);
		f.open(QFile::WriteOnly);
		QDataStream ds(&f);
        int version = 3;
        ds << version;
		QList<FE_FlowElement*> flowElements = scene->findChildren<FE_FlowElement*>();
		ds << flowElements.size();
		foreach (FE_FlowElement *fe, flowElements) {
			ds << fe->from();
			ds << fe->to();
			ds << fe->passive();
		}
		QList<QGraphicsItem*> gradientElements = scene->items();
		for (QMutableListIterator<QGraphicsItem*> it(gradientElements); it.hasNext();) {
			if (it.next()->type() != FE_GradientElement::Type)
				it.remove();
		}
		ds << gradientElements.size();
		foreach (QGraphicsItem *item, gradientElements) {
			ds << item->pos();
			ds << ((FE_GradientElement*) item)->color();
			ds << ((FE_GradientElement*) item)->passive();
		}
        QList<FE_BezierCurve*> bcs(bezierCurves());
        ds << bcs.size();
        foreach(FE_BezierCurve *bc, bcs) {
            bc->save(ds);
        }
	}
}

void FEMainWindow::exportFlowmap()
{
	QString fname = QFileDialog::getSaveFileName(this, "Save flowmap", QString(), "Images (*.png *.jpg)");
	if (!fname.isEmpty()) {
        QImage im(renderFinalImage(&FEMainWindow::nnGenerateFlowMap, false));
		im.save(fname);
		exportFName = QString("%1;1").arg(fname);
	}
}

void FEMainWindow::loadFlowField()
{
	QString fname = QFileDialog::getOpenFileName(this, "Load flow field", QString(), "Flow field (*.ff)");
	if (!fname.isEmpty())
		loadFlowField(fname);
}

void FEMainWindow::loadFlowField(const QString& fname)
{
	newFlowField();

	QFile f(fname);
	f.open(QFile::ReadOnly);
	QDataStream ds(&f);
    int version;
    ds >> version;
	int flowElementsCount;
	ds >> flowElementsCount;
	for (int i = 0; i < flowElementsCount; i++) {
		QPointF from;
		QPointF to;
		bool passive;
		ds >> from;
		ds >> to;
        ds >> passive;
		FE_FlowElement *elem = new FE_FlowElement(scene);
		elem->getHandleFrom()->setPos(from);
		elem->getHandleTo()->setPos(to);
		elem->onEndPositionChanged();
        elem->setPassive(passive);
	}
	int gradientElementsCount;
	ds >> gradientElementsCount;
	for (int i = 0; i < gradientElementsCount; i++) {
		QPointF pos;
		QColor color;
		bool passive;
		ds >> pos;
		ds >> color;
        ds >> passive;
		FE_GradientElement *elem = new FE_GradientElement();
		scene->addItem(elem);
		elem->setPos(pos);
		elem->setColor(color);
        elem->setPassive(passive);
	}
    int bezierCurvesCount;
    ds >> bezierCurvesCount;
    for (int i = 0; i < bezierCurvesCount; i++) {
        FE_BezierCurve *bc = new FE_BezierCurve(QPointF(0, 0), scene);
        bc->load(ds);
    }

	generatePreview();
}

extern "C" {

/* .. Scalar Arguments ..
      INTEGER          IER,MD,NDP,NXI,NYI,NEAR(NDP),NEXT(NDP)
*     ..
*     .. Array Arguments ..
      DOUBLE PRECISION             WK(NDP,17),XD(NDP),XI(NXI),YD(NDP),
     +                 YI(NYI),ZD(NDP),ZI(NXI,NYI),DIST(NDP)
	INTEGER          IWK(NDP,25)
	LOGICAL          EXTRPI(NXI,NYI) */

void sdsf3p_(int *MD, int *NDP, double *XD, double *YD, double *ZD, int *NXI,
	     double *XI, int *NYI, double *YI, double *ZI, int *IER, double *WK,
	     int *IWK, int *EXTRPI, int *NEAR_, int *NEXT, double *DIST);

}

QImage FEMainWindow::akimaGenerateFlowMap()
{
	QVector<FE_Element*> elems(this->elems());
	if (elems.size() < 10) {
		QMessageBox::warning(this, "AKIMA", "AKIMA Cubic Interpolation requires at least 10 points");
		return QImage();
	}
	int MD = 1;
	int NDP = elems.size();
	double *XD = new double[NDP];
	double *YD = new double[NDP];
	double *ZD1 = new double[NDP];
	double *ZD2 = new double[NDP];
	double *ZD3 = new double[NDP];
    double *ZD4 = new double[NDP];
	int NXI = image->pixmap().width();
	double *XI = new double[NXI];
	int NYI = image->pixmap().height();
	double *YI = new double[NYI];
	double *ZI1 = new double[NXI*NYI]; // final output X
	double *ZI2 = new double[NXI*NYI]; // final output Y
	double *ZI3 = new double[NXI*NYI]; // final output Z
    double *ZI4 = new double[NXI*NYI]; // final output A
	int IER;
	double *WK = new double[NDP * 17];
	int *IWK = new int[NDP * 25];
	int *EXTRPI = new int[NXI*NYI];
	int *NEAR_ = new int[NDP];
	int *NEXT = new int[NDP];
	double *DIST = new double[NDP];

//	memset(WK, 0, NDP * 17 * sizeof(double));
//	memset(IWK, 0, NDP * 25 * sizeof(int));
//	memset(EXTRPI, 0, NXI*NYI*sizeof(int));
//	memset(NEAR_, 0, NDP * sizeof(int));
//	memset(NEXT, 0, NDP * sizeof(int));
//	memset(DIST, 0, NDP * sizeof(double));

	for (int i = 0; i < NXI; i++)
		XI[i] = i;
	for (int i = 0; i < NYI; i++)
		YI[i] = i;

	for(int i = 0; i < NDP; i++) {
		XD[i] = elems[i]->pos().x();
		YD[i] = elems[i]->pos().y();
		QColor color(elems[i]->color());
		ZD1[i] = color.red();
		ZD2[i] = color.green();
		ZD3[i] = color.blue();
        ZD4[i] = color.alpha();
	}

	sdsf3p_(&MD, &NDP, XD, YD, ZD1, &NXI, XI, &NYI, YI, ZI1, &IER, WK, IWK, EXTRPI, NEAR_, NEXT, DIST);

//	memset(WK, 0, NDP * 17 * sizeof(double));
//	memset(IWK, 0, NDP * 25 * sizeof(int));
//	memset(EXTRPI, 0, NXI*NYI*sizeof(int));
//	memset(NEAR_, 0, NDP * sizeof(int));
//	memset(NEXT, 0, NDP * sizeof(int));
//	memset(DIST, 0, NDP * sizeof(double));

	sdsf3p_(&MD, &NDP, XD, YD, ZD2, &NXI, XI, &NYI, YI, ZI2, &IER, WK, IWK, EXTRPI, NEAR_, NEXT, DIST);

//	memset(WK, 0, NDP * 17 * sizeof(double));
//	memset(IWK, 0, NDP * 25 * sizeof(int));
//	memset(EXTRPI, 0, NXI*NYI*sizeof(int));
//	memset(NEAR_, 0, NDP * sizeof(int));
//	memset(NEXT, 0, NDP * sizeof(int));
//	memset(DIST, 0, NDP * sizeof(double));

	sdsf3p_(&MD, &NDP, XD, YD, ZD3, &NXI, XI, &NYI, YI, ZI3, &IER, WK, IWK, EXTRPI, NEAR_, NEXT, DIST);

    sdsf3p_(&MD, &NDP, XD, YD, ZD4, &NXI, XI, &NYI, YI, ZI4, &IER, WK, IWK, EXTRPI, NEAR_, NEXT, DIST);

	QImage im(NXI, NYI, QImage::Format_ARGB32);
    im.fill(0x00000000);
	uchar *data = im.bits();
	for (int x = 0; x < NXI; x++)
		for (int y = 0; y < NYI; y++) {
			int ofs1 = (y * NXI + x) * 4;
			int ofs2 = y * NXI + x;

			double red = qMin(qMax(ZI1[ofs2], 0.0), 255.0);
			double green = qMin(qMax(ZI2[ofs2], 0.0), 255.0);
			double blue = qMin(qMax(ZI3[ofs2], 0.0), 255.0);
            double alpha = qMin(qMax(ZI4[ofs2], 0.0), 255.0);
			// double l = sqrt(x*x+y*y);
			// x /= l;
			// y /= l;

            data[ofs1 + 3] = alpha;
			data[ofs1 + 2] = red;
			data[ofs1 + 1] = green;
			data[ofs1 + 0] = blue;
		}

	delete [] XD;
	delete [] YD;
	delete [] ZD1;
	delete [] ZD2;
	delete [] ZD3;
    delete [] ZD4;
	delete [] XI;
	delete [] YI;
	delete [] ZI1;
	delete [] ZI2;
	delete [] ZI3;
    delete [] ZI4;
	delete [] WK;
	delete [] IWK;
	delete [] EXTRPI;
	delete [] NEAR_;
	delete [] NEXT;
	delete [] DIST;

	return im;
}

QImage FEMainWindow::nnGenerateFlowMap()
{
	QVector<FE_Element*> elems(this->elems());
	point *points = new point[elems.size()];
	point *p = points;
	double *zin = new double[elems.size()];
	foreach (FE_Element *elem, elems) {
		p->x = elem->pos().x();
		p->y = elem->pos().y();
		p->z = 0;
		p++;
	}
	delaunay *d = delaunay_build(elems.size(), points, 0, 0, 0, 0);
	int w = image->pixmap().width();
	int h = image->pixmap().height();
	int N = w * h;
	double *x = new double[N];
	double *y = new double[N];
	double *red = new double[N];
	double *green = new double[N];
	double *blue = new double[N];
    double *alpha = new double[N];
	for (int yy = 0; yy < h; yy++) {
		for (int xx = 0; xx < w; xx++) {
			x[yy*w+xx] = xx;
			y[yy*w+xx] = yy;
		}
	}

	// nn_rule = NON_SIBSONIAN;
	nnai *nn = nnai_build(d, N, x, y);
	nnai_setwmin(nn, -INFINITY);

	// red
	for (int i = 0; i < elems.size(); i++) {
		zin[i] = elems[i]->color().red();
	}
	nnai_interpolate(nn, zin, red);

	// green
	for (int i = 0; i < elems.size(); i++) {
		zin[i] = elems[i]->color().green();
	}
	nnai_interpolate(nn, zin, green);

	// blue
	for (int i = 0; i < elems.size(); i++) {
		zin[i] = elems[i]->color().blue();
	}
	nnai_interpolate(nn, zin, blue);

    // alpha
    for (int i = 0; i < elems.size(); i++) {
        zin[i] = elems[i]->color().alpha();
    }
    nnai_interpolate(nn, zin, alpha);

#define CLAMP(v) ((v) < 0 ? 0 : ((v) > 255 ? 255 : (v)))

    QColor cc(0, 0, 0, 0);

	QImage im(w, h, QImage::Format_ARGB32);
    im.fill(0x00000000);
	for (int yy = 0; yy < h; yy++) {
		for (int xx = 0; xx < w; xx++) {
			double r = red[yy*w + xx];
			double g = green[yy*w + xx];
            double b = blue[yy*w + xx];
            double a = alpha[yy*w + xx];
			if (1){//isfinite(r) && isfinite(g) && isfinite(b)) {
                QColor c(CLAMP(r), CLAMP(g), CLAMP(b), CLAMP(a));
                im.setPixel(xx, yy, c.rgba());
				cc = c;
			} else {
                im.setPixel(xx, yy, cc.rgba());
			}
		}
	}

	delete[] points;
	delete[] zin;
	delete[] x;
	delete[] y;
	delete[] red;
	delete[] green;
	delete[] blue;
    delete[] alpha;

	nnai_destroy(nn);
	delaunay_destroy(d);

	return im;
}

void FEMainWindow::newProject()
{
	image->setPixmap(QPixmap());
	newFlowFieldAndPreview();
}

void FEMainWindow::newFlowField()
{
	foreach(FE_FlowElement *fe, scene->findChildren<FE_FlowElement*>()) {
		fe->removeFromScene();
		delete fe;
	}
	foreach(QGraphicsItem *item, scene->items()) {
        if (item->type() == FE_GradientElement::Type || item->type() == FE_BezierCurve::Type)
			delete item;
	}
}

void FEMainWindow::newFlowFieldAndPreview()
{
	newFlowField();
	generatePreview();
}

void FEMainWindow::exportFlowmapFast()
{
	QString fname = QFileDialog::getSaveFileName(this, "Save flowmap", QString(), "Images (*.png *.jpg)");
	if (!fname.isEmpty()) {
        QImage im(renderFinalImage(&FEMainWindow::fastGenerateFlowMap, false));
		im.save(fname);
		exportFName = QString("%1;2").arg(fname);
	}
}

void FEMainWindow::bigPreview(bool b)
{
	if (b) {
		origPixmap = image->pixmap();
        image->setPixmap(QPixmap::fromImage(renderFinalImage(&FEMainWindow::fastGenerateFlowMap)));
	} else {
		image->setPixmap(origPixmap);
	}
}

void FEMainWindow::expAndSwitch()
{
	QImage im;
	if (exportFName.isEmpty()) {
		QMessageBox::warning(this, "Repeat Last Export", "You haven't exported the flowmap yet!");
		return;
	}
	QChar c = exportFName[exportFName.length()-1];
	if (c == '1')
		im = generateFlowMap();
	else if (c == '2')
        im = fastGenerateFlowMap();
	else
		im = akimaGenerateFlowMap();
	im.save(exportFName.left(exportFName.length()-2));
}

void FEMainWindow::exportFlowmapAkima()
{
	QString fname = QFileDialog::getSaveFileName(this, "Save flowmap", QString(), "Images (*.png *.jpg)");
	if (!fname.isEmpty()) {
        QImage im(renderFinalImage(&FEMainWindow::akimaGenerateFlowMap, false));
		im.save(fname);
		exportFName = QString("%1;3").arg(fname);
	}
}

void FEMainWindow::generateGrid()
{
	bool ok;
	int nCols = QInputDialog::getInt(this, "Number of columns", "Columns", 10, 1, 1000, 1, &ok);
	if (!ok)
		return;
	int nRows = QInputDialog::getInt(this, "Number of rows", "Rows", 5, 1, 1000, 1, &ok);
	if (!ok)
		return;
	int dirX = QInputDialog::getInt(this, "Horizontal direction", "Horizontal direction", 100, -100, 100, 1, &ok);
	if (!ok)
		return;
	int dirY = QInputDialog::getInt(this, "Vertical direction", "Vertical direction", 100, -100, 100, 1, &ok);
	if (!ok)
		return;
	int waveSize = QInputDialog::getInt(this, "Wave size", "Wave size", 0, 0, 255, 1, &ok);
	if (!ok)
		return;

	float stepX = (float) image->pixmap().width() / nCols;
	float stepY = (float) image->pixmap().height() / nRows;
	float dx = dirX * 2 * FE_FlowElement::maxRadius() / 100.0f;
	float dy = dirY * 2 * FE_FlowElement::maxRadius() / 100.0f;

	for (int x = 0; x <= nCols; x++) {
		for (int y = 0; y <= nRows; y++) {
			FE_FlowElement *elem = new FE_FlowElement(scene);
			elem->setFrom(QPointF(x * stepX, y * stepY));
			elem->setTo(elem->from() + QPointF(dx, dy));
			elem->setWaveSize(waveSize);
		}
	}
}

void FEMainWindow::generateGradientGrid()
{
	bool ok;
	int nCols = QInputDialog::getInt(this, "Number of columns", "Columns", 10, 1, 1000, 1, &ok);
	if (!ok)
		return;
	int nRows = QInputDialog::getInt(this, "Number of rows", "Rows", 5, 1, 1000, 1, &ok);
	if (!ok)
		return;
    QColor c = QColorDialog::getColor(Qt::gray, this, "Color", QColorDialog::ShowAlphaChannel);
	if (!c.isValid())
		return;

	float stepX = (float) image->pixmap().width() / nCols;
	float stepY = (float) image->pixmap().height() / nRows;

	for (int x = 0; x <= nCols; x++) {
		for (int y = 0; y <= nRows; y++) {
			FE_GradientElement *elem = new FE_GradientElement();
			elem->setPos(QPointF(x * stepX, y * stepY));
			elem->setColor(c);
			scene->addItem(elem);
		}
	}
}

void FEMainWindow::selectGradientBrushColor()
{
    QColor c = QColorDialog::getColor(m_GradientBrushColor, this, "Color", QColorDialog::ShowAlphaChannel);
	if (c.isValid()) {
		m_GradientBrushColor = c;
		ui->gradientBrush_color->setStyleSheet(QString("background-color: #%1%2%3").arg(c.red(), 2, 16, QChar('0')).arg(c.green(), 2, 16, QChar('0')).arg(c.blue(), 2, 16, QChar('0')));
	}
}

bool FEMainWindow::eventFilter(QObject *o, QEvent *e)
{
	if (e->type() == QEvent::GraphicsSceneMousePress) {
		QGraphicsSceneMouseEvent *ge = (QGraphicsSceneMouseEvent*) e;
		QGraphicsItem *item = scene->itemAt(ge->scenePos());

		if (ui->tools_dockWidget->isFloating())
			ui->tools_dockWidget->hide();

		if (ge->button() == Qt::LeftButton) {
			if (ui->tool_comboBox->currentIndex() == GradientCloningTool && item && item->type() == FE_GradientElement::Type) {

				FE_GradientElement *elem = (FE_GradientElement*) item;

				QColor c(elem->color());
				int r, g, b;
				if (ui->gradClone_change_comboBox->currentIndex() == 0) { // absolute
					r = g = b = 0;
				} else {
					r = c.red();
					g = c.green();
					b = c.blue();
				}
				r += ui->gradClone_red_spinBox->value();
				g += ui->gradClone_green_spinBox->value();
				b += ui->gradClone_blue_spinBox->value();

				c.setRgb(qMin(qMax(r, 0), 255), qMin(qMax(g, 0), 255), qMin(qMax(b, 0), 255), 255);

				if (ui->gradientAdjust_clone->isChecked()) {
					FE_GradientElement *clone = new FE_GradientElement();
					scene->addItem(clone);
					clone->setPos(elem->pos());
					clone->setColor(c);

					m_ArrowCue = new QArrowCue();
				} else {
					elem->setColor(c);
					return true;
				}

			} else if (item == 0 || (item->flags() & QGraphicsItem::ItemIsMovable) == 0) {

				switch(ui->tool_comboBox->currentIndex()) {
				case FlowElementsTool: {
						FE_FlowElement *elem = new FE_FlowElement(scene);
						elem->setWaveSize(lastWaveSize);
						elem->getHandleFrom()->setPos(ge->scenePos());
						elem->getHandleTo()->setPos(ge->scenePos());
						elem->getHandleFrom()->setPos(ge->scenePos());
						elem->getHandleTo()->setPos(ge->scenePos());
						// elem->getHandleTo()->mousePressEvent(ge);
						elem->onEndPositionChanged();
						// generatePreview();
					}
					break;

				case GradientElementsTool: {
						FE_GradientElement *elem = new FE_GradientElement();
						scene->addItem(elem);
						elem->setPos(ge->scenePos());
						elem->setPos(ge->scenePos());
						elem->setColor(lastColor);
					}
					break;

				case FlowBrushTool:
					foreach(FE_FlowElement *elem, scene->findChildren<FE_FlowElement*>()) {
						elem->setBrushed(false);
					}
					return true;

				case GradientBrushTool:
					return true;

                case AddBezierCurveTool: {
                        new FE_BezierCurve(ge->scenePos(), scene);
                    }
                    return true;

                case AddBezierPointTool: {
                        if (FE_BezierCurve::lastCurve()) {
                            FE_BezierCurve::lastCurve()->addPoint(ge->scenePos());
                        }
                    }
                    return true;
				}
            } else if (ge->button() == Qt::LeftButton && tool() != FlowElementsTool && tool() != GradientElementsTool && tool() != AddBezierCurveTool && tool() != AddBezierPointTool)  {
				return true;
			}
		} else if (ge->button() == Qt::MidButton && item) {
			if (item->type() == FE_GradientElement::Type) {
				FE_GradientElement *elem = (FE_GradientElement*) item;
                QColor color = QColorDialog::getColor(elem->color(), this, "Color", QColorDialog::ShowAlphaChannel);
				if (color.isValid()) {
					elem->setColor(lastColor = color);
					generatePreview();
				}
				return true;
			} else if (item->type() == FE_FlowElementHandle::Type) {
				FE_FlowElement *elem = ((FE_FlowElement*) ((FE_FlowElementHandle*)item)->flowElement());
				bool ok;
				int s = QInputDialog::getInt(this, "Enter wave size (0-255)", "Wave size", elem->waveSize(), 0, 255, 1, &ok);
				if (ok) {
					lastWaveSize = s;
					elem->setWaveSize(s);
					generatePreview();
				}
				return true;
			}
		} else if (ge->button() == Qt::RightButton && item != 0) {
			if (item->type() == FE_FlowElementHandle::Type) {
				FE_FlowElement *fe = ((FE_FlowElementHandle*) item)->flowElement();

				if (ge->modifiers() & Qt::ShiftModifier) {
					fe->setPassive(!fe->passive());
				} else {
					fe->removeFromScene();
					delete fe;
					// generatePreview();
				}

				return true;
			} else if (item->type() == FE_GradientElement::Type) {
				if (ge->modifiers() & Qt::ShiftModifier) {
					((FE_GradientElement*) item)->setPassive(!((FE_GradientElement*) item)->passive());
				} else {
					delete item;
				}
				return true;
			}
		}

		if (ge->button() == Qt::RightButton && (item == 0 || (item->flags() & QGraphicsItem::ItemIsMovable) == 0)) {
			ui->tools_dockWidget->setFloating(true);
			ui->tools_dockWidget->setGeometry(QRect(ge->screenPos(), ui->tools_dockWidget->minimumSize()));
			ui->tools_dockWidget->setVisible(true);
			return true;
		}
	} else if (e->type() == QEvent::GraphicsSceneMouseRelease) {
		delete m_ArrowCue;
		m_ArrowCue = 0;

        /* foreach (QGraphicsItem *item, scene->items()) {
            if (item->data(ItemType) == BezierCurve) {
                QVector<QGraphicsItem*> elem(item->children().toVector());
                QPainterPath path;
                path.moveTo(elem[0]->scenePos());
                path.cubicTo(elem[1]->scenePos(), elem[2]->scenePos(), elem[3]->scenePos());
                ((QGraphicsPathItem*) item)->setPath(path);
            }
        } */

        if (ui->autoGeneratePreview->isChecked()) {
            generatePreview();
        }
	} else if (e->type() == QEvent::GraphicsSceneMouseMove) {
		QGraphicsSceneMouseEvent *ge = (QGraphicsSceneMouseEvent*) e;

		if (ui->tool_comboBox->currentIndex() == FlowBrushTool && (ge->buttons() & Qt::LeftButton)) {

			float angle = (ui->flowBrush_dial->value() - 90) * M_PI / 180.0f;

			float dx = cos(angle);
			float dy = -sin(angle);

			float magn = ui->flowBrush_magnitude->value() * 2 * FE_FlowElement::maxRadius() / 100.0f;
			dx *= magn;
			dy *= magn;

			float str = ui->flowBrush_strength->value() / 100.0f;

			int siz = ui->flowBrush_size->value();

			QTime now(QTime::currentTime());

			foreach(FE_FlowElement *elem, scene->findChildren<FE_FlowElement*>()) {
				if (QVector2D(elem->pos() - ge->scenePos()).length() < siz) {
					if (elem->brushedTime().msecsTo(now) > 100) {
						QPointF from = elem->getHandleFrom()->pos();
						QPointF dir = elem->dir();

						elem->getHandleTo()->setPos(from.x() + dx * str + dir.x() * (1 - str), from.y() + dy * str + dir.y() * (1 - str));
						elem->setBrushedTime(now);
					}
				} else {
					elem->setBrushed(false);
				}
			}
		} else if (ui->tool_comboBox->currentIndex() == EraserTool && (ge->buttons() & Qt::LeftButton)) {
			int siz = ui->eraser_size->value();

			foreach(FE_Element *elem, elems()) {
				if (QVector2D(elem->pos() - ge->scenePos()).length() < siz) {
					if (dynamic_cast<FE_FlowElement*>(elem)) {
						((FE_FlowElement*) elem)->removeFromScene();
					} else {
						scene->removeItem(dynamic_cast<QGraphicsItem*>(elem));
					}
					delete elem;
				}
			}

			scene->update();
		} else if (ui->tool_comboBox->currentIndex() == GradientBrushTool && (ge->buttons() & Qt::LeftButton)) {
			int siz = ui->gradientBrush_size->value();

			foreach(FE_Element *elem, elems()) {
				if (QVector2D(elem->pos() - ge->scenePos()).length() < siz) {
					if (dynamic_cast<FE_GradientElement*>(elem)) {
						((FE_GradientElement*) elem)->setColor(m_GradientBrushColor);
					}
				}
			}
		} else if (tool() == MarkPassiveTool && (ge->buttons() & Qt::LeftButton)) {
			int siz = ui->markPassive_size->value();
			int mode = ui->markPassive_mode->currentIndex();

			foreach(FE_Element *elem, elems()) {
				if (QVector2D(elem->pos() - ge->scenePos()).length() < siz) {
					elem->setPassive(mode == 0 ? true : (mode == 1 ? false : !elem->passive()));
				}
			}
		}
	}
	return QObject::eventFilter(o, e);
}

bool FEMainWindow::event(QEvent *e)
{
	/* if (e->type() == QEvent::LayoutRequest) {
		bool b = QMainWindow::event(e);
		previewBtn->setGeometry(QRect(15, 15, 120, 85));
		return b;
	} */
	return QMainWindow::event(e);
}

int FEMainWindow::tool()
{
	return ui->tool_comboBox->currentIndex();
}

QImage FEMainWindow::generateFlowMap()
{
	QSize s(image->pixmap().size());
	int w = s.width();
	int h = s.height();

	double *A = new double[w * h * 4];
	for (int i = 0; i < w*h*4; i++)
		A[i]=-1;

	// Voronoi tesselation
	QVector<FE_Element*> elems;
	foreach(FE_FlowElement *elem, scene->findChildren<FE_FlowElement*>()) {
		elems.push_back(elem);
	}
	foreach(QGraphicsItem *item, scene->items()) {
		if (item->type() == FE_GradientElement::Type)
			elems.push_back((FE_GradientElement*) item);
	}

	#pragma omp parallel for
	for (int i = 0; i < elems.size(); i++)
	{
		QPointF pos(elems[i]->pos());
		QColor color(elems[i]->color());

		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++) {
				int ofs = (y * w + x) * 4;
				qreal l = QVector2D(pos - QPointF(x, y)).lengthSquared();
				if (l < A[ofs] || A[ofs] == -1) {
					A[ofs] = l;
					A[ofs + 1] = color.red();
					A[ofs + 2] = color.green();
					A[ofs + 3] = color.blue();
				}
			}
	}

	double *B = new double[w * h * 3];

	// Natural neighbor
	#pragma omp parallel for
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			int r = 0;
			int count = 0;
			qreal red = 0;
			qreal green = 0;
			qreal blue = 0;
			while(true) {
				int count1 = count;
				for (int x1 = qMax(0, x - r); x1 <= qMin(w-1, x + r); x1++) {
					qreal l = (x1-x)*(x1-x) + r*r;
					int ofs1 = (qMax(0, y - r) * w + x1) * 4;
					Q_ASSERT(ofs1 < w*h*4);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						red += A[ofs1+1];
						green += A[ofs1+2];
						blue += A[ofs1+3];
						count++;
					}
					ofs1 = (qMin(h-1, y + r) * w + x1) * 4;
					Q_ASSERT(ofs1 < w*h*4);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						red += A[ofs1+1];
						green += A[ofs1+2];
						blue += A[ofs1+3];
						count++;
					}
				}
				for (int y1 = qMax(0, y - r); y1 <= qMin(h-1, y + r); y1++) {
					qreal l = (y1-y)*(y1-y) + r*r;
					int ofs1 = (y1 * w + qMax(0, x - r)) * 4;
					Q_ASSERT(ofs1 < w*h*4);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						red += A[ofs1+1];
						green += A[ofs1+2];
						blue += A[ofs1+3];
						count++;
					}
					ofs1 = (y1 * w + qMin(w-1, x + r)) * 4;
					Q_ASSERT(ofs1 < w*h*4);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						red += A[ofs1+1];
						green += A[ofs1+2];
						blue += A[ofs1+3];
						count++;
					}
				}
				if (count1 == count)
					break;
				r++;
			}
			int ofs = (y * w + x) * 3;
			B[ofs] = red / count;
			B[ofs+1] = green / count;
			B[ofs+2] = blue / count;
		}

	/* qreal max = 0;
	for (int i = 0; i < w * h * 2; i += 2) {
		qreal t = B[i]*B[i]+B[i+1]*B[i+1];
		if (t > max)
			max = t;
	}
	max = sqrt(max); */

	QImage im(s, QImage::Format_ARGB32);
	uchar *bits = im.bits();

	for (int i = 0; i < w * h; i++) {
		// A[i] /= max;
		bits[i * 4 + 3] = 255;
		bits[i * 4 + 2] = B[i * 3];
		bits[i * 4 + 1] = B[i * 3 + 1];
		bits[i * 4] = B[i * 3 + 2];
	}


	delete [] A;
	delete [] B;

	return im;
}

QImage FEMainWindow::fastGenerateFlowMap()
{
	QVector<FE_Element*> elems(this->elems());
	QProcess p;
	p.start("qdelaunay", QStringList("Fv") << "Qt");
	if (!p.waitForStarted()) {
		QMessageBox::warning(this, "qdelaunay failed", "Failed to start qdelaunay");
        return QImage();
	}
	p.write(QString("2 rbox %1 D2\r\n").arg(elems.size()).toAscii());
	p.write(QString("%1\r\n").arg(elems.size()).toAscii());
	foreach (FE_Element *e, elems) {
		p.write(QString("%1 %2\r\n").arg(e->pos().x()).arg(e->pos().y()).toAscii());
		p.waitForBytesWritten();
	}
	p.closeWriteChannel();
	/* if (!p.waitForReadyRead()) {
		QMessageBox::warning(this, "qdelaunay failed", "Timeout reached waiting for output");
		return QImage();
	} */
	if (!p.waitForFinished()) {
		QMessageBox::warning(this, "qdelaunay failed", "Timeout reached waiting for finish.");
        return QImage();
	}
	QByteArray ba(p.readAllStandardOutput());
	QStringList l(QString(ba).remove("\r").split("\n"));
	QVector<QVector<int> > indices;
	for (int i = 1; i < l.size() - 1; i++) {
		QStringList ind(l[i].split(" "));
		QVector<int> v;
		v << ind[1].toInt();
		v << ind[2].toInt();
		v << ind[3].toInt();
		indices.push_back(v);
	}

    QImage im(image->pixmap().width(), image->pixmap().height(), QImage::Format_ARGB32);
    im.fill(0x00000000);

	foreach (QVector<int> I, indices) {

		FE_Element *e0(elems[I[0]]);
		FE_Element *e1(elems[I[1]]);
		FE_Element *e2(elems[I[2]]);
		// glColor3ub(e1->color().red(), e1->color().green(), e1->color().blue());
		// glVertex3f(e1->pos().x(), e1->pos().y(), 0);

		QColor c0(e0->color());
		QColor c1(e1->color());
		QColor c2(e2->color());

		if (e0->passive()) c0 = (e1->passive() ? c2 : c1);
		if (e1->passive()) c1 = (e0->passive() ? c2 : c0);
		if (e2->passive()) c2 = (e0->passive() ? c1 : c0);

        Draw_Gouraud_Triangle(im, e0->pos().x(), e0->pos().y(), c0.red(), c0.green(), c0.blue(), c0.alpha(),
                      e1->pos().x(), e1->pos().y(), c1.red(), c1.green(), c1.blue(), c1.alpha(),
                      e2->pos().x(), e2->pos().y(), c2.red(), c2.green(), c2.blue(), c2.alpha());
	}

    return im; // QPixmap::fromImage(im);


	/* glwidget->setElems(elems);
	glwidget->setIndices(indices);
	// glwidget->swapBuffers();


	glwidget->setWindowFlags(glwidget->windowFlags() | Qt::WindowStaysOnTopHint);
	glwidget->setGeometry(2000, 2000, image->pixmap().width(), image->pixmap().height());
	glwidget->setVisible(true);
	// QPixmap ret = glwidget->renderPixmap(image->pixmap().width(), image->pixmap().height());

	QEventLoop loop;
	QTimer t;
	connect(&t, SIGNAL(timeout()), &loop, SLOT(quit()));
	t.setInterval(10);
	t.start();
	loop.exec(QEventLoop::ExcludeUserInputEvents);
	// glwidget->updateGL();
	// sleep()
	QPixmap ret = QPixmap::fromImage(glwidget->grabFrameBuffer());

	glwidget->setVisible(false);
	return ret; */
}

void FEMainWindow::generatePreview()
{
    QPixmap fm(QPixmap::fromImage(renderFinalImage(&FEMainWindow::fastGenerateFlowMap)));
	previewBtn->setIconSize(QSize(100, 75));
	previewBtn->setIcon(QIcon(fm));
	if (previewBtn->isChecked())
		image->setPixmap(fm);
}

QVector<FE_Element*> FEMainWindow::elems()
{
	QVector<FE_Element*> elems;
	foreach(FE_FlowElement *elem, scene->findChildren<FE_FlowElement*>()) {
		elems.push_back(elem);
	}
	foreach(QGraphicsItem *item, scene->items()) {
		if (item->type() == FE_GradientElement::Type)
			elems.push_back((FE_GradientElement*) item);
	}

	return elems;
}

QImage FEMainWindow::renderBezierCurves()
{
    QImage im(image->pixmap().size(), QImage::Format_ARGB32);
    im.fill(0x00000000);
    QPainter p(&im);
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->type() == FE_BezierCurve::Type) {
            ((FE_BezierCurve*) item)->render(&p);
        }
    }
    return im;
}

QImage FEMainWindow::renderFinalImage(QImage(FEMainWindow::*flowFieldMethod)(), bool useCheckerBoard)
{
    if (image->pixmap().isNull())
        return QImage();

    QImage im;
    if (useCheckerBoard) {
        im = checkerBoard();
    } else {
        im = QImage(image->pixmap().size(), QImage::Format_ARGB32);
    }
    QPainter p(&im);
    p.drawImage(0, 0, renderBezierCurves());
    p.drawImage(0, 0, (this->*flowFieldMethod)());
    return im;
}

QImage FEMainWindow::checkerBoard()
{
    int w = image->pixmap().size().width();
    int h = image->pixmap().size().height();
    QImage checkerBoard(w, h, QImage::Format_ARGB32);
    QPainter p(&checkerBoard);
    for (int x = 0; x*32 < w; x++) {
        for (int y = 0; y * 32 < h; y++) {
            p.fillRect(x * 32, y * 32, 32, 32, ((x % 2) ^ (y % 2)) ? Qt::gray : Qt::white);
        }
    }
    return checkerBoard;
}

QList<FE_BezierCurve*> FEMainWindow::bezierCurves()
{
    QList<FE_BezierCurve*> l;
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->type() == FE_BezierCurve::Type) {
            l.push_back((FE_BezierCurve*) item);
        }
    }
    return l;
}
