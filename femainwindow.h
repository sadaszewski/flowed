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
	void newFile();
	void exportFlowmapFast();
	void bigPreview(bool);
	void expAndSwitch();
	void exportFlowmapAkima();
    void makeGrid();

protected:
	bool eventFilter(QObject *, QEvent *);
	bool event(QEvent *);

private:
	QImage generateFlowMap();
	QPixmap fastGenerateFlowMap();
	void generatePreview();
	void loadFlowField(const QString&);
	QImage akimaGenerateFlowMap();

private:
    Ui::FEMainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *image;
    FE_GLWidget *glwidget;
    QPushButton *previewBtn;
    QPixmap origPixmap;
    QString exportFName;
};

#endif // FEMAINWINDOW_H
