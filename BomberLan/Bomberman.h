#pragma once
#include "Renderable.h"
#include "Map.h"
#include "Bomb.h"

class Map;//Because of recursive inclusion
class Bomb;

class Bomberman : public Renderable
{
public:
	Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map, bool isPlayer);
	void renderCopy();
	bool refresh() override;
	void move();
	void dropBomb();
	void die();
	~Bomberman();
private:
	Map* map;
	std::vector<std::unique_ptr<Bomb>> droppedBomb;
	SDL_Renderer* gRenderer;//To drop bomb
	Direction inputDirection = NOT;
	Direction movingDirection = NOT;
	bool isPlayer;
	float movingSpeed = 1 / 100;
	unsigned int nbrOfBomb = 10;
	unsigned int bombPower = 1;
	bool alive = true;
};

