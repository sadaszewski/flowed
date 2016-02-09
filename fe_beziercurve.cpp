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

#include "fe_beziercurve.h"

#include <QEvent>
#include <QGraphicsSceneEvent>
#include <QColorDialog>
#include <QPen>
#include <QGraphicsScene>
#include <QInputDialog>

#include "femainwindow.h"

FE_BezierCurve *FE_BezierCurve::m_LastCurve;

FE_BezierCurve* FE_BezierCurve::lastCurve()
{
    return m_LastCurve;
}

FE_BezierCurve::FE_BezierCurve(const QPointF &pt, QGraphicsScene *scene):
    QGraphicsItemGroup(0)
{
    m_Bezier = new QGraphicsPathItem(this);
    m_Segments = new QGraphicsPathItem(this);

    m_Bezier->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    m_Segments->setPen(QPen(Qt::white, 1, Qt::DashLine));

    for (int i = 0; i < 4; i++) {
        m_Points.push_back(newPoint(QPointF(pt.x() + i * 10, pt.y() + i * 10), Qt::gray));
    }

    updatePaths();

    m_LastCurve = this;
    m_Width = 5;

    scene->addItem(this);
}

FE_BezierCurve::~FE_BezierCurve()
{
    qDeleteAll(m_Points);
}

void FE_BezierCurve::addPoint(const QPointF &pt)
{
    QPointF tail(m_Points.last()->pos());
    QColor c(m_Points.last()->brush().color());

    QPointF delta(pt - tail);

    m_Points.push_back(newPoint(tail + delta / 2, Qt::gray));
    m_Points.push_back(newPoint(tail + 2 * delta / 3, Qt::gray));
    m_Points.push_back(newPoint(pt, c));

    updatePaths();
}

void FE_BezierCurve::save(QDataStream &ds)
{
    ds << m_Width;
    ds << m_Points.size();
    foreach(QGraphicsEllipseItem *item, m_Points) {
        ds << item->scenePos();
        ds << item->brush().color();
    }
}

void FE_BezierCurve::load(QDataStream &ds)
{
    qDeleteAll(m_Points);
    m_Points.clear();
    ds >> m_Width;
    int n;
    ds >> n;
    for (int i = 0; i < n; i++) {
        QPointF p;
        QColor c;
        ds >> p;
        ds >> c;
        m_Points.push_back(newPoint(p, c));
    }
    updatePaths();
}

void draw_item_along_bezier(QPainter *painter, QGraphicsItem *item, const qreal x[], const qreal y[], int steps, const QColor &c1, const QColor &c2);

void FE_BezierCurve::render(QPainter *painter)
{
    float w = m_Width;
    QGraphicsRectItem *item = new QGraphicsRectItem(-w/2, -w/2, w, w);
    item->setBrush(QBrush(Qt::gray));

    for (int i = 0; i < m_Points.size() - 3; i += 3) {
        qreal x[] = {m_Points[i]->scenePos().x(), m_Points[i + 1]->scenePos().x(), m_Points[i + 2]->scenePos().x(), m_Points[i + 3]->scenePos().x()};
        qreal y[] = {m_Points[i]->scenePos().y(), m_Points[i + 1]->scenePos().y(), m_Points[i + 2]->scenePos().y(), m_Points[i + 3]->scenePos().y()};

        draw_item_along_bezier(painter, item, x, y, 1000, m_Points[i]->brush().color(), m_Points[i + 3]->brush().color());
    }

    delete item;
}

int FE_BezierCurve::type() const
{
    return Type;
}

bool FE_BezierCurve::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress) {
        m_LastCurve = this;

        if (((QGraphicsSceneMouseEvent*) event)->button() == Qt::MiddleButton) {
            if (m_Points.indexOf((QGraphicsEllipseItem*) watched) % 3 == 0) {
                QColor c = QColorDialog::getColor(((QGraphicsEllipseItem*) watched)->brush().color(), 0, "Pick color", QColorDialog::ShowAlphaChannel);
                if (c.isValid()) {
                    updateColor((QAbstractGraphicsShapeItem*) watched, c);
                }
                watched->ungrabMouse();
                FEMainWindow::instance()->generatePreview();
                return true;
            } else {
                bool ok;
                int w = QInputDialog::getInt(0, "Curve width", "Curve width", m_Width, 1, 255, 1, &ok);
                if (ok) {
                    m_Width = w;
                }
                watched->ungrabMouse();
                FEMainWindow::instance()->generatePreview();
                return true;
            }
        } else if (((QGraphicsSceneMouseEvent*) event)->button() == Qt::RightButton) {
            int idx = m_Points.indexOf((QGraphicsEllipseItem*) watched);
            if (m_Points.size() > 4 && idx > 0 && idx % 3 == 0) {
                qDeleteAll(m_Points.mid(idx - 2, 3));
                m_Points.erase(m_Points.begin() + idx - 2, m_Points.begin() + idx + 1);
                updatePaths();
                return true;
            } else if (idx % 3 == 0) {
                m_LastCurve = 0;
                // qDeleteAll(m_Points);
                delete this;
                return true;
            }
        }
    } else if (event->type() == QEvent::GraphicsSceneMouseMove) {
        updatePaths();
    }

    return false;
}

QGraphicsEllipseItem* FE_BezierCurve::newPoint(const QPointF &pt, const QColor &c)
{
    QGraphicsEllipseItem *p = scene()->addEllipse(-5, -5, 10, 10);
    updateColor(p, c);
    p->setFlags(p->flags() | QGraphicsItem::ItemIsMovable);
    p->setPos(p->mapToParent(p->mapFromScene(pt)));
    p->setZValue(1);
    p->installSceneEventFilter(this);
    return p;
}

void FE_BezierCurve::updatePaths()
{
    QPainterPath p;

    p.moveTo(m_Points[0]->pos());
    for (int i = 1; i < m_Points.size(); i += 3) {
        p.cubicTo(m_Points[i]->pos(), m_Points[i + 1]->pos(), m_Points[i + 2]->pos());
    }

    m_Bezier->setPath(p);

    p = QPainterPath();
    p.moveTo(m_Points[0]->pos());
    for (int i = 1; i < m_Points.size(); i++) {
        p.lineTo(m_Points[i]->pos());
    }

    m_Segments->setPath(p);
}

void FE_BezierCurve::updateColor(QAbstractGraphicsShapeItem *item, const QColor &c)
{
    item->setBrush(QBrush(c));
    item->setPen(QPen(c.darker().rgb()));
}
