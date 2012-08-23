#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <math.h>

static void bezier_point(const qreal x[], const qreal y[], qreal t, qreal &xout, qreal &yout) {
	qreal a = 1 - t;		// 1-t
	qreal b = a * a * a;		// (1-t)^3
	qreal c = 3 * a * a * t;	// 3 * (1-t)^2 * t
	qreal d = 3 * a * t * t;	// 3 * (1-t)   * t^2
	qreal e = t * t * t;		// t^3


	xout = b * x[0] + c * x[1] + d * x[2] + e * x[3];
	yout = b * y[0] + c * y[1] + d * y[2] + e * y[3];
}

void draw_item_along_bezier(QPainter *painter, QGraphicsItem *item, const qreal x[], const qreal y[], int steps, const QColor &c1, const QColor &c2) {
	QStyleOptionGraphicsItem option;

	QTransform savedTransform(painter->transform());

	QAbstractGraphicsShapeItem *shape = dynamic_cast<QAbstractGraphicsShapeItem*>(item);
	QBrush savedBrush;
	QPen savedPen;
	if (shape) {
		savedBrush = shape->brush();
		savedPen = shape->pen();
	}

	for (int i = 0; i < steps; i++) {
		qreal t1 = (qreal) i / steps;
		qreal t2 = (qreal) (i + 1) / steps;

		qreal x1, y1, x2, y2;

		bezier_point(x, y, t1, x1, y1);
		bezier_point(x, y, t2, x2, y2);

		qreal dx = x2 - x1;
		qreal dy = y2 - y1;

		qreal angle = atan2(dy,  dx);

		painter->setTransform(savedTransform);
		painter->translate(x1, y1);
		painter->rotate(angle);
		if (shape && c1.isValid() && c2.isValid()) {
            int r = (1-t1) * c1.red() + t1 * c2.red();
            int g = (1-t1) * c1.green() + t1 * c2.green();
            int b = (1-t1) * c1.blue() + t1 * c2.blue();
			QColor c(r, g, b);
			
			QBrush brush(savedBrush);
			brush.setColor(c);
			QPen pen(savedPen);
			pen.setColor(c);
			shape->setBrush(brush);
			shape->setPen(pen);
		}
		item->paint(painter, &option, 0);
	}

	if (shape) {
		shape->setBrush(savedBrush);
		shape->setPen(savedPen);
	}
}
