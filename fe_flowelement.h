/*
 * Copyright (c) 2012-2016, Stanislaw Adaszewski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
