#pragma once
#include "Renderable.h"
class Bomb :
	public Renderable
{
public:
	Bomb(int xTile, int yTile, int power, SDL_Renderer* gRenderer);
	bool refresh() override;
	void explode();
	~Bomb();
private:
	Uint32 dropTime;
	int power;
};

