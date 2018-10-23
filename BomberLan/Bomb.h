#pragma once
#include "Rect.h"
#include "Map.h"

class Map;//Because of recursive inclusion

class Bomb :
	public Rect
{
public:
	Bomb(int xTile, int yTile, int power, Map* map, COLOR color);
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
	COLOR color;
};