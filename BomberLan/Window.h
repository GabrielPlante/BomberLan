#pragma once
#include <SDL.h>
#include <stdexcept>

class Window
{
public:
	Window(const int screenWith, const int screenHeight);
	void clear();
	void update();
	SDL_Renderer* getRenderer();
	~Window();
private:
	SDL_Window* gWindow{ nullptr };
	SDL_Renderer* gRenderer{ nullptr };
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
};

