#include "Bomb.h"



Bomb::Bomb(int xTile, int yTile, int power, Map* map, COLOR color)
	: Rect(xTile*35+35/2-28/2, yTile*35+35/2-28/2, 28, 28, color)
{
	this->map = map;
	dropTime = SDL_GetTicks();
	this->power = power;
}

void Bomb::renderCopy(SDL_Renderer* gRenderer) {
	if (!explosionTime) Rect::renderCopy(gRenderer);
	else if (SDL_GetTicks() < explosionTime + 100) {
		for (int i = 0; i != 4; ++i) {//For every direction
			bool x = false;//We need to stop the explosion at the first non-walkable block
			for (int j = 1; j != power + 1 && !x; ++j) {
				SDL_Rect explosion;
				switch (i)//GL HF
				{
				case 0: if (map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] - j + 1 }, TOP) != WALKABLE){
					x = true;
					break;
				}
					explosion.x = getTilePosition()[0] * 35 + 35 / 2 - 35 / 8; explosion.y = (getTilePosition()[1] - j) * 35;
					explosion.w = 35 / 4; explosion.h = 35; break;
				case 1: if (map->checkNextTile({ getTilePosition()[0] - j + 1,getTilePosition()[1]}, LEFT) != WALKABLE){
					x = true;
					break;
				}
					explosion.x = (getTilePosition()[0] - j) * 35; explosion.y = getTilePosition()[1] * 35 + 35 / 2 - 35 / 8;
					explosion.w = 35; explosion.h = 35 / 4; break;
				case 2: if (map->checkNextTile({ getTilePosition()[0],getTilePosition()[1] + j - 1 }, BOTTOM) != WALKABLE){
					x = true;
					break;
				}
					explosion.x = getTilePosition()[0] * 35 + 35 / 2 - 35 / 8; explosion.y = (getTilePosition()[1] + j) * 35;
					explosion.w = 35 / 4; explosion.h = 35; break;
				case 3: if (map->checkNextTile({ getTilePosition()[0] + j - 1,getTilePosition()[1]}, RIGHT) != WALKABLE){
					x = true;
					break;
				}
					explosion.x = (getTilePosition()[0] + j) * 35; explosion.y = getTilePosition()[1] * 35 + 35 / 2 - 35 / 8;
					explosion.w = 35; explosion.h = 35 / 4; break;
				}
				setRenderDrawColor(gRenderer, getColor());//Set the good color
				SDL_RenderFillRect(gRenderer, &explosion);
			}
		}
	}
	auto it = particleEmitters.begin();
	while (it != particleEmitters.end()){
		if (!(**it).renderCopy(gRenderer)) {
			it = particleEmitters.erase(it);
		}
		else ++it;
	}

}

///return true if the bomb still exist, or else false
bool Bomb::refresh() {
	if (SDL_GetTicks() > dropTime + lastingTime) {//2 sec before explosion
		if (!explosionTime)
			explode();
		else if (SDL_GetTicks() > explosionTime + 100)//Explosion effect last 100 ms
			return false;
	}
	else if (rand()%10==1){
		std::unique_ptr<ParticleEmitter> particleEmitter{ new ParticleEmitter(getPosition()->x, getPosition()->y, (SDL_GetTicks() - dropTime)/100, 1.5, getColor()) };
		particleEmitters.push_back(std::move(particleEmitter));
	}
	return true;
}

void Bomb::shortTheTime() {
	if (SDL_GetTicks() < dropTime + lastingTime - 80) {
		lastingTime = SDL_GetTicks() + 80 - dropTime;
	}
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
	particleEmitters.clear();
}
