#include "Map.h"

Map::Map(SDL_Renderer* gRenderer)
{
	//Temporary : map full of path
	for (int x = 0; x != mapSize; ++x) {
		for (int y = 0; y != mapSize; ++y) {
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

//To render the whole map on the screen, must be called each frame
void Map::renderCopy(SDL_Renderer* gRenderer) {
	for (auto it = tiles.begin(); it != tiles.end();++it) {
		(**it).renderCopy(gRenderer);
	}
}

bool Map::checkNextTile(std::array<int,2> playerTilePosition, Direction direction) {
	switch (direction) {
	case TOP: return (playerTilePosition[1] != 0 && tiles[playerTilePosition[0]+(playerTilePosition[1]-1)*(mapSize)]->isWalkable());//if the player is not on the top line of the map && the top tile is walkable
	case LEFT: return (playerTilePosition[0] != 0 && tiles[playerTilePosition[0]-1+playerTilePosition[1]*mapSize]->isWalkable());//not on the left side of the map && the left tile is walkable
	case BOTTOM: return (playerTilePosition[1] != mapSize - 1 && tiles[playerTilePosition[0]+(playerTilePosition[1]+1)*(mapSize)]->isWalkable());//...
	case RIGHT: return (playerTilePosition[0] != mapSize - 1 && tiles[playerTilePosition[0]+1+playerTilePosition[1]*mapSize]->isWalkable());
	}
	return false;
}

Map::~Map()
{
}
