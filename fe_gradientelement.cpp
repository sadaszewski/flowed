#include "fe_gradientelement.h"

#include <QBrush>
#include <QPen>

FE_GradientElement::FE_GradientElement()
{
	setRect(-5, -5, 10, 10);
	setColor(Qt::gray);
	setFlag(QGraphicsItem::ItemIsMovable);
	m_Passive = false;
}

FE_GradientElement::~FE_GradientElement() {
    // delete parentItem();
}

void FE_GradientElement::setColor(const QColor &c)
{
    QColor d(c.darker().rgb());
    setPen(QPen(d, 1, m_Passive ? Qt::DotLine : Qt::SolidLine));
	setBrush(c);
}

QColor FE_GradientElement::color() const
{
	return brush().color();
}

void FE_GradientElement::setPassive(bool p)
{
	m_Passive = p;

    setPen(QPen(QColor(brush().color().darker().rgb()), 1, p ? Qt::DotLine : Qt::SolidLine));
}

bool FE_GradientElement::passive() const
{
	return m_Passive;
}

QPointF FE_GradientElement::pos() const
{
	return scenePos();
}

int FE_GradientElement::type() const
{
	return Type;
}

void FE_GradientElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsEllipseItem::mouseReleaseEvent(event);
}
