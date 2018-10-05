#pragma once
#include "Renderable.h"
#include "Map.h"
#include <array>
class Map;//Because Map.h and Bomberman.h include eachother
enum Direction;//Same
class Bomberman : public Renderable
{
public:
	Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map);
	std::array<int, 2> getTilePosition();
	void move(Direction direction);
	~Bomberman();
private:
	Map* map;
};

