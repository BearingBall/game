
#include <iostream>
#include <SDL.h>

#include "map.h"
#include "rect.h"
#include "triangle.h"
#include "gameShell.h"
#include "gameExceptions.h"

bool gameSimulation()
{
	_CrtMemState startPoint, endPoint, diff;
	_CrtMemCheckpoint(&startPoint);
	{
		try
		{
			std::cout << "Welcome to WalkerGame\n";
			GameShell game;
			int levelNumber = game.menuSimulation();
			std::string level("Level ");
			level = level + static_cast<char>(levelNumber / 10 + 48) + static_cast<char>(levelNumber % 10 + 48);
			game.setUpLevel(level);
			game.engine->mapDraw();
			SDL_Event windowEvent;
			SDL_ShowCursor(SDL_DISABLE);
			bool pressedW = false;
			bool pressedS = false;
			bool pressedA = false;
			bool pressedD = false;
			bool pressedESC = false;
			int moveType = 0;
			while (!pressedESC)
			{
				while (SDL_PollEvent(&windowEvent))
				{
					if (windowEvent.type == SDL_MOUSEMOTION)
					{
						game.engine->map.cameraLeftRightTurn(static_cast<double>(windowEvent.motion.x) - game.engine->map.getWindowWidth() / 2);
						game.engine->setMouseInMiddlePosition();
					}
					if (windowEvent.type == SDL_KEYDOWN)
					{
						if (windowEvent.key.keysym.sym == SDLK_w)
						{
							pressedW = true;
						}
						if (windowEvent.key.keysym.sym == SDLK_a)
						{
							pressedA = true;
						}
						if (windowEvent.key.keysym.sym == SDLK_s)
						{
							pressedS = true;
						}
						if (windowEvent.key.keysym.sym == SDLK_d)
						{
							pressedD = true;
						}
						if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
						{
							pressedESC = true;
						}
						if (windowEvent.key.keysym.sym == SDLK_LSHIFT)
						{
							moveType = 1;
						}
					}
					if (windowEvent.type == SDL_KEYUP)
					{
						if (windowEvent.key.keysym.sym == SDLK_w)
						{
							pressedW = false;
						}
						if (windowEvent.key.keysym.sym == SDLK_a)
						{
							pressedA = false;
						}
						if (windowEvent.key.keysym.sym == SDLK_s)
						{
							pressedS = false;
						}
						if (windowEvent.key.keysym.sym == SDLK_d)
						{
							pressedD = false;
						}
						if (windowEvent.key.keysym.sym == SDLK_LSHIFT)
						{
							moveType = 0;
						}
					}
				}
				if (pressedW)
				{
					game.engine->map.cameraStepForward(moveType);
				}
				if (pressedS)
				{
					game.engine->map.cameraStepBack(moveType);
				}
				if (pressedA)
				{
					game.engine->map.cameraStepLeft(moveType);
				}
				if (pressedD)
				{
					game.engine->map.cameraStepRight(moveType);
				}
				game.engine->mapDraw();
			}
		}
		catch ( SDL_GraphicsError& a)
		{
			std::cout << "Something wrong. Sdl cant open window, create graphics file or same problem :(\n";
		}
		catch (MemoryError& a)
		{
			std::cout << "Your memory pool not enough for this game :(\n";
		}
		catch (InputDataCorruption& a)
		{
			std::cout << "Somebody broke game files... Try to find non corrupted version :(\n";
		}
	}
	_CrtMemCheckpoint(&endPoint);
	return _CrtMemDifference(&diff, &startPoint, &endPoint);
}
