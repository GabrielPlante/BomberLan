#include "Event.h"

Event::Event()
{
}

bool Event::checkEvent() {
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			return false;
	}
	return true;
}

Event::~Event()
{
}
