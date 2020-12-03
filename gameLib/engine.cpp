#include "engine.h"
#include "gameExceptions.h"
#include "rect.h"

#define IF_NULL_THROW(pointer,exception) if (pointer == nullptr) { throw exception; }

Engine::Engine(std::string name, Point windowCoordinate, Point windowSize, Point mapSize) : map(mapSize.x, mapSize.y, windowSize.x, windowSize.y)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(name.data(), windowCoordinate.x, windowCoordinate.y, 
		windowSize.x, windowSize.y, SDL_WINDOW_ALLOW_HIGHDPI);
	IF_NULL_THROW(window, SDL_GraphicsError());
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	IF_NULL_THROW(renderer, SDL_GraphicsError());
}

Engine::~Engine()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::mapDraw()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 0x40);
	SDL_Rect rect = { 0, 0, (double)map.getMapWidth(), (double)map.getMapHeight() };
	SDL_RenderDrawRect(renderer, &rect);
	map.draw(renderer);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x40);
	SDL_RenderPresent(renderer);
}

void Engine::setMouseInMiddlePosition() const 
{
	SDL_WarpMouseInWindow(window,map.getWindowWidth() / 2, map.getWindowHeight() / 2);
}

SDL_Renderer* Engine::getRenderer() const
{
	return renderer;
}