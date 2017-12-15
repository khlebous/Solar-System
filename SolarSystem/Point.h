#pragma once
namespace GL
{
	struct  Point
	{
		float x, y, z, w;
		Point();
		Point(float _x, float _y, float _z);
		Point(const Point& p);
		bool operator==(Point& p)const;
		bool operator!=(Point& p)const;
	};
}
