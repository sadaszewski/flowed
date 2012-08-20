#ifndef FE_GRADIENTELEMENT_H
#define FE_GRADIENTELEMENT_H

#include <QGraphicsEllipseItem>

#include "fe_element.h"

class FE_GradientElement : public QGraphicsEllipseItem, public FE_Element
{
public:
	enum {
		Type = UserType + 2
	};

	FE_GradientElement();

	void setColor(const QColor&);
	QColor color() const;

	void setPassive(bool);
	bool passive() const;

	QPointF pos() const;

	int type() const;

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	bool m_Passive;
};

#endif // FE_GRADIENTELEMENT_H
