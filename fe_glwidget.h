#ifndef FE_GLWIDGET_H
#define FE_GLWIDGET_H

#include <QGLWidget>

class FE_Element;

class FE_GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit FE_GLWidget(QWidget *parent = 0);

	void setElems(QVector<FE_Element*> elems);
	void setIndices(QVector<QVector<int> > ind);
	void paintGL();

signals:

public slots:

protected:
	void initializeGL();
	void resizeGL(int w, int h);


private:
	QVector<FE_Element*> elems;
	QVector<QVector<int> > ind;
	int w;
	int h;
};

#endif // FE_GLWIDGET_H
