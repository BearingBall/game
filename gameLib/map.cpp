#include "map.h"

#include <algorithm>
#include <iostream>
#include <thread>

#include "gameExceptions.h"

#define IF_NULL_THROW(pointer,exception) if (pointer == nullptr) { throw exception; }

int Map::playerModelCollission(double angleShift, double & collisionAngle)
{
	int collisions = 0;
	bool left = false;
	bool rigth = false;
	{
		double length = camera->circle.radius;
		double angleCounter = camera->angle - M_PI/2 + angleShift;
		while (angleCounter < camera->angle + angleShift)
		{
			Beam beam;
			beam.a = camera->circle.coordinate;
			beam.b = { beam.a.x + camera->viewRange*cos(angleCounter), beam.a.y + camera->viewRange*sin(angleCounter) };
			for (auto* element : objects)
			{
				auto it = element->collision(beam);
				if (length >= it.length)
				{
					length = it.length;
					collisionAngle = angleCounter;
					left = true;
				}
			}
			angleCounter += camera->traceFreq;
		}
	}
	{
		double length = camera->circle.radius;
		double angleCounter = camera->angle + angleShift;
		while (angleCounter < camera->angle + M_PI/2 + angleShift)
		{
			Beam beam;
			beam.a = camera->circle.coordinate;
			beam.b = { beam.a.x + camera->viewRange*cos(angleCounter), beam.a.y + camera->viewRange*sin(angleCounter) };
			for (auto* element : objects)
			{
				auto it = element->collision(beam);
				if (length >= it.length)
				{
					length = it.length;
					collisionAngle = angleCounter;
					rigth = true;
				}
			}
			angleCounter += camera->traceFreq;
		}
	}
	if (left) collisions++;
	if (rigth) collisions++;
	return collisions;
}

Map::Map(size_t _mapWidth, size_t _mapHeight, size_t _windowWidth, size_t _windowHeight)
{
	mapWidth = _mapWidth;
	mapHeight = _mapHeight;
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

size_t Map::getMapWidth() const
{
	return mapWidth;
}

size_t Map::getMapHeight() const
{
	return mapHeight;
}

size_t Map::getWindowWidth() const
{
	return windowWidth;
}

size_t Map::getWindowHeight() const
{
	return windowHeight;
}

Camera* Map::getCamera() const
{
	return camera;
}

void Map::cameraStepForward(int type)
{
	double modificator = 1;
	if (type == 1)
	{
		modificator *= camera->boost;
	}
	if (cameraSeted)
	{
		double collisionAngle;
		int collisions = playerModelCollission(0, collisionAngle);
		if (collisions==0)
		{
			camera->circle.coordinate.x += modificator * camera->linealSpeed*cos(camera->angle);
			camera->circle.coordinate.y += modificator * camera->linealSpeed*sin(camera->angle);
		}
		if (collisions==1)
		{
				if (collisionAngle > camera->angle)
				{
					camera->circle.coordinate.x += modificator * camera->linealSpeed*cos(collisionAngle - M_PI /2);
					camera->circle.coordinate.y += modificator * camera->linealSpeed*sin(collisionAngle - M_PI /2);
				}
				else
				{
					camera->circle.coordinate.x += modificator * camera->linealSpeed*cos(collisionAngle + M_PI / 2);
					camera->circle.coordinate.y += modificator * camera->linealSpeed*sin(collisionAngle + M_PI / 2);
				}
		}
	}
}

void Map::cameraStepBack(int type)
{
	double modificator = 1;
	if (type == 1)
	{
		modificator *= camera->boost;
	}
	if (cameraSeted)
	{
		double collisionAngle;
		double secondAngle;
		int collisions = playerModelCollission(M_PI, collisionAngle);
		if (collisions == 0)
		{
			camera->circle.coordinate.x -= modificator * camera->linealSpeed*cos(camera->angle);
			camera->circle.coordinate.y -= modificator * camera->linealSpeed*sin(camera->angle);
		}
		if (collisions == 1)
		{
			if (collisionAngle > camera->angle + M_PI)
			{
				camera->circle.coordinate.x += modificator * camera->linealSpeed*cos(collisionAngle - M_PI / 2);
				camera->circle.coordinate.y += modificator * camera->linealSpeed*sin(collisionAngle - M_PI / 2);
			}
			else
			{
				camera->circle.coordinate.x += modificator * camera->linealSpeed*cos(collisionAngle + M_PI / 2);
				camera->circle.coordinate.y += modificator * camera->linealSpeed*sin(collisionAngle + M_PI / 2);
			}
		}
	}
}

void Map::cameraStepRight(int type)
{
	double modificator = 1;
	if (type == 1)
	{
		modificator *= camera->boost;
	}
	if (cameraSeted)
	{
		double collisionAngle;
		int collisions = playerModelCollission(M_PI /2, collisionAngle);
		if (collisions == 0)
		{
			camera->circle.coordinate.x += modificator * camera->linealSpeed*cos(camera->angle + M_PI / 2);
			camera->circle.coordinate.y += modificator * camera->linealSpeed*sin(camera->angle + M_PI / 2);
		}
		if (collisions == 1)
		{
			if (collisionAngle > camera->angle + 3.1415 / 2)
			{
				camera->circle.coordinate.x +=  modificator* camera->linealSpeed*cos(collisionAngle - M_PI / 2);
				camera->circle.coordinate.y +=  modificator* camera->linealSpeed*sin(collisionAngle - M_PI / 2);
			}
			else
			{
				camera->circle.coordinate.x +=  modificator* camera->linealSpeed*cos(collisionAngle + M_PI / 2);
				camera->circle.coordinate.y +=  modificator* camera->linealSpeed*sin(collisionAngle + M_PI / 2);
			}
		}
	}
}

void Map::cameraStepLeft(int type)
{
	double modificator = 1;
	if (type == 1)
	{
		modificator *= camera->boost;
	}
	if (cameraSeted)
	{
		double collisionAngle;
		int collisions = playerModelCollission(-M_PI / 2, collisionAngle);
		if (collisions == 0)
		{
			camera->circle.coordinate.x +=  modificator* camera->linealSpeed*cos(camera->angle - M_PI / 2);
			camera->circle.coordinate.y +=  modificator* camera->linealSpeed*sin(camera->angle - M_PI / 2);
		}
		if (collisions == 1)
		{
			if (collisionAngle > camera->angle - 3.1415 / 2)
			{
				camera->circle.coordinate.x +=  modificator* camera->linealSpeed*cos(collisionAngle - M_PI / 2);
				camera->circle.coordinate.y +=  modificator* camera->linealSpeed*sin(collisionAngle - M_PI / 2);
			}
			else
			{
				camera->circle.coordinate.x +=  modificator* camera->linealSpeed*cos(collisionAngle + M_PI / 2);
				camera->circle.coordinate.y +=  modificator* camera->linealSpeed*sin(collisionAngle + M_PI / 2);
			}
		}
	}
}

void Map::cameraLeftRightTurn( double motion)
{
	if (cameraSeted)
	{
		camera->angle += motion * camera->angleSpeed;
	}
}

void Map::setCamera(Circle circle, double _angle, double _linealSpeed, double _angleSpeed, double _viewRange, double _viewAngle, double _traceFreq)
{
	if (cameraSeted)
	{
		delete camera;
	}
	camera = new Camera(circle, _angle, _linealSpeed, _angleSpeed,_viewRange,_viewAngle, _traceFreq);
	IF_NULL_THROW(camera, MemoryError());
	cameraSeted = true;
}

Map::~Map()
{
	if (cameraSeted)
	{
		delete camera;
	}
	for (auto element : objects)
	{
		delete element;
	}
}

void Map::drawDefaultBackground(SDL_Renderer *renderer)
{
	SDL_Rect a = { 0,0,getWindowWidth(),getWindowHeight() * 0.4 };
	SDL_SetRenderDrawColor(renderer, 75, 75, 200, 0);
	SDL_RenderFillRect(renderer, &a);
	SDL_Rect b = { 0, getWindowHeight() * 0.4,getWindowWidth(),getWindowHeight() * 0.6 };
	SDL_SetRenderDrawColor(renderer, 18, 9, 6, 0);
	SDL_RenderFillRect(renderer, &b);
}

void Map::draw(SDL_Renderer* renderer)
{
	if (cameraSeted)
	{
		drawDefaultBackground(renderer);
		camera->draw(renderer);
		double angleCounter = camera->angle - camera->viewAngle;
				while (angleCounter < camera->angle + camera->viewAngle)
				{
					Beam beam;
					beam.a = camera->circle.coordinate;
					beam.b = { beam.a.x + camera->viewRange*cos(angleCounter), beam.a.y + camera->viewRange*sin(angleCounter) };
					DrawerBeam drawerBeam{ camera->viewRange, 0, -1, 1 };
					for (auto* element : objects)
					{
						drawerBeam = std::min(drawerBeam, element->collision(beam));
					}
					if (drawerBeam.length < getCamera()->viewRange * 0.99)
					{
						double ligthAbber = (angleCounter - camera->angle)*(angleCounter - camera->angle);
						SDL_SetRenderDrawColor(renderer,
							std::min(static_cast<double>(240), (25000 * (1 - ligthAbber)) / (drawerBeam.length * drawerBeam.length)),
							std::min(static_cast<double>(240), (25000 * (1 - ligthAbber)) / (drawerBeam.length  * drawerBeam.length)),
							std::min(static_cast<double>(240), (25000 * (1 - ligthAbber)) / (drawerBeam.length  * drawerBeam.length)),
							0xff);

						double lengthCorrected = drawerBeam.length * cos(angleCounter - camera->angle);
						SDL_Rect a;
						a.x = getWindowWidth() * (0.5 + (angleCounter - camera->angle) / camera->viewAngle / 2);
						a.y = getWindowHeight() / 2 * (0.8 - 4 / (lengthCorrected));
						a.h = getWindowHeight() * 4 / (lengthCorrected / 2);
						a.w = 2500 * camera->traceFreq;

						if (drawerBeam.texture != -1)
						{
							SDL_Rect b;
							b.x = static_cast<int>(drawerBeam.lengthFromLeftEdge * 30) % textures.getTextures()[drawerBeam.texture].rect.w;
							b.y = 0;
							b.w = std::max(static_cast<double>(1), 5 * camera->traceFreq*drawerBeam.length*sqrt(1 - drawerBeam.cosAngle*drawerBeam.cosAngle));
							b.h = textures.getTextures()[drawerBeam.texture].rect.h;
							SDL_RenderFillRect(renderer, &a);
							SDL_SetTextureColorMod(textures.getTextures()[drawerBeam.texture].polygon,
								std::min(static_cast<double>(220), (500000 * (1 - ligthAbber)) / (drawerBeam.length * drawerBeam.length)),
								std::min(static_cast<double>(220), (500000 * (1 - ligthAbber)) / (drawerBeam.length  * drawerBeam.length)),
								std::min(static_cast<double>(220), (500000 * (1 - ligthAbber)) / (drawerBeam.length  * drawerBeam.length)));
							SDL_RenderCopy(renderer, textures.getTextures()[drawerBeam.texture].polygon, &b, &a);
						}
					}
					SDL_SetRenderDrawColor(renderer, 0x20, 0x90, 0xff, 0x90);
					SDL_RenderDrawLine(renderer, camera->circle.coordinate.x, camera->circle.coordinate.y,
						camera->circle.coordinate.x + drawerBeam.length * cos(angleCounter),
						camera->circle.coordinate.y + drawerBeam.length * sin(angleCounter));
					angleCounter += camera->traceFreq;
				}
		SDL_SetRenderDrawColor(renderer, 0x20, 0x80, 0x20, 0x40);
		for (auto* element : objects)
		{
			element->draw(renderer);
		}
	}
}

void Map::setLevel(std::string& _level)
{
	level = _level;
}

std::string Map::getLevel() const
{
	return level;
}
