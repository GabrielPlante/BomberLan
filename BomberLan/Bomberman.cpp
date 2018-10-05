#include "Bomberman.h"



Bomberman::Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map)
	:Renderable(xTile*35+35/2-18/2, yTile*35+35/2-36/2, 18, 36, "Bomberman.bmp", gRenderer)
{
	this->map = map;
}

std::array<int, 2> Bomberman::getTilePosition() {
	return std::array<int, 2> {(position.x + 18 / 2 - 35 / 2) / 35, (position.y + 36 / 2 - 35 / 2) / 35};
}

void Bomberman::move(Direction direction) {
	if (map->checkNextTile(getTilePosition(), direction)) {
		switch (direction) {
		case TOP: position.y -= 35; break;
		case LEFT: position.x -= 35; break;
		case BOTTOM: position.y += 35; break;
		case RIGHT: position.x += 35; break;
		}
	}
}

Bomberman::~Bomberman()
{
}
