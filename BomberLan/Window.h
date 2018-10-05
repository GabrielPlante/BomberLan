#pragma once
#include "Map.h"
#include "Event.h"

class Window
{
public:
	Window(const int screenWith, const int screenHeight);
	void refresh();
	~Window();
private:
	SDL_Window* gWindow{ nullptr };
	SDL_Renderer* gRenderer{ nullptr };
	std::unique_ptr<Map> map;//Unique_ptr so it don't need to be initialized know
	std::vector<std::unique_ptr<Bomberman>> listeJoueur;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
};

