#pragma once
#include <SDL.h>
#include <iostream>
#include <stdexcept>
#include "Map.h"

class Window
{
public:
	Window(const int screenWith, const int screenHeight);
	void refresh();
	bool loadMedia();
	~Window();
private:
	SDL_Window* gWindow{ nullptr };
	SDL_Renderer* gRenderer{ nullptr };
	Map map{};
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
};

