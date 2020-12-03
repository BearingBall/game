#pragma once
#include "engine.h"


class GameShell final
{
private:
	bool engineSeted = false;
	void setUpSettings();
	void setUpMap();
	std::string level;
public:
	Engine* engine;

	int menuSimulation();
	
	void setUpLevel(std::string& _level);

	
	GameShell() = default;
	~GameShell();
};
