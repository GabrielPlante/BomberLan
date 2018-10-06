#include "Bomb.h"



Bomb::Bomb(int xTile, int yTile, int power, SDL_Renderer* gRenderer)
	: Renderable(xTile*35+35/2-28/2, yTile*35+35/2-28/2, 28, 28, "Bomb.bmp", gRenderer)
{
	dropTime = SDL_GetTicks();
	this->power = power;
}

bool Bomb::refresh() {
	if (SDL_GetTicks() > dropTime + 2000) {
		explode();
		return false;
	}
	return true;
}

void Bomb::explode() {

}

Bomb::~Bomb()
{
}
