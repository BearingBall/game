#pragma once
#include "mapObjects.h"

class Triangle final : public Object
{
private:
	Point secondCoordinate;
	Point thirdCoordinate;
public:
	Triangle() = delete;
	explicit Triangle(Point _first, Point _second, Point _third, double h, int _texture);
	~Triangle() = default;
	DrawerBeam collision(Beam m) override;
	void draw(SDL_Renderer *renderer) override;
};
