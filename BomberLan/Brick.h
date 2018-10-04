#pragma once
#include "Tiles.h"
class Brick :
	public Tiles
{
public:
	Brick(int x, int y, SDL_Renderer* gRenderer);
	bool isWalkable() override;
	bool isDestroyable() override;
	~Brick();
};

