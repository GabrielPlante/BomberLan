#pragma once
#include <SDL.h>
#include <iostream>
#include <stdexcept>
#include <array>
class Renderable
{
public:
	Renderable(int x, int y, int w, int h, std::string path, SDL_Renderer* gRenderer);
	void renderCopy(SDL_Renderer* gRenderer);
	virtual bool refresh() = 0;
	std::array<int, 2> getTilePosition();
	SDL_Texture* getTexture();
	SDL_Rect* getPosition();
	~Renderable();
private:
	SDL_Texture* texture = nullptr;
protected:
	SDL_Rect position;
};

