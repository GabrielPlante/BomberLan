#pragma once
#include "Tiles.h"
class Wall :
	public Tiles
{
public:
	Wall(int x, int y, SDL_Renderer* gRenderer);
	bool isWalkable() override;
	bool isDestroyable() override;
	~Wall();
};

