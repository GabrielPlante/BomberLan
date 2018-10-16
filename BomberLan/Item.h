#pragma once
#include "Renderable.h"
#include "Enum.h"
class Item :
	public Renderable
{
public:
	Item(int x, int y, std::string path, SDL_Renderer* gRenderer, ITEM item);
	ITEM getItem();
	bool refresh() override;
	~Item();
private:
	ITEM item;
};

