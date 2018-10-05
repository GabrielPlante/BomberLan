#pragma once
#include <SDL.h>
#include <iostream>
#include <stdexcept>
class Renderable
{
public:
	Renderable(int x, int y, int w, int h, std::string path, SDL_Renderer* gRenderer);
	void renderCopy(SDL_Renderer* gRenderer);
	SDL_Texture* getTexture();
	SDL_Rect* getPosition();
	~Renderable();
protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect position;
};

