#pragma once
#include "Rect.h"
#include "Map.h"
#include "Particle.h"
#include <list>

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
	std::list<std::unique_ptr<Particle>> particleList;
	Uint32 dropTime;
	Uint32 explosionTime = 0;
	bool exploded = false;
	int lastingTime = 2000;
	int power;
};