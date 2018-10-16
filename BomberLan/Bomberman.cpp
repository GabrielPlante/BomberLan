#include "Bomberman.h"



Bomberman::Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map, int numPlayer)
	:Renderable(xTile*35+35/2-18/2, yTile*35+35/2-36/2, 18, 36, "Bomberman.bmp", gRenderer)
{
	this->numPlayer = numPlayer;
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
	ITEM item = map->takeItem(getTilePosition());
	if (item == BOMBPLUS) {
		++nbrOfBomb;
	}
	else if (item == POWERPLUS) {
		++bombPower;
	}
	if (numPlayer) {
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		switch (numPlayer) {
		case 1:
			if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_LEFT]
				&& !currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_RIGHT])
				inputDirection = NOT;
			if (currentKeyStates[SDL_SCANCODE_RSHIFT]) dropBomb();
			break;
		case 2:
			if (!currentKeyStates[SDL_SCANCODE_W] && !currentKeyStates[SDL_SCANCODE_A]
				&& !currentKeyStates[SDL_SCANCODE_S] && !currentKeyStates[SDL_SCANCODE_D])
				inputDirection = NOT;
			if (currentKeyStates[SDL_SCANCODE_SPACE]) dropBomb();
			break;
		}
		if (inputDirection != NOT)
			movingDirection = inputDirection;
		move();
	}
	if (!alive) return false;
	return true;
}

void Bomberman::setInput(Direction input) {
	inputDirection = input;
}

//To not move on a bomb, check in move() if the next tile have a bomb on it (every player, every bomb)
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
			std::shared_ptr<Bomb> bomb{ new Bomb(getTilePosition()[0], getTilePosition()[1], bombPower, gRenderer, map) };
			droppedBomb.push_back(std::move(bomb));
		}
	}
}

void Bomberman::die() {
	alive = false;
}

std::vector<std::shared_ptr<Bomb>>* Bomberman::getBombs() {
	return &droppedBomb;
}