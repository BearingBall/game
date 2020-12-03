#pragma once
#include <utility>

#include "point.h"

class Beam final
{
private:
public:
	Point a;
	Point b;
	double length();
};

double vectorLength(Point& a, Point& b);

double vectorLength(Point& a);