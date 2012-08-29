#ifndef FEMAINWINDOW_H
#define FEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class FEMainWindow;
}

class QGraphicsScene;
class QGraphicsPixmapItem;
class FE_GLWidget;
class QPushButton;
class FE_Element;
class QArrowCue;
class FE_BezierCurve;

class FEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static FEMainWindow* instance();

public:
    explicit FEMainWindow(QWidget *parent = 0);
    ~FEMainWindow();

public slots:
	void loadImage();
	void saveFlowField();
	void exportFlowmap();
	void loadFlowField();
	void newProject();
	void newFlowField();
	void newFlowFieldAndPreview();
	void exportFlowmapFast();
	void bigPreview(bool);
	void expAndSwitch();
	void exportFlowmapAkima();
	void generateGrid();
	void generateGradientGrid();
	void selectGradientBrushColor();
    void generatePreview();
    int showLicense();

protected:
	bool eventFilter(QObject *, QEvent *);
	bool event(QEvent *);
	int tool();

private:
	QImage generateFlowMap();
    QImage fastGenerateFlowMap();
	void loadFlowField(const QString&);
	QImage akimaGenerateFlowMap();
	QImage nnGenerateFlowMap();
	QVector<FE_Element*> elems();
    QImage renderBezierCurves();
    QImage renderFinalImage(QImage(FEMainWindow::*flowFieldMethod)(), bool useCheckerBoard = true);
    QImage checkerBoard();
    QList<FE_BezierCurve*> bezierCurves();

private:
    static FEMainWindow *m_Instance;
    Ui::FEMainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *image;
    FE_GLWidget *glwidget;
    QPushButton *previewBtn;
    QPixmap origPixmap;
    QString exportFName;
    QColor lastColor;
    int lastWaveSize;
    QColor m_GradientBrushColor;
    QArrowCue *m_ArrowCue;
};

#endif // FEMAINWINDOW_H
