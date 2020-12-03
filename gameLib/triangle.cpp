#include "triangle.h"

#include <algorithm>

#include "collider.h"

Triangle::Triangle(Point _first, Point _second, Point _third, double h, int _texture) :Object(_first, h, _texture)
{
	secondCoordinate = _second;
	thirdCoordinate = _third;
}

void Triangle::draw(SDL_Renderer *renderer)
{
	SDL_RenderDrawLine(renderer, coordinate.x, coordinate.y, secondCoordinate.x, secondCoordinate.y);
	SDL_RenderDrawLine(renderer, coordinate.x, coordinate.y, thirdCoordinate.x, thirdCoordinate.y);
	SDL_RenderDrawLine(renderer, thirdCoordinate.x, thirdCoordinate.y, secondCoordinate.x, secondCoordinate.y);
}

DrawerBeam Triangle::collision(Beam beam)
{
	double edgeLength = 0;
	double length = beam.length();
	double cosAngle = 1;
	double cosAngle2;
	Point collision;
	if (collider(beam.a, beam.b, coordinate, secondCoordinate, collision, cosAngle2)
		&& length > vectorLength(beam.a, collision))
	{
		length = vectorLength(beam.a, collision);
		edgeLength = vectorLength(collision, coordinate);
		cosAngle = cosAngle2;
	}

	if (collider(beam.a, beam.b, secondCoordinate, thirdCoordinate, collision, cosAngle2)
		&& length > vectorLength(beam.a, collision))
	{
		length = vectorLength(beam.a, collision);
		edgeLength = vectorLength(collision, secondCoordinate);
		cosAngle = cosAngle2;
	}
	if (collider(beam.a, beam.b, thirdCoordinate, coordinate, collision, cosAngle2)
		&& length > vectorLength(beam.a, collision))
	{
		length = vectorLength(beam.a, collision);
		edgeLength = vectorLength(collision, thirdCoordinate);
		cosAngle = cosAngle2;
	}
	return DrawerBeam{ length, edgeLength, texture, cosAngle };
}