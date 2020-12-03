#include "camera.h"

#include <cmath>

Camera::Camera(Circle _circle, double _angle, double _linealSpeed, double _angleSpeed, double _viewRange, double _viewAngle, double _traceFreq): circle(_circle.coordinate, _circle.radius, 0)
{
	angle = _angle;
	linealSpeed = _linealSpeed;
	angleSpeed = _angleSpeed;
	viewRange = _viewRange;
	viewAngle = _viewAngle;
	traceFreq = _traceFreq;
}

void Camera::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x80, 0x20, 0x20, 0x90);
	circle.draw(renderer);
}