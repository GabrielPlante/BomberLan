#pragma once
#include "Renderable.h"
#include "Map.h"
#include "Bomb.h"

class Map;//Because of recursive inclusion
class Bomb;

class Bomberman : public Renderable
{
public:
	Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map);
	void renderCopy();
	bool refresh() override;
	void move(Direction direction);
	void dropBomb();
	void die();
	~Bomberman();
private:
	Map* map;
	std::vector<std::unique_ptr<Bomb>> droppedBomb;
	SDL_Renderer* gRenderer;//To drop bomb
	int nbrOfBomb = 1;
	int bombPower = 1;
	bool alive = true;
};

