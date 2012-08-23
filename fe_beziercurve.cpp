#include "fe_beziercurve.h"

#include <QEvent>
#include <QGraphicsSceneEvent>
#include <QColorDialog>
#include <QPen>

FE_BezierCurve::FE_BezierCurve(const QPointF &pt, QGraphicsScene *scene):
    QGraphicsItemGroup(0, scene)
{
    m_Bezier = new QGraphicsPathItem(this);
    m_Segments = new QGraphicsPathItem(this);

    for (int i = 0; i < 4; i++) {
        m_Points.push_back(newPoint(QPointF(pt.x() + i * 10, pt.y() + i * 10)));
    }

    updatePaths();
}

void FE_BezierCurve::addPoint(const QPointF &pt)
{
    QPointF tail(m_Points.last()->pos());

    QPointF delta(pt - tail);

    m_Points.push_back(newPoint(tail + delta / 2));
    m_Points.push_back(newPoint(tail + 2 * delta / 3));
    m_Points.push_back(newPoint(pt));

    updatePaths();
}

bool FE_BezierCurve::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress) {
        if (((QGraphicsSceneMouseEvent*) event)->button() == Qt::MiddleButton) {
            if (m_Points.indexOf((QGraphicsEllipseItem*) watched) % 3 == 0) {
                QColor c = QColorDialog::getColor(((QGraphicsEllipseItem*) watched)->brush().color());
                if (c.isValid()) {
                    updateColor((QAbstractGraphicsShapeItem*) watched, c);
                }
                return true;
            }
        } else if (((QGraphicsSceneMouseEvent*) event)->button() == Qt::RightButton) {
            int idx = m_Points.indexOf((QGraphicsEllipseItem*) watched);
            if (m_Points.size() > 4 && idx > 0 && idx % 3 == 0) {
                qDeleteAll(m_Points.mid(idx - 2, 3));
                m_Points.erase(m_Points.begin() + idx - 2, m_Points.begin() + idx + 1);
                updatePaths();
                return true;
            }
        }
    } else if (event->type() == QEvent::GraphicsSceneMove) {
        updatePaths();
    }

    return false;
}

QGraphicsEllipseItem* FE_BezierCurve::newPoint(const QPointF &pt)
{
    QGraphicsEllipseItem *p = new QGraphicsEllipseItem(-8, -8, 16, 16, this);
    p->setFlags(p->flags() | QGraphicsItem::ItemIsMovable);
    p->setPos(p->mapToParent(p->mapFromScene(pt)));
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
    QBrush b(item->brush());
    b.setColor(c);
    item->setBrush(b);
    QPen p(item->pen());
    p.setColor(c);
    item->setPen(p);
}
