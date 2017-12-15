#include "Point.h"

GL::Point::Point()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}
GL::Point::Point(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	w = 1;
}
GL::Point::Point(const GL::Point & p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	w = p.w;
}

bool GL::Point::operator==(Point & p) const
{
	return ((x==p.x)&&(y==p.y));
}
bool GL::Point::operator!=(Point & p) const
{
	return ((x != p.x) || (y != p.y));
}

