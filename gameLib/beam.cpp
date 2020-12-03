#include "beam.h"

double Beam::length()
{
	return	sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double vectorLength(Point& a,Point& b)
{
	return	sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double vectorLength(Point& a)
{
	return	sqrt(a.x*a.x + a.y*a.y);
}