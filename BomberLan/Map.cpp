#include "Map.h"
#include <stdlib.h>
#include <time.h>

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
	srand(time(NULL));
}

void Map::addPlayers(std::array<Bomberman*, 4> players) {
	this->players = players;
}

//To render the whole map on the screen, must be called each frame
void Map::renderCopy(SDL_Renderer* gRenderer) {
	for (auto it = tiles.begin(); it != tiles.end();++it) {
		(**it).renderCopy(gRenderer);
	}
	for (auto it = items.begin(); it != items.end(); ++it)
		(**it).renderCopy(gRenderer);
}

TileProperty Map::checkNextTile(std::array<int,2> playerTilePosition, Direction direction) {
	int x = -1;
	switch (direction) {//Transform from {x, y} to position in array for every direction
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
	case NOT:
		if (playerTilePosition[0] >= 0 && playerTilePosition[0] < mapSize && playerTilePosition[1] >= 0 && playerTilePosition[1] < mapSize)
			x = playerTilePosition[0] + playerTilePosition[1] * mapSize;
	}
	if (x == -1) return INEXISTANT;
	for (auto it = players.begin(); it != players.end(); ++it) {//Check if the next tile is a bomb
		for (auto id = (**it).getBombs()->begin(); id != (**it).getBombs()->end(); ++id)
			if ((**id).getTilePosition()[0] + (**id).getTilePosition()[1]*mapSize == x)
				return BOMB;
	}
	if (tiles[x]->isWalkable()) return WALKABLE;
	else if (tiles[x]->isDestroyable()) return DESTROYABLE;
	else return NOTHING;
}

///Return the item on the ground and delete it, or return NOITEM if there isn't an item on the ground
ITEM Map::takeItem(std::array<int, 2> tilePosition) {
	for (auto it = items.begin(); it != items.end(); ++it)
		if ((**it).getTilePosition() == tilePosition) {
			ITEM item = (**it).getItem();
			items.erase(it);
			return item;
		}
	return NOITEM;
}

///Return true if the explosion stop at that tile (aka the tile is a brick or a wall)
bool Map::destroyTile(std::array<int, 2> tilePosition) {
	for (auto it = players.begin(); it != players.end(); ++it) {
		if ((**it).getTilePosition() == tilePosition)
			(**it).die();
		std::vector<std::shared_ptr<Bomb>>* bombs = (**it).getBombs();
		for (auto id = bombs->begin(); id != bombs->end(); ++id) {
			if ((**id).getTilePosition() == tilePosition)
				(**id).shortTheTime();
		}
	}
	if (tilePosition[0] >= 0 && tilePosition[0] < mapSize && tilePosition[1] >= 0 && tilePosition[1] < mapSize) {//Replace the tile
		takeItem(tilePosition);
		if (tiles[tilePosition[0] + tilePosition[1] * mapSize]->isDestroyable()) {//If it's a brick
			tiles[tilePosition[0] + tilePosition[1] * mapSize] = std::unique_ptr<Tiles>{ new Path(tilePosition[0] * 35,tilePosition[1] * 35,gRenderer) };
			int random = rand() % 3;//Random for item drop
			if (random == 0) {//Bomb plus item
				std::unique_ptr<Item> item(new Item(tilePosition[0] * 35, tilePosition[1] * 35, "BombPlus.bmp", gRenderer, BOMBPLUS));
				items.push_back(std::move(item));
			}
			else if (random == 1){//Power plus item
				std::unique_ptr<Item> item(new Item(tilePosition[0] * 35, tilePosition[1] * 35, "Power.bmp", gRenderer, POWERPLUS));
				items.push_back(std::move(item));
			}
			return true;
		}
		if (!tiles[tilePosition[0] + tilePosition[1] * mapSize]->isWalkable())//Check for invicible block
			return true;
	}
	return false;
}

Map::~Map()
{
}
