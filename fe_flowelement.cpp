#include "fe_flowelement.h"

#include <QGraphicsScene>
#include "fe_flowelementhandle.h"
#include <QVector2D>
#include <QQuaternion>
#include <QGraphicsEllipseItem>
#include <math.h>

FE_FlowElement::FE_FlowElement(QGraphicsScene *s):
	QObject(s)
{
	scene = s;

	QPen pen(Qt::red);

	handleFrom = new FE_FlowElementHandle(-3, -3, 6, 6, this);
	handleTo = new FE_FlowElementHandle(-3, -3, 6, 6, this);
	handleMiddle = new FE_FlowElementHandle(-3, -3, 6, 6, this);

	line1 = new QGraphicsLineItem(0, s);
	line2 = new QGraphicsLineItem(0, s);
	line3 = new QGraphicsLineItem(0, s);


	// ellipse = new QGraphicsEllipseItem(0, s);

	line1->setZValue(-1);
	line2->setZValue(-1);
	line3->setZValue(-1);
	// ellipse->setZValue(-1);

	handleFrom->setPen(pen);
	handleTo->setPen(pen);
	handleMiddle->setPen(pen);
	line1->setPen(pen);
	line2->setPen(pen);
	line3->setPen(pen);
	// ellipse->setPen(pen);

	s->addItem(handleFrom);
	s->addItem(handleMiddle);
	s->addItem(handleTo);

	connect(handleFrom, SIGNAL(positionChanged()), this, SLOT(onEndPositionChanged()));
	connect(handleTo, SIGNAL(positionChanged()), this, SLOT(onEndPositionChanged()));
	connect(handleMiddle, SIGNAL(positionChanged()), this, SLOT(onMiddlePositionChanged()));
}

FE_FlowElement::~FE_FlowElement()
{

}

void FE_FlowElement::removeFromScene()
{
	scene->removeItem(handleFrom);
	scene->removeItem(handleTo);
	scene->removeItem(handleMiddle);
	scene->removeItem(line1);
	scene->removeItem(line2);
	scene->removeItem(line3);
	// scene->removeItem(ellipse);
	delete line1;
	delete line2;
	delete line3;
	delete handleFrom;
	delete handleTo;
	delete handleMiddle;
	// delete ellipse;
}

void FE_FlowElement::setFrom(const QPointF &p)
{
	handleFrom->setPos(p);
	handleMiddle->setPos((handleFrom->pos() + handleTo->pos()) / 2);
}

void FE_FlowElement::setTo(const QPointF &p)
{
	handleTo->setPos(p);
	handleMiddle->setPos((handleFrom->pos() + handleTo->pos()) / 2);
	alignArrow();
}

QPointF FE_FlowElement::from()
{
	return handleFrom->pos();
}

QPointF FE_FlowElement::to()
{
	return handleTo->pos();
}

FE_FlowElementHandle* FE_FlowElement::getHandleFrom()
{
	return handleFrom;
}

FE_FlowElementHandle* FE_FlowElement::getHandleTo()
{
	return handleTo;
}

QPointF FE_FlowElement::dir()
{
	return handleTo->pos() - handleFrom->pos();
}

QPointF FE_FlowElement::pos()
{
	return (handleTo->pos() + handleFrom->pos())/2;
}

qreal FE_FlowElement::radius()
{
	return QVector2D(handleTo->pos() - handleFrom->pos()).length() / 2;
}

void FE_FlowElement::onEndPositionChanged()
{
	handleMiddle->setFlag(FE_FlowElementHandle::ItemSendsGeometryChanges, false);
	handleMiddle->setPos((handleFrom->pos() + handleTo->pos()) / 2);
	handleMiddle->setFlag(FE_FlowElementHandle::ItemSendsGeometryChanges, true);
	alignArrow();
}

void FE_FlowElement::onMiddlePositionChanged()
{
	handleFrom->setFlag(FE_FlowElementHandle::ItemSendsGeometryChanges, false);
	handleTo->setFlag(FE_FlowElementHandle::ItemSendsGeometryChanges, false);
	QPointF old = (handleFrom->pos() + handleTo->pos()) / 2;
	handleFrom->setPos(handleMiddle->pos() + (handleFrom->pos() - old));
	handleTo->setPos(handleMiddle->pos() + (handleTo->pos() - old));
	handleFrom->setFlag(FE_FlowElementHandle::ItemSendsGeometryChanges);
	handleTo->setFlag(FE_FlowElementHandle::ItemSendsGeometryChanges);
	alignArrow();
}

void FE_FlowElement::alignArrow()
{
	line1->setLine(QLineF(handleFrom->pos(), handleTo->pos()));
	QPointF d(handleFrom->pos() - handleTo->pos());
	QVector3D v(d.x(), d.y(), 0);
	v.normalize();
	QQuaternion q = QQuaternion::fromAxisAndAngle(0, 0, 1, 45);
	line2->setLine(QLineF(handleTo->pos(), handleTo->pos() + q.rotatedVector(v).toVector2D().toPointF() * 10));
	q = QQuaternion::fromAxisAndAngle(0, 0, 1, -45);
	line3->setLine(QLineF(handleTo->pos(), handleTo->pos() + q.rotatedVector(v).toVector2D().toPointF() * 10));
	// float r = sqrt(d.x() * d.x() + d.y() * d.y()) / 2 + 10;
	// ellipse->setRect(QRectF(handleMiddle->pos().x() - r, handleMiddle->pos().y() - r, 2 * r, 2 * r));
}

bool FE_FlowElement::isAffectedByBrush()
{
    return affectedByBrush;
}

void FE_FlowElement::setAffectedByBrush(bool b)
{
    affectedByBrush = b;
}
