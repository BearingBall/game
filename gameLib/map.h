#pragma once
#include <vector>


#include "camera.h"
#include "mapObjects.h"
#include "rect.h"
#include "textures.h"

class Map final
{
private:
	bool cameraSeted = false;
	size_t mapWidth;
	size_t mapHeight;
	size_t windowWidth;
	size_t windowHeight;
    Camera* camera;
	std::string level;

	void drawDefaultBackground(SDL_Renderer *renderer);
public:
	Textures textures;
	std::vector<Object*> objects;
	Map() = delete;
	explicit Map(size_t _mapWidth, size_t _mapHeight, size_t _windowWidth, size_t _windowHeight);
	~Map();
	size_t getMapWidth() const;
	size_t getMapHeight() const;
	size_t getWindowWidth() const;
	size_t getWindowHeight() const;
	Camera* getCamera() const;
	
	int playerModelCollission(double angleShift, double & collisionAngle);
	
	void draw(SDL_Renderer *renderer);
	
	void setCamera(Circle circle, double _angle, double _linealSpeed, double _angleSpeed, double _viewRange, double _viewAngle, double _traceFreq);
	void cameraStepForward(int type);
	void cameraStepBack(int type);
	void cameraStepLeft(int type);
	void cameraStepRight(int type);
	void cameraLeftRightTurn( double motion);
	void setLevel(std::string& _level);
	std::string getLevel() const;
};
