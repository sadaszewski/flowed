#ifndef FE_FLOWELEMENT_H
#define FE_FLOWELEMENT_H

#include <QObject>

#include <QGraphicsRectItem>
#include <QGraphicsObject>
#include <QTime>

#include "fe_element.h"

class QGraphicsScene;
class FE_FlowElementHandle;
class QPoint;
class QGraphicsLineItem;
class QGraphicsEllipseItem;


class FE_FlowElement : public QObject, public FE_Element
{
    Q_OBJECT
public:
	static void setMaxRadius(float);
	static float maxRadius();

public:
    explicit FE_FlowElement(QGraphicsScene *s = 0);
	~FE_FlowElement();

	void setFrom(const QPointF&);
	void setTo(const QPointF&);
	void setWaveSize(int);
	int waveSize() const;

	QPointF from();
	QPointF to();

	FE_FlowElementHandle *getHandleFrom();
	FE_FlowElementHandle *getHandleTo();

	QPointF dir() const;
	QPointF pos() const;
	qreal radius() const;
	QColor color() const;

	void setPassive(bool);
	bool passive() const;

	void setBrushed(bool);
	bool brushed() const;

	void setBrushedTime(const QTime&);
	const QTime& brushedTime() const;

	void removeFromScene();

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
	static float m_MaxRadius;
	int m_WaveSize;
	bool m_Brushed;
	QTime m_BrushedTime;
	bool m_Passive;
};

#endif // FE_FLOWELEMENT_H
