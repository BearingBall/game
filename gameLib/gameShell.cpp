#include "gameShell.h"
#include <iostream>
#include <string>
#include "fstream"
#include "triangle.h"
#include "gameExceptions.h"

#define IF_STREAM_THROW(pointer,exception) if (!pointer) { throw exception; }
#define IF_NULL_THROW(pointer,exception) if (pointer == nullptr) { throw exception; }

namespace
{
	char* findSubString(std::string & string)
	{
		char* subString = &string[0];
		for (int i = 0; i < string.size(); ++i)
		{
			if (isdigit(string[i]))
			{
				subString = &string[i];
				break;
			}
		}
		return subString;
	}
}

void GameShell::setUpLevel(std::string& _level)
{
	level = _level;
	setUpSettings();
	engine->map.setLevel(_level);
	setUpMap();
}

void GameShell::setUpSettings()
{
	std::ifstream setting(std::string("../gameFiles/") + level + std::string("/settings.txt"));
	IF_STREAM_THROW(setting, InputDataCorruption());
	Point a, b, c;
	std::string string;
	std::getline(setting, string);
	char* subString = findSubString(string);
	sscanf_s(subString, "%lf %lf", &a.x, &a.y);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf %lf", &b.x, &b.y);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf %lf", &c.x, &c.y);
	engine = new Engine(level, a, b, c);
	IF_NULL_THROW(engine, MemoryError());
	engineSeted = true;
	double r, an, ls, as, vr, va, tf;
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf %lf", &a.x, &a.y);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf", &r);
	Circle player(a, r, 0);

	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf", &an);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf", &ls);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf", &as);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf", &vr);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf", &va);
	std::getline(setting, string);
	subString = findSubString(string);
	sscanf_s(subString, "%lf", &tf);
	engine->map.setCamera(player, an, ls, as, vr, va, tf);
}

void GameShell::setUpMap()
{
	std::ifstream rects(std::string("../gameFiles/") + level + std::string("/map/rectangles.txt"));
	IF_STREAM_THROW(rects, InputDataCorruption());
	std::string string;
	char* subString;
	Point a, b, c, d;
	double h;
	
	while (rects)
	{
		std::getline(rects, string);
		subString = findSubString(string);
		int i = sscanf_s(subString, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y, &h);
		std::getline(rects, string);
		if (i != 9)
		{
			continue;	
		}

		
		
		int texture = engine->map.textures.addTexture(engine->getRenderer(), std::string("../gameFiles/") + level + std::string("/map/") + string);
		if (texture != -1)
		{
			Rectangle* rect = new Rectangle({ a.x,a.y }, { b.x,b.y }, 
				{ c.x,c.y }, { d.x,d.y }, h, texture);
			IF_NULL_THROW(rect, MemoryError());
			engine->map.objects.push_back(rect);
		}
	}
	rects.close();
	
	std::ifstream trians(std::string("../gameFiles/") + level + std::string("/map/triangles.txt"));
	IF_STREAM_THROW(trians, InputDataCorruption());
	while (trians)
	{
		std::getline(trians, string);
		subString = findSubString(string);
		int i = sscanf_s(subString, "%lf %lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &h);
		std::getline(trians, string);
		if (i != 7)
		{
			continue;
		}
		int texture = engine->map.textures.addTexture(engine->getRenderer(), std::string("../gameFiles/") + level + std::string("/map/") + string);
		if (texture != -1)
		{
			Triangle* trian = new Triangle({ a.x,a.y }, { b.x,b.y }, { c.x,c.y }, h, texture);
			IF_NULL_THROW(trian, MemoryError());
			engine->map.objects.push_back(trian);
		}
	}
}

GameShell::~GameShell()
{
	if (engineSeted)
	{
		delete engine;
	}
}

int GameShell::menuSimulation()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("menu", 300, 300,1000, 600, SDL_WINDOW_ALLOW_HIGHDPI);
	IF_NULL_THROW(window, SDL_GraphicsError());
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	IF_NULL_THROW(window, SDL_GraphicsError());
	SDL_Surface* surface = SDL_LoadBMP("../gameFiles/MenuSprites/controls.bmp");
	IF_NULL_THROW(surface, SDL_GraphicsError());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	IF_NULL_THROW(texture, SDL_GraphicsError());
	SDL_Event windowEvent;
	bool skip = false;
	
	for (int i = 0; i < 50; ++i)
	{
		SDL_SetTextureColorMod(texture, i*5, i*5, i*5);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
		if (SDL_PollEvent(&windowEvent) && windowEvent.type == SDL_KEYDOWN)
		{
			skip = true;
		}
		if (skip)
		{
			break;
		}
	}
	
	for(int i=0;i<50;++i)
	{
		SDL_Delay(100);
		if (SDL_PollEvent(&windowEvent) && windowEvent.type == SDL_KEYDOWN)
		{
			skip = true;
		}
		if (skip)
		{
			break;
		}
	}

	for (int i = 50; i < 0; --i)
	{
		SDL_SetTextureColorMod(texture, i * 5, i * 5, i * 5);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
		if (SDL_PollEvent(&windowEvent) && windowEvent.type == SDL_KEYDOWN)
		{
			skip = true;
		}
		if (skip)
		{
			break;
		}
	}

	SDL_RenderClear(renderer);
	
	bool levels[16];
	for (int i = 0; i < 16; ++i)
	{
		levels[i] = false;
	}

	for(int i = 0; i<16;++i)
	{
		std::ifstream levelStream(std::string("../gameFiles/Level ") + static_cast<char>((i + 1) / 10 + 48) + static_cast<char>((i + 1) % 10 + 48) + "/settings.txt");
		SDL_Surface* surfaceLevel;
		if (levelStream)
		{
			levels[i] = true;
			surfaceLevel = SDL_LoadBMP((std::string("../gameFiles/MenuSprites/Level ") + static_cast<char>((i + 1) / 10 + 48) + static_cast<char>((i + 1) % 10 + 48) + ".bmp").data());
		}
		else
		{
			surfaceLevel = SDL_LoadBMP("../gameFiles/MenuSprites/emptyLevel.bmp");
		}
		IF_NULL_THROW(surfaceLevel, InputDataCorruption());
		SDL_Texture* textureLevel = SDL_CreateTextureFromSurface(renderer, surfaceLevel);
		IF_NULL_THROW(textureLevel, SDL_GraphicsError());
		SDL_Rect rect{ 200 + i % 4 * 150 ,50 + i/4*125,100,100 };
		SDL_RenderCopy(renderer, textureLevel, NULL, &rect);
	}

	SDL_RenderPresent(renderer);

	bool levelAccepted = false;
	int level = -1;
	while(!levelAccepted)
	{
		while (SDL_PollEvent(&windowEvent)&&!levelAccepted)
		{
			if (windowEvent.type == SDL_MOUSEBUTTONDOWN && windowEvent.button.button == SDL_BUTTON_LEFT)
			{
				level = -1;
				if ((windowEvent.button.y - 50) % 125 <= 100 &&
					windowEvent.button.y >= 50 && windowEvent.button.y <= 550 &&
					(windowEvent.button.x - 200) % 150 <=100 &&
					windowEvent.button.x>=200 && windowEvent.button.x<=800)
				{
					level = ((windowEvent.button.y - 50) / 125)*4;
					level += (windowEvent.button.x - 200) / 150 + 1;
					if (levels[level-1])
					{
						levelAccepted = true;
					}
				}
			}
		}
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	return level;
}