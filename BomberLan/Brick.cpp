#include "Brick.h"



Brick::Brick(int x, int y, SDL_Renderer* gRenderer)
:Tiles(x,y,"Brick.bmp",gRenderer)
{
}

bool Brick::isWalkable() { return false; }

bool Brick::isDestroyable() { return true; }

Brick::~Brick()
{
}
