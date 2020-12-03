
#include <iostream>
#include <SDL.h>

#include "gameSimulation.h"

int main(int argc, char *argv[])
{
	bool flag = gameSimulation();
	std::cout<< "Memory leaks = " << flag;
	return 0;
}
