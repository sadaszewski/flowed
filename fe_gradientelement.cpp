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
