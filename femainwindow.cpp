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
#include <QInputDialog>
#include <QDateTime>

#include <math.h>

#include "fe_flowelement.h"
#include "fe_flowelementhandle.h"
#include "fe_glwidget.h"

FEMainWindow::FEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FEMainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->installEventFilter(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    connect(ui->action_Load_image, SIGNAL(triggered()), this, SLOT(loadImage()));
    connect(ui->action_Save_flow_field, SIGNAL(triggered()), this, SLOT(saveFlowField()));
    connect(ui->action_Export_flow_map, SIGNAL(triggered()), this, SLOT(exportFlowmap()));
    connect(ui->action_Load_flow_field, SIGNAL(triggered()), this, SLOT(loadFlowField()));
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->action_Quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->action_Export_flow_map_fast, SIGNAL(triggered()), this, SLOT(exportFlowmapFast()));

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

    image = new QGraphicsPixmapItem(0, scene);
    image->setZValue(-2);
    // image->setOffset();

    glwidget = new FE_GLWidget(this);
    glwidget->setVisible(false);

    previewBtn = ui->previewBtn;
    ui->fileBtn->setMenu(ui->menu_File);
    ui->menuBar->setVisible(false);

    connect(previewBtn, SIGNAL(toggled(bool)), this, SLOT(bigPreview(bool)));
    connect(ui->expAndSwitchBtn, SIGNAL(clicked()), this, SLOT(expAndSwitch()));
    connect(ui->actionExport_flow_map_AKIMA, SIGNAL(triggered()), this, SLOT(exportFlowmapAkima()));
    connect(ui->makeGridBtn, SIGNAL(clicked()), this, SLOT(makeGrid()));
}

FEMainWindow::~FEMainWindow()
{
    delete ui;
}

void FEMainWindow::loadImage()
{
	QString fname = QFileDialog::getOpenFileName(this, "Select image", QString(), "Images (*.png; *.jpg)");
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
		foreach (FE_FlowElement *fe, scene->findChildren<FE_FlowElement*>()) {
			ds << fe->from();
			ds << fe->to();
		}
	}
}

void FEMainWindow::exportFlowmap()
{
	QString fname = QFileDialog::getSaveFileName(this, "Save flowmap", QString(), "Images (*.png; *.jpg)");
	if (!fname.isEmpty()) {
		QImage im(generateFlowMap());
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
	foreach (FE_FlowElement *fe, scene->findChildren<FE_FlowElement*>()) {
		fe->removeFromScene();
		delete fe;
	}

	QFile f(fname);
	f.open(QFile::ReadOnly);
	QDataStream ds(&f);
	while (!ds.atEnd()) {
		QPointF from;
		QPointF to;
		ds >> from;
		ds >> to;
		FE_FlowElement *elem = new FE_FlowElement(scene);
		elem->getHandleFrom()->setPos(from);
		elem->getHandleTo()->setPos(to);
		elem->onEndPositionChanged();
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
	QVector<FE_FlowElement*> elems = scene->findChildren<FE_FlowElement*>().toVector();
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
	int NXI = image->pixmap().width();
	double *XI = new double[NXI];
	int NYI = image->pixmap().height();
	double *YI = new double[NYI];
	double *ZI1 = new double[NXI*NYI]; // final output X
	double *ZI2 = new double[NXI*NYI]; // final output Y
	int IER;
	double *WK = new double[NDP * 17];
	int *IWK = new int[NDP * 25];
	int *EXTRPI = new int[NXI*NYI];
	int *NEAR_ = new int[NDP];
	int *NEXT = new int[NDP];
	double *DIST = new double[NDP];

	memset(WK, 0, NDP * 17 * sizeof(double));
	memset(IWK, 0, NDP * 25 * sizeof(int));
	memset(EXTRPI, 0, NXI*NYI*sizeof(int));
	memset(NEAR_, 0, NDP * sizeof(int));
	memset(NEXT, 0, NDP * sizeof(int));
	memset(DIST, 0, NDP * sizeof(double));


	for (int i = 0; i < NXI; i++)
		XI[i] = i;
	for (int i = 0; i < NYI; i++)
		YI[i] = i;

	for(int i = 0; i < NDP; i++) {
		XD[i] = elems[i]->pos().x();
		YD[i] = elems[i]->pos().y();
		QVector2D d(elems[i]->dir());
		d.normalize();
		ZD1[i] = d.x();
		ZD2[i] = d.y();
	}

	sdsf3p_(&MD, &NDP, XD, YD, ZD1, &NXI, XI, &NYI, YI, ZI1, &IER, WK, IWK, EXTRPI, NEAR_, NEXT, DIST);
	sdsf3p_(&MD, &NDP, XD, YD, ZD2, &NXI, XI, &NYI, YI, ZI2, &IER, WK, IWK, EXTRPI, NEAR_, NEXT, DIST);

	/* double max = 0;
	for (int i = 0; i < NXI * NYI; i++) {
		double t = ZI1[i]*ZI1[i]+ZI2[i]*ZI2[i+1];
		if (t > max)
			max = t;
	}
	max = sqrt(max); */

	QImage im(NXI, NYI, QImage::Format_ARGB32);
	uchar *data = im.bits();
	for (int x = 0; x < NXI; x++)
		for (int y = 0; y < NYI; y++) {
			int ofs1 = (y * NXI + x) * 4;
			int ofs2 = y * NXI + x;

			double x = /* ZI1[ofs2]; */ qMin(qMax(ZI1[ofs2], -1.0), 1.0);
			double y = /* ZI2[ofs2]; */ qMin(qMax(ZI2[ofs2], -1.0), 1.0);
			// double l = sqrt(x*x+y*y);
			// x /= l;
			// y /= l;

			data[ofs1 + 3] = 255;
			data[ofs1 + 2] = (x + 1) * 255 / 2;
			data[ofs1 + 1] = (y + 1) * 255 / 2;
			data[ofs1 + 0] = 0;
		}

	delete [] XD;
	delete [] YD;
	delete [] ZD1;
	delete [] ZD2;
	delete [] XI;
	delete [] YI;
	delete [] ZI1;
	delete [] ZI2;
	delete [] WK;
	delete [] IWK;
	delete [] EXTRPI;
	delete [] NEAR_;
	delete [] NEXT;
	delete [] DIST;

	return im;
}

void FEMainWindow::newFile()
{
	image->setPixmap(QPixmap());
	foreach(FE_FlowElement *fe, scene->findChildren<FE_FlowElement*>()) {
		fe->removeFromScene();
		delete fe;
	}
	generatePreview();
}

void FEMainWindow::exportFlowmapFast()
{
	QString fname = QFileDialog::getSaveFileName(this, "Save flowmap", QString(), "Images (*.png; *.jpg)");
	if (!fname.isEmpty()) {
		QImage im(fastGenerateFlowMap().toImage());
		im.save(fname);
		exportFName = QString("%1;2").arg(fname);
	}
}

void FEMainWindow::bigPreview(bool b)
{
	if (b) {
		origPixmap = image->pixmap();
		image->setPixmap(fastGenerateFlowMap());
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
		im = fastGenerateFlowMap().toImage();
	else
		im = akimaGenerateFlowMap();
	im.save(exportFName.left(exportFName.length()-2));
}

void FEMainWindow::exportFlowmapAkima()
{
	QString fname = QFileDialog::getSaveFileName(this, "Save flowmap", QString(), "Images (*.png; *.jpg)");
	if (!fname.isEmpty()) {
		QImage im(akimaGenerateFlowMap());
		im.save(fname);
		exportFName = QString("%1;3").arg(fname);
	}
}

void FEMainWindow::makeGrid()
{
    int cols = QInputDialog::getInt(this, "Make grid", "Number of columns");
    int rows = QInputDialog::getInt(this, "Make grid", "Number of rows");
    int dir_x = QInputDialog::getInt(this, "Make grid", "X direction");
    int dir_y = QInputDialog::getInt(this, "Make grid", "Y direction");
    int w = image->pixmap().width();
    int h = image->pixmap().height();

    for (int x = 0; x <= cols; x++) {
        for (int y = 0; y <= rows; y++) {
            FE_FlowElement *elem = new FE_FlowElement(scene);
            for (int i = 0; i < 2; i++) {
                elem->getHandleFrom()->setPos(((x == 0 && y == 0) ? -1 : 0) + x * w / cols - dir_x / 2, y * h / rows - dir_y / 2);
                elem->getHandleTo()->setPos(x * w / cols + dir_x / 2, y * h / cols + dir_y / 2);
            }
            elem->onEndPositionChanged();
        }
    }
    generatePreview();
}

bool FEMainWindow::eventFilter(QObject *o, QEvent *e)
{
    if (ui->indivBtn->isChecked()) {
        if (e->type() == QEvent::GraphicsSceneMousePress) {
            QGraphicsSceneMouseEvent *ge = (QGraphicsSceneMouseEvent*) e;
            QGraphicsItem *item = scene->itemAt(ge->scenePos());
            if (ge->button() == Qt::LeftButton && (item == 0 || (item->flags() & QGraphicsItem::ItemIsMovable) == 0)) {
                FE_FlowElement *elem = new FE_FlowElement(scene);
                elem->getHandleFrom()->setPos(ge->scenePos());
                elem->getHandleTo()->setPos(ge->scenePos());
                elem->getHandleFrom()->setPos(ge->scenePos());
                elem->getHandleTo()->setPos(ge->scenePos());
                elem->getHandleTo()->mousePressEvent(ge);
                elem->onEndPositionChanged();
                // generatePreview();
            } else if (ge->button() == Qt::RightButton && item != 0 && item->type() == FE_FlowElementHandle::Type) {
                FE_FlowElement *fe = ((FE_FlowElementHandle*) item)->flowElement();
                fe->removeFromScene();
                delete fe;
                // generatePreview();
            }
        } else if (e->type() == QEvent::GraphicsSceneMouseRelease) {
            generatePreview();
        }
    } else if (ui->brushBtn->isChecked() || ui->eraserBtn->isChecked()) {
        static QPointF lastBrushPos, midBrushPos;
//        static quint64 lastTimestamp;
        if (e->type() == QEvent::GraphicsSceneMousePress) {
            QGraphicsSceneMouseEvent *ge = (QGraphicsSceneMouseEvent*) e;
            lastBrushPos = ge->scenePos();
            midBrushPos = lastBrushPos;
//            lastTimestamp = QDateTime::currentMSecsSinceEpoch();
            foreach (FE_FlowElement *elem, scene->findChildren<FE_FlowElement*>()) {
                elem->setAffectedByBrush(false);
            }
        } else if (e->type() == QEvent::GraphicsSceneMouseMove) {
            QGraphicsSceneMouseEvent *ge = (QGraphicsSceneMouseEvent*) e;
            if (ge->buttons() & Qt::LeftButton) {
                int brushSizeSq = ui->brushSizeSlider->value();
                bool affectOnce = ui->brushOnceChkbx->isChecked();
                brushSizeSq *= brushSizeSq;
                QVector2D v(ge->scenePos() - lastBrushPos);
                // v.normalize();
                foreach (FE_FlowElement *elem, scene->findChildren<FE_FlowElement*>()) {
                    if (affectOnce && elem->isAffectedByBrush())
                        continue;
                    QPointF pos(elem->pos());
                    if (QVector2D(pos - ge->scenePos()).lengthSquared() <= brushSizeSq) {
                        if (ui->eraserBtn->isChecked()) {
                            elem->removeFromScene();
                            delete elem;
                        } else {
                            qreal radius(elem->radius());
                            QPointF from(pos - v.normalized().toPointF() * radius);
                            QPointF to(pos + v.normalized().toPointF() * radius);
                            elem->setAffectedByBrush(true);
                            elem->setFrom(from);
                            elem->setTo(to);
                        }
                    }
                }
                if (v.lengthSquared() > 16*16)
                    lastBrushPos = midBrushPos;
                if (v.lengthSquared() > 8*8)
                    midBrushPos = ge->scenePos();
//                if (QDateTime::currentMSecsSinceEpoch() - lastTimestamp > 500) {
//                    lastBrushPos = (4 * ge->scenePos() + lastBrushPos) / 5;
//                    lastTimestamp = QDateTime::currentMSecsSinceEpoch();
//                }
            }
            return true;
        } else if (e->type() == QEvent::GraphicsSceneMouseRelease) {
            generatePreview();
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

QImage FEMainWindow::generateFlowMap()
{
	QSize s(image->pixmap().size());
	int w = s.width();
	int h = s.height();

	double *A = new double[w * h * 3];
	for (int i = 0; i < w*h*3; i++)
		A[i]=-1;

	// Voronoi tesselation
	QVector<FE_FlowElement*> elems = scene->findChildren<FE_FlowElement*>().toVector();
	#pragma omp parallel for
	for (int i = 0; i < elems.size(); i++)
	{
		QPointF pos(elems[i]->pos());
		QVector2D dir(elems[i]->dir());
		if (dir.length() < 1)
			dir = QVector2D();
		dir.normalize();

		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++) {
				int ofs = (y * w + x) * 3;
				qreal l = QVector2D(pos - QPointF(x, y)).lengthSquared();
				if (l < A[ofs] || A[ofs] == -1) {
					A[ofs] = l;
					A[ofs + 1] = dir.x();
					A[ofs + 2] = dir.y();
				}
			}
	}

	double *B = new double[w * h * 2];

	// Natural neighbor
	#pragma omp parallel for
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			int r = 0;
			int count = 0;
			qreal dir_x = 0;
			qreal dir_y = 0;
			while(true) {
				int count1 = count;
				for (int x1 = qMax(0, x - r); x1 <= qMin(w-1, x + r); x1++) {
					qreal l = (x1-x)*(x1-x) + r*r;
					int ofs1 = (qMax(0, y - r) * w + x1) * 3;
					Q_ASSERT(ofs1 < w*h*3);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						dir_x += A[ofs1+1];
						dir_y += A[ofs1+2];
						count++;
					}
					ofs1 = (qMin(h-1, y + r) * w + x1) * 3;
					Q_ASSERT(ofs1 < w*h*3);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						dir_x += A[ofs1+1];
						dir_y += A[ofs1+2];
						count++;
					}
				}
				for (int y1 = qMax(0, y - r); y1 <= qMin(h-1, y + r); y1++) {
					qreal l = (y1-y)*(y1-y) + r*r;
					int ofs1 = (y1 * w + qMax(0, x - r)) * 3;
					Q_ASSERT(ofs1 < w*h*3);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						dir_x += A[ofs1+1];
						dir_y += A[ofs1+2];
						count++;
					}
					ofs1 = (y1 * w + qMin(w-1, x + r)) * 3;
					Q_ASSERT(ofs1 < w*h*3);
					Q_ASSERT(A[ofs1] != -1);
					if (l <= A[ofs1]) {
						dir_x += A[ofs1+1];
						dir_y += A[ofs1+2];
						count++;
					}
				}
				if (count1 == count)
					break;
				r++;
			}
			int ofs = (y * w + x) * 2;
			B[ofs] = dir_x / count;
			B[ofs+1] = dir_y / count;
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
		bits[i * 4 + 2] = (B[i * 2] + 1) / 2 * 255;
		bits[i * 4 + 1] = (B[i * 2 + 1] + 1) / 2 * 255;
		bits[i * 4] = 0;
	}


	delete [] A;
	delete [] B;

	return im;
}

QPixmap FEMainWindow::fastGenerateFlowMap()
{
	QVector<FE_FlowElement*> elems(scene->findChildren<FE_FlowElement*>().toVector());
	QProcess p;
	p.start("qdelaunay", QStringList("Fv") << "Qt");
	if (!p.waitForStarted()) {
		QMessageBox::warning(this, "qdelaunay failed", "Failed to start qdelaunay");
		return QPixmap();
	}
	p.write(QString("2 rbox %1 D2\r\n").arg(elems.size()).toAscii());
	p.write(QString("%1\r\n").arg(elems.size()).toAscii());
	foreach (FE_FlowElement *e, elems) {
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
		return QPixmap();
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
	glwidget->setElems(elems);
	glwidget->setIndices(indices);
	return glwidget->renderPixmap(image->pixmap().width(), image->pixmap().height());
}

void FEMainWindow::generatePreview()
{
	QPixmap fm(fastGenerateFlowMap());
	previewBtn->setIconSize(QSize(100, 75));
	previewBtn->setIcon(QIcon(fm));
	if (previewBtn->isChecked())
		image->setPixmap(fm);
}
