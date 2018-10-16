#include "Item.h"



Item::Item(int x, int y, std::string path, SDL_Renderer* gRenderer, ITEM item)
	: Renderable(x, y, 35, 35, path, gRenderer)
{
	this->item = item;
}

ITEM Item::getItem() {
	return item;
}

bool Item::refresh() {
	return true;
}

Item::~Item()
{
}
