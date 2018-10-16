#pragma once
#include "Renderable.h"
#include "Map.h"
#include "Bomb.h"

class Map;//Because of recursive inclusion
class Bomb;

class Bomberman : public Renderable
{
public:
	Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map, int numPlayer = 0);
	void renderCopy();
	bool refresh() override;
	void move();
	void dropBomb();
	void die();
	std::vector<std::shared_ptr<Bomb>>* getBombs();
private:
	Map* map;
	std::vector<std::shared_ptr<Bomb>> droppedBomb;
	SDL_Renderer* gRenderer;//To drop bomb
	Direction inputDirection = NOT;
	Direction movingDirection = NOT;
	int numPlayer;
	int movingSpeed = 1 ;
	unsigned int nbrOfBomb = 1;
	unsigned int bombPower = 1;
	bool alive = true;
};

