#include "Tiles.h"

Tiles::Tiles(int x, int y, std::string path, SDL_Renderer* gRenderer)
{
	//creating the positon of the rectangle that hold the tile
	position.x = x;
	position.y = y;
	position.w = 35;//The image used as the brick is 35*35
	position.h = 35;

	//Creating the surface holder
	SDL_Surface* loadSurface = SDL_LoadBMP(path.c_str());
	if (loadSurface == nullptr)
		throw std::invalid_argument("Could not load surface, SDL_LoadBMP failed");

	//Creating the texture from the surface
	tileTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
	if (tileTexture == nullptr)
		throw std::runtime_error("SDL_CreateTextureFromSurface failed");
	SDL_FreeSurface(loadSurface);
}

SDL_Texture* Tiles::getTexture() {
	return tileTexture;
}

SDL_Rect* Tiles::getPosition() {
	return &position;
}

Tiles::~Tiles()
{
	SDL_DestroyTexture(tileTexture);
	tileTexture = nullptr;
}
