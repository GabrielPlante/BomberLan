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
	void setRenderDrawColor(SDL_Renderer* gRenderer, COLOR color, int offsetR = 0, int offsetG = 0, int offsetB = 0);
	std::array<int, 2> getTilePosition();
	SDL_Rect* getPosition();
	void setPosition(int x, int y);
	COLOR getColor();
	~Rect();
protected:
	float positionX;
	float positionY;
private:
	SDL_Rect position;
	COLOR color;
};