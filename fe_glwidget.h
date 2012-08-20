#ifndef FE_GLWIDGET_H
#define FE_GLWIDGET_H

#include <QGLWidget>

class FE_FlowElement;

class FE_GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit FE_GLWidget(QWidget *parent = 0);

	void setElems(QVector<FE_FlowElement*> elems);
	void setIndices(QVector<QVector<int> > ind);

signals:

public slots:

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	QVector<FE_FlowElement*> elems;
	QVector<QVector<int> > ind;
	int w;
	int h;
};

#endif // FE_GLWIDGET_H
