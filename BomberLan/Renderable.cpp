#include "Renderable.h"

Renderable::Renderable(int x, int y, int w, int h, std::string path, SDL_Renderer* gRenderer)
{
	//creating the positon of the rectangle that hold the texture
	position.x = x;//Position of the top left of the image
	position.y = y;
	position.w = w;//Must be the size of the image or it will resize it
	position.h = h;

	//Creating the temporary surface holder
	SDL_Surface* loadSurface = SDL_LoadBMP(path.c_str());
	if (loadSurface == nullptr)
		throw std::invalid_argument("Could not load surface, SDL_LoadBMP failed");

	//Creating the texture from the surface
	texture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
	if (texture == nullptr)
		throw std::runtime_error("SDL_CreateTextureFromSurface failed");
	SDL_FreeSurface(loadSurface);
}

void Renderable::renderCopy(SDL_Renderer* gRenderer) {
	SDL_RenderCopy(gRenderer, texture, nullptr, &position);
}

SDL_Texture* Renderable::getTexture() {
	return texture;
}

SDL_Rect* Renderable::getPosition() {
	return &position;
}

Renderable::~Renderable()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
