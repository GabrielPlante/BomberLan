#include "Bomberman.h"



Bomberman::Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map)
	:Renderable(xTile*35+35/2-18/2, yTile*35+35/2-36/2, 18, 36, "Bomberman.bmp", gRenderer)
{
	this->map = map;
	this->gRenderer = gRenderer;
	nbrOfBomb = 1;
	bombPower = 10;
}

void Bomberman::renderCopy() {
	for (auto it = droppedBomb.begin(); it != droppedBomb.end(); ++it) {
		(**it).renderCopy(gRenderer);
	}
	Renderable::renderCopy(gRenderer);
}

bool Bomberman::refresh() {
	for (int i = 0; i != droppedBomb.size(); ++i) {//Couldn't get it to work nicely with iterator
		if (!droppedBomb[i]->refresh()) {
			droppedBomb.erase(droppedBomb.begin()+i);
			--i;
		}
	}
	return true;
}

void Bomberman::move(Direction direction) {
	if (map->checkNextTile(getTilePosition(), direction) == WALKABLE) {
		switch (direction) {
		case TOP: position.y -= 35; break;
		case LEFT: position.x -= 35; break;
		case BOTTOM: position.y += 35; break;
		case RIGHT: position.x += 35; break;
		}
	}
}

void Bomberman::dropBomb() {
	bool drop = true;
	for (auto it = droppedBomb.begin(); it != droppedBomb.end(); ++it)
		if ((**it).getTilePosition() == getTilePosition())
			drop = false;
	if (drop) {
		std::unique_ptr<Bomb> bomb{ new Bomb(getTilePosition()[0], getTilePosition()[1], bombPower, gRenderer, map) };
		droppedBomb.push_back(std::move(bomb));
	}
}

Bomberman::~Bomberman()
{
}
