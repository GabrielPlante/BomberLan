#pragma once
#include <SDL.h>
#include <iostream>
#include "Tiles.h"
#include "Path.h"
#include <vector>
#include <memory>

class Map
{
public:
	Map();
	void init(SDL_Renderer* gRenderer);
	void renderCopy(SDL_Renderer* gRenderer);
	~Map();
private:
	std::vector<std::unique_ptr<Tiles>> tiles;
};

