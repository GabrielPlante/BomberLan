#include "Bomb.h"



Bomb::Bomb(int xTile, int yTile, int power, SDL_Renderer* gRenderer, Map* map)
	: Renderable(xTile*35+35/2-28/2, yTile*35+35/2-28/2, 28, 28, "Bomb.bmp", gRenderer)
{
	this->map = map;
	dropTime = SDL_GetTicks();
	this->power = power;
}

void Bomb::renderCopy(SDL_Renderer* gRenderer) {
	if (SDL_GetTicks() < dropTime + 2000 ) Renderable::renderCopy(gRenderer);
	else {
		for (int i = 0; i != 4; ++i) {//For every direction
			bool x = false;//We need to stop the explosion at the first non-walkable block
			for (int j = 1; j != power + 1 && !x; ++j) {
				SDL_Rect explosion;
				switch (i)
				{
				case 0: if (map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] - j + 1 }, TOP) != WALKABLE) {
					x = true;
					break;
				}
					explosion.x = getTilePosition()[0] * 35 + 35 / 2 - 35 / 8; explosion.y = (getTilePosition()[1] - j) * 35;
					explosion.w = 35 / 4; explosion.h = 35; break;
				case 1: if (map->checkNextTile({ getTilePosition()[0] - j + 1,getTilePosition()[1]}, LEFT) != WALKABLE) {
					x = true;
					break;
				}
					explosion.x = (getTilePosition()[0] - j) * 35; explosion.y = getTilePosition()[1] * 35 + 35 / 2 - 35 / 8;
					explosion.w = 35; explosion.h = 35 / 4; break;
				case 2: if (map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] + j - 1 }, BOTTOM) != WALKABLE) {
					x = true;
					break;
				}
					explosion.x = getTilePosition()[0] * 35 + 35 / 2 - 35 / 8; explosion.y = (getTilePosition()[1] + j) * 35;
					explosion.w = 35 / 4; explosion.h = 35; break;
				case 3: if (map->checkNextTile({ getTilePosition()[0] + j - 1,getTilePosition()[1]}, RIGHT) != WALKABLE) {
					x = true;
					break;
				}
					explosion.x = (getTilePosition()[0] + j) * 35; explosion.y = getTilePosition()[1] * 35 + 35 / 2 - 35 / 8;
					explosion.w = 35; explosion.h = 35 / 4; break;
				}
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderFillRect(gRenderer, &explosion);
			}
		}
	}
}

bool Bomb::refresh() {
	if (SDL_GetTicks() > dropTime + 2000) {
		if (explode())
			return false;
	}
	return true;
}

bool Bomb::explode() {
	if (SDL_GetTicks() > dropTime + 2200)//The explosion last 200ms
		return true;
	if (!exploded) {
		map->destroyTile(getTilePosition());//Destroy the actual tile (to kill players)
		for (int i = 0; i != 4; ++i) {//For every direction
			bool x = false;//We need to stop the explosion at the first non-walkable block
			for (int j = 1; j != power + 1 && !x; ++j) {
				switch (i)
				{
				case 0: x = map->destroyTile({ getTilePosition()[0], getTilePosition()[1] - j }); break;
				case 1: x = map->destroyTile({ getTilePosition()[0] - j, getTilePosition()[1] }); break;
				case 2: x = map->destroyTile({ getTilePosition()[0], getTilePosition()[1] + j }); break;
				case 3: x = map->destroyTile({ getTilePosition()[0] + j, getTilePosition()[1] }); break;
				}
			}
		}
		exploded = true;
	}
	return false;
}

Bomb::~Bomb()
{
}
