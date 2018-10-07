#include "Map.h"

Map::Map(SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	//Temporary : map full of path
	for (int y = 0; y != mapSize; ++y) {//Creating the map left to right and top to bottom (in this order)
		for (int x = 0; x != mapSize; ++x) {
			if (x == 4 || x == 13 || y == 4 || y == 13) {
				std::unique_ptr<Tiles> tile(new Path(x * 35, y * 35, gRenderer));
				tiles.push_back(std::move(tile));
			}
			else {
				std::unique_ptr<Tiles> tile(new Brick(x * 35, y * 35, gRenderer));
				tiles.push_back(std::move(tile));
			}
		}
	}
}

void Map::addPlayers(std::array<Bomberman*, 4> players) {
	this->players = players;
}

//To render the whole map on the screen, must be called each frame
void Map::renderCopy(SDL_Renderer* gRenderer) {
	for (auto it = tiles.begin(); it != tiles.end();++it) {
		(**it).renderCopy(gRenderer);
	}
}

TileProperty Map::checkNextTile(std::array<int,2> playerTilePosition, Direction direction) {
	int x = -1;
	switch (direction) {
	case TOP:
		if (playerTilePosition[1] != 0)
			x = playerTilePosition[0] + (playerTilePosition[1] - 1) * mapSize;
		break;
	case LEFT:
		if (playerTilePosition[0] != 0)
			x = playerTilePosition[0] - 1 + playerTilePosition[1] * mapSize;
		break;
	case BOTTOM:
		if (playerTilePosition[1] != mapSize - 1)
			x = playerTilePosition[0] + (playerTilePosition[1] + 1) * mapSize;
		break;
	case RIGHT:
		if (playerTilePosition[0] != mapSize - 1)
			x = playerTilePosition[0] + 1 + playerTilePosition[1] * mapSize;
		break;
	}
	if (x == -1) return INEXISTANT;
	else if (tiles[x]->isWalkable()) return WALKABLE;
	else if (tiles[x]->isDestroyable()) return DESTROYABLE;
	else return NOTHING;
}

bool Map::destroyTile(std::array<int, 2> tilePosition) {
	for (auto it = players.begin(); it != players.end(); ++it)
		if ((**it).getTilePosition() == tilePosition)
			(**it).die();
	if (tilePosition[0] >= 0 && tilePosition[0] < mapSize && tilePosition[1] >= 0 && tilePosition[1] < mapSize) {
		if (tiles[tilePosition[0] + tilePosition[1] * mapSize]->isDestroyable()) {
			tiles[tilePosition[0] + tilePosition[1] * mapSize] = std::unique_ptr<Tiles>{ new Path(tilePosition[0] * 35,tilePosition[1] * 35,gRenderer) };
			return true;
		}
	}
	return false;
}

Map::~Map()
{
}
