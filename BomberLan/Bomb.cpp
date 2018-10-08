#include "Bomb.h"



Bomb::Bomb(int xTile, int yTile, int power, SDL_Renderer* gRenderer, Map* map)
	: Renderable(xTile*35+35/2-28/2, yTile*35+35/2-28/2, 28, 28, "Bomb.bmp", gRenderer)
{
	this->map = map;
	dropTime = SDL_GetTicks();
	this->power = power;
}

void Bomb::renderCopy(SDL_Renderer* gRenderer) {
	if (!explosionTime) Renderable::renderCopy(gRenderer);
	else if (SDL_GetTicks() < explosionTime + 100) {
		for (int i = 0; i != 4; ++i) {//For every direction
			bool x = false;//We need to stop the explosion at the first non-walkable block
			for (int j = 1; j != power + 1 && !x; ++j) {
				SDL_Rect explosion;
				switch (i)//GL HF
				{
				case 0: if (map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] - j + 1 }, TOP) != WALKABLE
					&& map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] - j + 1 }, TOP) != BOMB) {
					x = true;
					break;
				}
					explosion.x = getTilePosition()[0] * 35 + 35 / 2 - 35 / 8; explosion.y = (getTilePosition()[1] - j) * 35;
					explosion.w = 35 / 4; explosion.h = 35; break;
				case 1: if (map->checkNextTile({ getTilePosition()[0] - j + 1,getTilePosition()[1]}, LEFT) != WALKABLE
					&& map->checkNextTile({ getTilePosition()[0] - j + 1,getTilePosition()[1]}, LEFT) != BOMB) {
					x = true;
					break;
				}
					explosion.x = (getTilePosition()[0] - j) * 35; explosion.y = getTilePosition()[1] * 35 + 35 / 2 - 35 / 8;
					explosion.w = 35; explosion.h = 35 / 4; break;
				case 2: if (map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] + j - 1 }, BOTTOM) != WALKABLE
					&& map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] + j - 1 }, BOTTOM) != BOMB) {
					x = true;
					break;
				}
					explosion.x = getTilePosition()[0] * 35 + 35 / 2 - 35 / 8; explosion.y = (getTilePosition()[1] + j) * 35;
					explosion.w = 35 / 4; explosion.h = 35; break;
				case 3: if (map->checkNextTile({ getTilePosition()[0] + j - 1,getTilePosition()[1]}, RIGHT) != WALKABLE
					&& map->checkNextTile({ getTilePosition()[0] + j - 1,getTilePosition()[1]}, RIGHT) != BOMB) {
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
	if (SDL_GetTicks() > dropTime + 2000) {//2 sec before explosion
		if (!explosionTime)
			explode();
		else if (SDL_GetTicks() > explosionTime + 100)//Explosion effect last 100 ms
			return false;
	}
	return true;
}

void Bomb::explode() {
	if (!explosionTime) {
		explosionTime = SDL_GetTicks();
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
	}
}

Bomb::~Bomb()
{
}
