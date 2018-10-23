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

void Rect::setRenderDrawColor(SDL_Renderer* gRenderer, COLOR color) {
	switch (color)
	{//Set the good code for each color
	case RED:
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		break;
	case GREEN:
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		break;
	case BLUE:
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		break;
	case YELLOW:
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
		break;
	case ORANGE:
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 160, 0x00, 0xFF);
		break;
	case BLACK:
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		break;
	case WHITE:
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		break;
	}
}

std::array<int, 2> Rect::getTilePosition() {
	return std::array<int, 2> {(position.x + position.w / 2) / 35, (position.y + position.h / 2) / 35};
}

SDL_Rect* Rect::getPosition() {
	return &position;
}

COLOR Rect::getColor() {
	return color;
}

Rect::~Rect()
{
}
