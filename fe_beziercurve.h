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

#ifndef FE_BEZIERCURVE_H
#define FE_BEZIERCURVE_H

#include <QGraphicsItemGroup>

class FE_BezierCurve : public QGraphicsItemGroup
{
public:
    enum {
        Type = UserType + 3
    };

public:
    static FE_BezierCurve* lastCurve();

public:
    FE_BezierCurve(const QPointF&, QGraphicsScene *scene = 0);
    ~FE_BezierCurve();

    void addPoint(const QPointF&);

    void save(QDataStream &ds);
    void load(QDataStream &ds);

    void render(QPainter*);

    int type() const;

protected:
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

private:
    QGraphicsEllipseItem* newPoint(const QPointF&, const QColor&);
    void updatePaths();
    void updateColor(QAbstractGraphicsShapeItem*, const QColor&);
    void deleteLater();

private:
    QGraphicsPathItem *m_Bezier;
    QGraphicsPathItem *m_Segments;
    QList<QGraphicsEllipseItem*> m_Points;
    static FE_BezierCurve *m_LastCurve;
    int m_Width;
};

#endif // FE_BEZIERCURVE_H
