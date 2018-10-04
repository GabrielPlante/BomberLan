#include "Path.h"



Path::Path(int x, int y, SDL_Renderer* gRenderer)
:Tiles(x, y, "Path.bmp", gRenderer)
{
}

bool Path::isWalkable() { return true; }

bool Path::isDestroyable() { return false; }

Path::~Path()
{
}
