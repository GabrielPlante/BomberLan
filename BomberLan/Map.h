#pragma once
#include "Path.h"
#include "Brick.h"
#include <vector>
#include <memory>
#include "Bomberman.h"
#include "Enum.h"

class Bomberman;
class Map
{
public:
	Map(SDL_Renderer* gRenderer);
	void renderCopy(SDL_Renderer* gRenderer);
	bool checkNextTile(std::array<int,2> playerTilePosition, Direction direction);
	~Map();
private:
	std::vector<std::unique_ptr<Tiles>> tiles;//Vector of unique_ptr so there is one array for all the tiles (path, brick...)
	const int mapSize = 18;//630/35=18
	};
