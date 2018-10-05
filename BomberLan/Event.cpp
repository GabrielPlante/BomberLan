#include "Event.h"

Event::Event()
{
}

bool Event::checkEvent() {
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}

Event::~Event()
{
}
