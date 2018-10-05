#pragma once
#include <SDL.h>
#include "Bomberman.h"
class Event//Decided not to derive anything from this one to keep thing compact + few event to check
{
public:
	Event();
	~Event();
	bool checkEvent();//Return false if user want to quit
private:
	SDL_Event event;
};

