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

class FEMainWindow : public QMainWindow
{
    Q_OBJECT

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

protected:
	bool eventFilter(QObject *, QEvent *);
	bool event(QEvent *);
	int tool();

private:
	QImage generateFlowMap();
	QPixmap fastGenerateFlowMap();
	void generatePreview();
	void loadFlowField(const QString&);
	QImage akimaGenerateFlowMap();
	QImage nnGenerateFlowMap();
	QVector<FE_Element*> elems();

private:
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
