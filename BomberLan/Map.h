#pragma once
#include "Path.h"
#include "Brick.h"
#include <vector>
#include <memory>

class Map
{
public:
	Map(SDL_Renderer* gRenderer);
	void renderCopy(SDL_Renderer* gRenderer);
	~Map();
private:
	std::vector<std::unique_ptr<Tiles>> tiles;//Vector of unique_ptr so there is one array for all the tiles (path, brick...)
};

