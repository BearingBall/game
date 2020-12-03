#pragma once
#include <SDL_render.h>

#include "point.h"

#include "beam.h"
#include "drawerBeam.h"
#include "textures.h"

class Object
{
protected:
	int texture;
public:
	Point coordinate;
	double h;
	Object() = delete;
	explicit Object(Point m, double _h, int _texture);
	virtual ~Object() = default;
	virtual DrawerBeam collision(Beam m);
	virtual void draw(SDL_Renderer *renderer);
};
