#pragma once
#include "mapObjects.h"

class Rectangle final: public Object
{
private:
	Point secondCoordinate;
	Point thirdCoordinate;
	Point fourthCoordinate;
public:
	Rectangle() = delete;
	explicit Rectangle(Point _first, Point _second, Point _third, Point _fourth, double h, int _texture);
	~Rectangle() = default;
	DrawerBeam collision(Beam m) override;
	void draw(SDL_Renderer *renderer) override;
};
