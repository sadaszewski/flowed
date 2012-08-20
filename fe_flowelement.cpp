#include "fe_flowelement.h"

#include <QGraphicsScene>
#include "fe_flowelementhandle.h"
#include <QVector2D>
#include <QQuaternion>
#include <QGraphicsEllipseItem>
#include <math.h>
#include <QVector3D>

float FE_FlowElement::m_MaxRadius = 32;

void FE_FlowElement::setMaxRadius(float r)
{
	m_MaxRadius = r;
}

float FE_FlowElement::maxRadius()
{
	return m_MaxRadius;
}

FE_FlowElement::FE_FlowElement(QGraphicsScene *s):
	QObject(s)
{
	scene = s;
	m_WaveSize = 0;
	m_BrushedTime = QTime::currentTime();
	m_Passive = false;

	QPen pen(Qt::red);

	handleFrom = new FE_FlowElementHandle(-4, -4, 8, 8, this);
	handleTo = new FE_FlowElementHandle(-4, -4, 8, 8, this);
	handleMiddle = new FE_FlowElementHandle(-4, -4, 8, 8, this);

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

QPointF FE_FlowElement::dir() const
{
	return handleTo->pos() - handleFrom->pos();
}

QPointF FE_FlowElement::pos() const
{
	// return (handleTo->pos() + handleFrom->pos())/2;
	return handleFrom->pos();
}

QColor FE_FlowElement::color() const
{
	QVector3D v(dir());
	v /= (2 * m_MaxRadius);
	v += QVector3D(1, 1, 1);
	v /= 2;
	v *= QVector3D(255, 255, 0);
	return QColor(v.x(), v.y(), m_WaveSize, 255);
}

void FE_FlowElement::setPassive(bool p)
{
	m_Passive = p;

	line1->setPen(QPen(line1->pen().brush(), 1, p ? Qt::DotLine : Qt::SolidLine));
}

bool FE_FlowElement::passive() const
{
	return m_Passive;
}

qreal FE_FlowElement::radius() const
{
	return QVector2D(handleTo->pos() - handleFrom->pos()).length() / 2;
}

void FE_FlowElement::setBrushed(bool b)
{
	m_Brushed = b;
}

bool FE_FlowElement::brushed() const
{
	return m_Brushed;
}

void FE_FlowElement::setBrushedTime(const QTime &t)
{
	m_BrushedTime = t;
}

const QTime& FE_FlowElement::brushedTime() const
{
	return m_BrushedTime;
}

void FE_FlowElement::onEndPositionChanged()
{
	if (radius() > m_MaxRadius) {
		handleTo->setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
		handleTo->setPos(handleFrom->pos() + QVector2D(dir()).normalized().toPointF() * m_MaxRadius * 2);
		handleTo->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	}

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

void FE_FlowElement::setWaveSize(int s)
{
	m_WaveSize = s;
}

int FE_FlowElement::waveSize() const
{
	return m_WaveSize;
}
