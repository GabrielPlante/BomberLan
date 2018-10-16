#pragma once
#include "Renderable.h"
#include "Map.h"

class Map;//Because of recursive inclusion

class Bomb :
	public Renderable
{
public:
	Bomb(int xTile, int yTile, int power, SDL_Renderer* gRenderer, Map* map);
	void renderCopy(SDL_Renderer* gRenderer);
	bool refresh() override;
	void shortTheTime();
	void explode();
	~Bomb();
private:
	Map* map;
	Uint32 dropTime;
	Uint32 explosionTime = 0;
	bool exploded = false;
	int lastingTime = 2000;
	int power;
};