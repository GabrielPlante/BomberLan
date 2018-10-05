#include "Map.h"

Map::Map(SDL_Renderer* gRenderer)
{
	//Temporary : map full of path
	//630/35=18
	for (int x = 0; x != 18; ++x) {
		for (int y = 0; y != 18; ++y) {
			std::unique_ptr<Tiles> tile(new Path(x * 35, y * 35, gRenderer));
			tiles.push_back(std::move(tile));
		}
	}
}

//To render the whole map on the screen, must be called each frame
void Map::renderCopy(SDL_Renderer* gRenderer) {
	for (auto it = tiles.begin(); it != tiles.end();++it) {
		(**it).renderCopy(gRenderer);
	}
}

Map::~Map()
{
}
