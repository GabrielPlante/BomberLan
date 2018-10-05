#include "Bomberman.h"



Bomberman::Bomberman(int x, int y, SDL_Renderer* gRenderer)
	:Renderable(x, y, 18, 36, "Bomberman.bmp", gRenderer)
{
}


Bomberman::~Bomberman()
{
}
