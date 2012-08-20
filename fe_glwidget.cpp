#include "fe_glwidget.h"

#include "fe_element.h"

#include <QVector2D>

FE_GLWidget::FE_GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void FE_GLWidget::setElems(QVector<FE_Element*> elems)
{
	this->elems = elems;
}

void FE_GLWidget::setIndices(QVector<QVector<int> > ind)
{
	this->ind = ind;
}

void FE_GLWidget::initializeGL()
{

}

void FE_GLWidget::resizeGL(int w, int h)
{
	this->w = w;
	this->h = h;


}

void FE_GLWidget::paintGL()
{
	glViewport(0, 0, w, h);
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	foreach (QVector<int> I, ind) {

		for (int i = 0; i < 3; i++) {
			FE_Element *e1(elems[I[i]]);
			glColor3ub(e1->color().red(), e1->color().green(), e1->color().blue());
			glVertex3f(e1->pos().x(), e1->pos().y(), 0);
		}
	}
	glEnd();
}
