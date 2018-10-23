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
	void setInput(Direction input);
	void move();
	void dropBomb();
	void recenter(Uint16 delta);
	void die();
	std::vector<std::shared_ptr<Bomb>>* getBombs();
private:
	Map* map;
	std::vector<std::shared_ptr<Bomb>> droppedBomb;
	SDL_Renderer* gRenderer;//To drop bomb
	Direction inputDirection = NOT;
	std::array<int, 2> destination;
	int numPlayer;
	float movingSpeed = .2;
	unsigned int nbrOfBomb = 1;
	unsigned int bombPower = 1;
	float positionY;
	float positionX;
	bool alive = true;
	Uint32 timeLastFrame = 0;
};

