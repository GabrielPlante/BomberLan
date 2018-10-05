#include "Tiles.h"

Tiles::Tiles(int x, int y, std::string path, SDL_Renderer* gRenderer)
	: Renderable(x, y, 35, 35, path, gRenderer)
{

}


Tiles::~Tiles()
{
}
