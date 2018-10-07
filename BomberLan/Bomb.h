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
	bool explode();
	~Bomb();
private:
	Map* map;
	Uint32 dropTime;
	bool exploded = false;
	int power;
};