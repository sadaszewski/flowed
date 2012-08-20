#include "fe_flowelementhandle.h"

FE_FlowElementHandle::FE_FlowElementHandle(qreal x, qreal y, qreal width, qreal height, FE_FlowElement *elem, QGraphicsItem * parent):
	QGraphicsRectItem(x, y, width, height, parent)
{
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	this->elem = elem;
}

void FE_FlowElementHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsRectItem::mousePressEvent(event);
}

FE_FlowElement* FE_FlowElementHandle::flowElement()
{
	return elem;
}

QVariant FE_FlowElementHandle::itemChange ( FE_FlowElementHandle::GraphicsItemChange change, const QVariant & value )
{
	if (change == ItemPositionHasChanged)
		emit positionChanged();

	return QGraphicsRectItem::itemChange(change, value);
}

int FE_FlowElementHandle::type() const
{
	return Type;
}
