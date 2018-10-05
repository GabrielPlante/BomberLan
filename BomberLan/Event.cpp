#include "Event.h"

Event::Event()
{
}

bool Event::checkEvent(Bomberman* player) {
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return false;
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_z:
			case SDLK_UP: player->move(TOP); break;
			case SDLK_q:
			case SDLK_LEFT: player->move(LEFT); break;
			case SDLK_s:
			case SDLK_DOWN: player->move(BOTTOM); break;
			case SDLK_d:
			case SDLK_RIGHT: player->move(RIGHT); break;
			}
		}
	}
	return true;
}

Event::~Event()
{
}
