#pragma once
#include "mapObjects.h"

class Circle final : public Object
{
private:
public:
	size_t radius;
	Circle() = delete;
	explicit Circle(Point _first, size_t _radius, double h);
	~Circle() = default;
	DrawerBeam collision(Beam m) override;
	void draw(SDL_Renderer *renderer) override;
};
