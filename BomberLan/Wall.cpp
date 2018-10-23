#include "Wall.h"



Wall::Wall(int x, int y, SDL_Renderer* gRenderer)
:Tiles(x, y, "Wall.bmp", gRenderer)
{
}

bool Wall::isWalkable() { return false; }

bool Wall::isDestroyable() { return false; }

Wall::~Wall()
{
}
