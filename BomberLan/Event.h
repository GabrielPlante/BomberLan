#pragma once
#include <SDL.h>
#include "Bomberman.h"

class Event//Decided not to derive anything from this one to keep thing compact + few event to check
{
public:
	Event(std::initializer_list<Bomberman*> activePlayersList);
	~Event();
	bool checkEvent();//Return false if user want to quit
private:
	std::vector<Bomberman*> activePlayers;
	SDL_Event event;
};