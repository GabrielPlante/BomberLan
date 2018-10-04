#pragma once
#include <SDL.h>
#include <iostream>
#include <stdexcept>

class Tiles
{
public:
	Tiles(int x, int y, std::string path, SDL_Renderer* gRenderer);
	SDL_Texture* getTexture();
	SDL_Rect* getPosition();
	virtual bool isWalkable() = 0;
	virtual bool isDestroyable() = 0;
	~Tiles();
protected:
	SDL_Texture* tileTexture = nullptr;
	SDL_Rect position;
};
