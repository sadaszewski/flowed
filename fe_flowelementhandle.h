#ifndef FE_FLOWELEMENTHANDLE_H
#define FE_FLOWELEMENTHANDLE_H

#include <QGraphicsRectItem>

class FE_FlowElement;

class FE_FlowElementHandle: public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	enum {
		Type = UserType + 1
	};

	FE_FlowElementHandle(qreal x, qreal y, qreal width, qreal height, FE_FlowElement *elem, QGraphicsItem * parent = 0);

	void mousePressEvent(QGraphicsSceneMouseEvent *event);

	FE_FlowElement *flowElement();

	int type() const;

protected:
	QVariant itemChange ( GraphicsItemChange change, const QVariant & value );

signals:
	void positionChanged();

private:
	FE_FlowElement *elem;
};

#endif // FE_FLOWELEMENTHANDLE_H
