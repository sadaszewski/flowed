#ifndef FE_BEZIERCURVE_H
#define FE_BEZIERCURVE_H

#include <QGraphicsItemGroup>

class FE_BezierCurve : public QGraphicsItemGroup
{
public:
    FE_BezierCurve(const QPointF&, QGraphicsScene *scene = 0);

    void addPoint(const QPointF&);

protected:
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

private:
    QGraphicsEllipseItem* newPoint(const QPointF&);
    void updatePaths();
    void updateColor(QAbstractGraphicsShapeItem*, const QColor&);

private:
    QGraphicsPathItem *m_Bezier;
    QGraphicsPathItem *m_Segments;
    QList<QGraphicsEllipseItem*> m_Points;
};

#endif // FE_BEZIERCURVE_H
