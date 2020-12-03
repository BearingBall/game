#pragma once
#include <SDL.h>

#include "map.h"

class Engine final
{
private:
	SDL_Window *window;
	SDL_Event windowEvent;
	SDL_Renderer *renderer;
public:
	Map map;
	Engine() = delete;
	explicit Engine(std::string name, Point windowCoordinate, Point windowSize, Point mapSize);
	void mapDraw();
	~Engine();

	SDL_Renderer* getRenderer() const;
	void setMouseInMiddlePosition() const;
};
