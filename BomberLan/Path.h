#pragma once
#include "Tiles.h"
class Path :
	public Tiles
{
public:
	Path(int x, int y, SDL_Renderer* gRenderer);
	bool isWalkable() override;
	bool isDestroyable() override;
	~Path();
};

