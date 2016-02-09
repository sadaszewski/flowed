/*
 * Copyright (c) 2012-2016, Stanislaw Adaszewski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
