#include "Event.h"

Event::Event(std::initializer_list<Bomberman*> activePlayersList)
{
	for (auto it = activePlayersList.begin(); it != activePlayersList.end(); ++it) {
		activePlayers.push_back(*it);
	}
}

bool Event::checkEvent() {
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			return false;
		if (event.type == SDL_KEYDOWN) {
			if (activePlayers.size() == 2){
				switch (event.key.keysym.sym) {
				case SDLK_UP: activePlayers[0]->setInput(TOP); break;
				case SDLK_LEFT: activePlayers[0]->setInput(LEFT); break;
				case SDLK_DOWN: activePlayers[0]->setInput(BOTTOM); break;
				case SDLK_RIGHT: activePlayers[0]->setInput(RIGHT); break;
				case SDLK_z: activePlayers[1]->setInput(TOP); break;
				case SDLK_q: activePlayers[1]->setInput(LEFT); break;
				case SDLK_s: activePlayers[1]->setInput(BOTTOM); break;
				case SDLK_d: activePlayers[1]->setInput(RIGHT); break;
				}
			}
			else if (activePlayers.size() == 1) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
				case SDLK_w: activePlayers[0]->setInput(TOP); break;
				case SDLK_LEFT:
				case SDLK_a: activePlayers[0]->setInput(LEFT); break;
				case SDLK_DOWN:
				case SDLK_s: activePlayers[0]->setInput(BOTTOM); break;
				case SDLK_RIGHT:
				case SDLK_d: activePlayers[0]->setInput(RIGHT); break;
				}
			}
		}
	}
	return true;
}

Event::~Event()
{
}
