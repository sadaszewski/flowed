#ifndef FE_ELEMENT_H
#define FE_ELEMENT_H

#include <QPointF>
#include <QColor>

class FE_Element
{
public:
	virtual QPointF pos() const = 0;
	virtual QColor color() const = 0;
	virtual bool passive() const = 0;
	virtual void setPassive(bool) = 0;
	virtual ~FE_Element() {}
};

#endif // FE_ELEMENT_H
