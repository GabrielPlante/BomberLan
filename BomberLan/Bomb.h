#pragma once
#include "Renderable.h"
#include "Map.h"

class Bomb :
	public Renderable
{
public:
	Bomb(int xTile, int yTile, int power, SDL_Renderer* gRenderer, Map* map);
	bool refresh() override;
	void explode();
	~Bomb();
private:
	Map* map;
	Uint32 dropTime;
	int power;
};