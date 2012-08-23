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
