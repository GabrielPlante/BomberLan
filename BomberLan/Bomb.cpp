#include "Bomb.h"



Bomb::Bomb(int xTile, int yTile, int power, SDL_Renderer* gRenderer, Map* map)
	: Renderable(xTile*35+35/2-28/2, yTile*35+35/2-28/2, 28, 28, "Bomb.bmp", gRenderer)
{
	this->map = map;
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
	for (int i = 0; i != 4; ++i) {//For every direction
		bool x = false;
		for (int j = 1; j != power+1 && !x; ++j) {
			switch (i)
			{
			case 0: x = map->destroyTile({getTilePosition()[0], getTilePosition()[1] - j}); break;
			case 1: x = map->destroyTile({getTilePosition()[0] - j, getTilePosition()[1]}); break;
			case 2: x = map->destroyTile({getTilePosition()[0], getTilePosition()[1] + j}); break;
			case 3: x = map->destroyTile({getTilePosition()[0] + j, getTilePosition()[1]}); break;
			}
		}
	}
}

Bomb::~Bomb()
{
}
