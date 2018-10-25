#include "Rect.h"

Rect::Rect(int x, int y, int w, int h, COLOR color)
{
	//creating the positon of the rectangle that hold the texture
	position.x = x;//Position of the top left of the image
	position.y = y;
	position.w = w;//Must be the size of the image or it will resize it
	position.h = h;
	this->color = color;
}

void Rect::renderCopy(SDL_Renderer* gRenderer) {
	setRenderDrawColor(gRenderer, color);
	SDL_RenderFillRect(gRenderer, &position);
}

void Rect::setRenderDrawColor(SDL_Renderer* gRenderer, COLOR color, int offsetR, int offsetG, int offsetB, int offsetA) {
	switch (color)
	{//Set the good code for each color
	case RED:
		SDL_SetRenderDrawColor(gRenderer, 255-offsetR, 0+offsetG, 0+offsetB, 255-offsetA);
		break;
	case GREEN:
		SDL_SetRenderDrawColor(gRenderer, 0+offsetR, 255-offsetG, 0+offsetG, 255-offsetA);
		break;
	case BLUE:
		SDL_SetRenderDrawColor(gRenderer, 0+offsetR, 0+offsetG, 255-offsetG, 255-offsetA);
		break;
	case YELLOW:
		SDL_SetRenderDrawColor(gRenderer, 255-offsetR, 255-offsetG, 0+offsetG, 255-offsetA);
		break;
	case ORANGE:
		SDL_SetRenderDrawColor(gRenderer, 255-offsetR, 160+offsetG, 0+offsetG, 255-offsetA);
		break;
	case BLACK:
		SDL_SetRenderDrawColor(gRenderer, 0+offsetR, 0+offsetG, 0+offsetG, 255-offsetA);
		break;
	case WHITE:
		SDL_SetRenderDrawColor(gRenderer, 255-offsetR, 255-offsetG, 255-offsetG, 255-offsetA);
		break;
	case PURPLE:
		SDL_SetRenderDrawColor(gRenderer, 128+offsetR, 0+offsetG, 128+offsetG, 255-offsetA);
	}
}

std::array<int, 2> Rect::getTilePosition() {
	return std::array<int, 2> {(position.x + position.w / 2) / 35, (position.y + position.h / 2) / 35};
}

SDL_Rect* Rect::getPosition() {
	return &position;
}

///Apply the float position to the real position of the object
void Rect::applyPosition() {
	position.x = static_cast<int>(positionX);
	position.y = static_cast<int>(positionY);
}

COLOR Rect::getColor() {
	return color;
}

Rect::~Rect()
{
}
