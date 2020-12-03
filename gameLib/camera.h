#pragma once
#include <SDL_render.h>


#include "circle.h"
#include "point.h"

class Camera final
{
public:
	Circle circle;
	double angle;
	double linealSpeed;
	double angleSpeed;
	double viewRange;
	double viewAngle;
	double traceFreq;
	double boost = 2;
	Camera() = delete;
	explicit Camera(Circle circle, double _angle, double _linealSpeed, double _angleSpeed, double _viewRange, double _viewAngle, double _traceFreq);
	~Camera() = default;
	void draw(SDL_Renderer *renderer);
};
