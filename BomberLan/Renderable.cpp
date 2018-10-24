#include "Renderable.h"

Renderable::Renderable(int x, int y, int w, int h, std::string path, SDL_Renderer* gRenderer)
	: Rect(x, y, w, h)
{
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
	SDL_RenderCopy(gRenderer, texture, nullptr, getPosition());
}

SDL_Texture* Renderable::getTexture() {
	return texture;
}

Renderable::~Renderable()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
