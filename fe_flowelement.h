#ifndef FE_FLOWELEMENT_H
#define FE_FLOWELEMENT_H

#include <QObject>

#include <QGraphicsRectItem>
#include <QGraphicsObject>
class QGraphicsScene;
class FE_FlowElementHandle;
class QPoint;
class QGraphicsLineItem;
class QGraphicsEllipseItem;


class FE_FlowElement : public QObject
{
    Q_OBJECT
public:
    explicit FE_FlowElement(QGraphicsScene *s = 0);
	~FE_FlowElement();

	void setFrom(const QPointF&);
	void setTo(const QPointF&);

	QPointF from();
	QPointF to();

	FE_FlowElementHandle *getHandleFrom();
	FE_FlowElementHandle *getHandleTo();

	QPointF dir();
	QPointF pos();
	qreal radius();

	void removeFromScene();

    bool isAffectedByBrush();
    void setAffectedByBrush(bool);

signals:

public slots:
	void onEndPositionChanged();
	void onMiddlePositionChanged();

private:
	void alignArrow();

private:
	QGraphicsScene *scene;
	FE_FlowElementHandle *handleFrom;
	FE_FlowElementHandle *handleTo;
	FE_FlowElementHandle *handleMiddle;
	QGraphicsLineItem *line1;
	QGraphicsLineItem *line2;
	QGraphicsLineItem *line3;
	QGraphicsEllipseItem *ellipse;
    bool affectedByBrush;
};

#endif // FE_FLOWELEMENT_H
