#include "rect.h"

#include <algorithm>

#include "collider.h"

Rectangle::Rectangle(Point _first, Point _second, Point _third, Point _fourth, double h, int _texture) :Object(_first, h, _texture)
{
	secondCoordinate = _second;
	thirdCoordinate = _third;
	fourthCoordinate = _fourth;
}

void Rectangle::draw(SDL_Renderer *renderer)
{
	SDL_RenderDrawLine(renderer, coordinate.x, coordinate.y, secondCoordinate.x, secondCoordinate.y);
	SDL_RenderDrawLine(renderer, secondCoordinate.x, secondCoordinate.y, thirdCoordinate.x, thirdCoordinate.y);
	SDL_RenderDrawLine(renderer, thirdCoordinate.x, thirdCoordinate.y, fourthCoordinate.x, fourthCoordinate.y);
	SDL_RenderDrawLine(renderer, fourthCoordinate.x, fourthCoordinate.y, coordinate.x, coordinate.y);
}

DrawerBeam Rectangle::collision(Beam beam)
{
	double edgeLength = 0;
	double length = beam.length();
	double cosAngle = 1;
	double cosAngle2;
	Point collision;
	if (collider(beam.a,beam.b,coordinate,secondCoordinate, collision, cosAngle2)
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
	if (collider(beam.a, beam.b, thirdCoordinate, fourthCoordinate, collision, cosAngle2)
		&& length > vectorLength(beam.a, collision))
	{
		length = vectorLength(beam.a, collision);
		edgeLength = vectorLength(collision, fourthCoordinate);
		cosAngle = cosAngle2;
	}
	if (collider(beam.a, beam.b, fourthCoordinate,	coordinate, collision, cosAngle2)
		&& length > vectorLength(beam.a, collision))
	{
		length = vectorLength(beam.a, collision);
		edgeLength = vectorLength(collision, fourthCoordinate);
		cosAngle = cosAngle2;
	}
	return DrawerBeam{length, edgeLength, texture, cosAngle};
}

