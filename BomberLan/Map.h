#pragma once
#include "Path.h"
#include "Brick.h"
#include "Wall.h"
#include <vector>
#include <memory>
#include "Item.h"
#include "Bomberman.h"

class Bomberman;
class Bomb;

class Map
{
public:
	Map(SDL_Renderer* gRenderer);
	void addPlayers(std::array<Bomberman*, 4> players);
	void renderCopy(SDL_Renderer* gRenderer);
	TileProperty checkNextTile(std::array<int,2> playerTilePosition, Direction direction = NOT);
	ITEM takeItem(std::array<int, 2> tilePosition);
	bool destroyTile(std::array<int,2> tilePosition);
	~Map();
private:
	std::vector<std::unique_ptr<Tiles>> tiles;//Vector of unique_ptr so there is one array for all the tiles (path, brick...)
	std::vector<std::unique_ptr<Item>> items;
	SDL_Renderer* gRenderer;
	std::array<Bomberman*, 4> players;
	const int mapSize = 18;//630/35=18
};
