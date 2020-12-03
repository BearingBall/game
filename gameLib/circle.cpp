#include "circle.h"

Circle::Circle(Point _first, size_t _radius, double h) :Object(_first, h, -1)
{
	radius = _radius;
}

void Circle::draw(SDL_Renderer *renderer)
{
	double pointX;
	double pointY;
	for (int t = 0; t < 360; t++)
	{
		pointX = coordinate.x + radius * cos(t);
		pointY = coordinate.y + radius * sin(t);
		SDL_RenderDrawPoint(renderer, pointX, pointY);
	}
}

DrawerBeam Circle::collision(Beam m)
{
	return DrawerBeam{ 0};
}