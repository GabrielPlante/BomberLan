#pragma once
#include <SDL.h>
#include <iostream>
#include <stdexcept>
#include <array>
#include "Enum.h"
class Rect
{
public:
	Rect(int x, int y, int w, int h, COLOR color = BLACK);
	virtual bool refresh() = 0;
	virtual void renderCopy(SDL_Renderer* gRenderer);
	void setRenderDrawColor(SDL_Renderer* gRenderer, COLOR color);
	std::array<int, 2> getTilePosition();
	SDL_Rect* getPosition();
	COLOR getColor();
	~Rect();
protected:
	SDL_Rect position;
private:
	COLOR color;
};