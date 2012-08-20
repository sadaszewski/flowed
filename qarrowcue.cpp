/*

Copyright (c) 2011, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "qarrowcue.h"

#include <QTimer>
#include <QDrag>
#include <QVector2D>
#include <QPaintEvent>
#include <QPainter>
#if defined(Q_WS_X11)
#include <QX11Info>
#endif // Q_WS_X11
#if defined(Q_WS_WIN)
#include <QApplication>
#include <QDesktopWidget>
#endif // Q_WS_WIN

#include <stdio.h>

QArrowCue::QArrowCue() // QDrag *parent)
{
	m_StartPosition = QCursor::pos();
	/* QPoint srcWidgetScreenPos(parent->source()->mapToGlobal(QPoint(0, 0)));
	QRect startPosClip(parent->source()->rect().translated(srcWidgetScreenPos));
	if (m_StartPosition.x() < startPosClip.left())
	{
		m_StartPosition.setX(startPosClip.left());
	} else
	if (m_StartPosition.x() > startPosClip.right())
	{
		m_StartPosition.setX(startPosClip.right());
	}
	if (m_StartPosition.y() < startPosClip.top())
	{
		m_StartPosition.setY(startPosClip.top());
	} else
	if (m_StartPosition.y() > startPosClip.bottom())
	{
		m_StartPosition.setY(startPosClip.bottom());
	} */
	m_UpdatePositionTimer = new QTimer(this);
	QObject::connect(m_UpdatePositionTimer, SIGNAL(timeout()), this, SLOT(updatePosition()));
	// QObject::connect(parent, SIGNAL(destroyed()), this, SLOT(deleteLater()));
	m_UpdatePositionTimer->start(30);
	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	// setAttribute(Qt::WA_NoSystemBackground);
	setGeometry(QRect(m_StartPosition, m_StartPosition + QPoint(1,1)));
	setPalette(QColor(255, 200, 0));
	setWindowOpacity(0.75);
	show();
}

void QArrowCue::updatePosition()
{
	QVector2D vec(QCursor::pos() - m_StartPosition);

	qreal vecLen(vec.length());
	vec = vec.normalized() * (vecLen > 16 ? vecLen - 16 : 1);

	QPoint topLeft(m_StartPosition);
	QPoint bottomRight(m_StartPosition + vec.toPoint());

	QPolygon p(QVector<QPoint>() << QPoint(0, -8) << QPoint(16, 8) << QPoint(-16, 8));
	QLineF l(topLeft, bottomRight);
	QLineF lorig(0, 1, 0, 0);
	QLineF orthoVec(l.normalVector()); // .unitVector());
	QVector2D normVec(orthoVec.p2() - orthoVec.p1());
	normVec.normalize();
	QLineF l1(l.translated((normVec * 5).toPointF()));
	QLineF l2(l.translated((-normVec * 5).toPointF()));
	QPolygon pline(QVector<QPoint>() << l1.p1().toPoint() << l1.p2().toPoint() << l2.p2().toPoint() << l2.p1().toPoint());

	qreal angle(l.angleTo(lorig));
	QTransform t;
	t.rotate(angle, Qt::ZAxis);
	p = t.map(p);
	// p.translate(16, 16);
	p.translate(bottomRight);

	m_Shape = p.united(pline);
#if defined(Q_WS_WIN)
	setGeometry(qApp->desktop()->screenGeometry());
#else
	setGeometry(m_Shape.boundingRect().adjusted(-2, -2, 2, 2));
	m_Shape.translate(-m_Shape.boundingRect().topLeft() + QPoint(2, 2));
#endif // Q_WS_WIN

	QRegion r(m_Shape);
	// r.unite(pline);
	// r.translate();
#if defined(Q_WS_X11)
	if (!QX11Info::isCompositingManagerRunning())
	{
		setMask(r);
	}
#endif // Q_WS_X11

	update();


	/* if (topLeft.x() > bottomRight.x())
	{
		topLeft.setX(bottomRight.x());
		bottomRight.setX(m_StartPosition.x());
	}
	if (topLeft.y() > bottomRight.y())
	{
		topLeft.setY(bottomRight.y());
		bottomRight.setY(m_StartPosition.y());
	}

	setGeometry(QRect(topLeft, bottomRight)); */
}

void QArrowCue::paintEvent(QPaintEvent*)
{
	// printf("QArrowCue::paintEvent()\n");
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(QColor(225, 180, 0), 2));
	painter.setBrush(QColor(255, 200, 0));
	painter.drawConvexPolygon(m_Shape);
}
