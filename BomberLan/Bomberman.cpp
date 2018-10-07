#include "Bomberman.h"



Bomberman::Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map, bool isPlayer)
	:Renderable(xTile*35+35/2-18/2, yTile*35+35/2-36/2, 18, 36, "Bomberman.bmp", gRenderer)
{
	this->isPlayer = isPlayer;
	this->map = map;
	this->gRenderer = gRenderer;
}

void Bomberman::renderCopy() {
	for (auto it = droppedBomb.begin(); it != droppedBomb.end(); ++it) {
		(**it).renderCopy(gRenderer);
	}
	if (alive)
		Renderable::renderCopy(gRenderer);
}

bool Bomberman::refresh() {
	for (int i = 0; i != droppedBomb.size(); ++i) {//Couldn't get it to work nicely with iterator
		if (!droppedBomb[i]->refresh()) {
			droppedBomb.erase(droppedBomb.begin()+i);
			--i;
		}
	}
	if (isPlayer) {
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_UP]) inputDirection = TOP;
		else if (currentKeyStates[SDL_SCANCODE_LEFT]) inputDirection = LEFT;
		else if (currentKeyStates[SDL_SCANCODE_DOWN]) inputDirection = BOTTOM;
		else if (currentKeyStates[SDL_SCANCODE_RIGHT]) inputDirection = RIGHT;
		else inputDirection = NOT;
		if (currentKeyStates[SDL_SCANCODE_SPACE]) dropBomb();
		if (inputDirection != NOT)
			movingDirection = inputDirection;
		move();
	}
	if (!alive) return false;
	return true;
}

void Bomberman::move() {
	if (inputDirection != NOT && map->checkNextTile(getTilePosition(), movingDirection) == WALKABLE) {//If the player walk freely
		switch (movingDirection) {
		case TOP: position.y -= movingSpeed; break;
		case LEFT: position.x -= movingSpeed; break;
		case BOTTOM: position.y += movingSpeed; break;
		case RIGHT: position.x += movingSpeed; break;
		}
	}
	else if (inputDirection != NOT) inputDirection = NOT;//So you can enter a tile where the next one is non walkable
	//To recenter the player and to make "one tap to move" possible
	if (position.y > getTilePosition()[1] * 35 && inputDirection != TOP && inputDirection != BOTTOM) {
		if (inputDirection == NOT && movingDirection == BOTTOM) position.y+=movingSpeed;
		else {
			position.y-=movingSpeed; movingDirection = NOT;
		}
	}
	else if (position.x - position.w / 2 > getTilePosition()[0] * 35 && inputDirection != LEFT && inputDirection != RIGHT) {
		if (inputDirection == NOT && movingDirection == RIGHT) position.x+=movingSpeed;
		else {
			position.x-=movingSpeed; movingDirection = NOT;
		}
	}
	else if (position.y < getTilePosition()[1] * 35 && inputDirection != TOP && inputDirection != BOTTOM) {
		if (inputDirection == NOT && movingDirection == TOP) position.y-=movingSpeed;
		else {
			position.y+=movingSpeed; movingDirection = NOT;
		}
	}
	else if (position.x - position.w / 2 < getTilePosition()[0] * 35 && inputDirection != LEFT && inputDirection != RIGHT) {
		if (inputDirection == NOT && movingDirection == LEFT) position.x-=movingSpeed;
		else {
			position.x+=movingSpeed; movingDirection = NOT;
		}
	}
	else if (inputDirection == NOT)
		movingDirection = NOT;
}

void Bomberman::dropBomb() {
	if (alive && nbrOfBomb > droppedBomb.size()) {//The player need to be alive and have bomb in stock
		bool drop = true;
		for (auto it = droppedBomb.begin(); it != droppedBomb.end(); ++it)//The tile need to be clear of bomb
			if ((**it).getTilePosition() == getTilePosition())
				drop = false;
		if (drop) {
			std::unique_ptr<Bomb> bomb{ new Bomb(getTilePosition()[0], getTilePosition()[1], bombPower, gRenderer, map) };
			droppedBomb.push_back(std::move(bomb));
		}
	}
}

void Bomberman::die() {
	alive = false;
}

Bomberman::~Bomberman()
{
}
