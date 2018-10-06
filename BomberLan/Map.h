#pragma once
#include "Path.h"
#include "Brick.h"
#include <vector>
#include <memory>
#include "Enum.h"

class Map
{
public:
	Map(SDL_Renderer* gRenderer);
	void renderCopy(SDL_Renderer* gRenderer);
	TileProperty checkNextTile(std::array<int,2> playerTilePosition, Direction direction);
	bool destroyTile(std::array<int,2> tilePosition);
	~Map();
private:
	std::vector<std::unique_ptr<Tiles>> tiles;//Vector of unique_ptr so there is one array for all the tiles (path, brick...)
	SDL_Renderer* gRenderer;
	std::array<std::array<int, 2>, 4> playerPosition;//4 players only
	const int mapSize = 18;//630/35=18
};
