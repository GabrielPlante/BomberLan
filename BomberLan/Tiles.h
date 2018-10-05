#pragma once
#include "Renderable.h"


class Tiles : public Renderable
{
public:
	Tiles(int x, int y, std::string path, SDL_Renderer* gRenderer);
	virtual bool isWalkable() = 0;
	virtual bool isDestroyable() = 0;
	~Tiles();
protected:
};
