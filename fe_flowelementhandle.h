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
