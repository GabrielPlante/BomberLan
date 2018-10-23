#include "Bomberman.h"



Bomberman::Bomberman(int xTile, int yTile, SDL_Renderer* gRenderer, Map* map, int numPlayer)
	:Renderable(xTile*35+35/2-18/2, yTile*35+35/2-36/2, 18, 36, "Bomberman.bmp", gRenderer)
{
	this->numPlayer = numPlayer;
	this->map = map;
	this->gRenderer = gRenderer;
	positionX = getPosition()->x;
	positionY = getPosition()->y;
	destination = getTilePosition();
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
		case 1://If it's the first player...
			if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_LEFT]
				&& !currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_RIGHT])
				inputDirection = NOT;//Only check if the player is not pressing any key
			if (currentKeyStates[SDL_SCANCODE_RSHIFT]) dropBomb();//Or is dropping a bomb
			break;
		case 2:
			if (!currentKeyStates[SDL_SCANCODE_W] && !currentKeyStates[SDL_SCANCODE_A]
				&& !currentKeyStates[SDL_SCANCODE_S] && !currentKeyStates[SDL_SCANCODE_D])
				inputDirection = NOT;
			if (currentKeyStates[SDL_SCANCODE_SPACE]) dropBomb();
			break;
		}
		move();
	}
	if (!alive) return false;
	return true;
}

void Bomberman::setInput(Direction input) {
	inputDirection = input;
}

///Move a bomberman
void Bomberman::move() {
	Uint16 delta = SDL_GetTicks() - timeLastFrame;//To make movement speed independant of framerate
	timeLastFrame = SDL_GetTicks();
	if (inputDirection != NOT && map->checkNextTile(getTilePosition(), inputDirection) == WALKABLE) {
		switch (inputDirection)//If the player want to move
		{//Every direction
		case TOP: destination = getTilePosition(); destination[1] = getTilePosition()[1] - 1; break;//Don't accumulate move
		case LEFT: destination = getTilePosition(); destination[0] = getTilePosition()[0] - 1; break;
		case BOTTOM: destination = getTilePosition(); destination[1] = getTilePosition()[1] + 1; break;
		case RIGHT: destination = getTilePosition(); destination[0] = getTilePosition()[0] + 1; break;
		}
		if (inputDirection == TOP || inputDirection == BOTTOM) {//Recenter if the player change direction
			if (getTilePosition()[0] * 35 + 35 / 4 >= getPosition()->x)
				positionX += movingSpeed * delta;
			if (getTilePosition()[0] * 35 + 35 / 4 <= getPosition()->x)
				positionX -= movingSpeed * delta;
		}
		else if (inputDirection == LEFT || inputDirection == RIGHT) {
			if (getTilePosition()[1] * 35 - 35 / 4 >= getPosition()->y)
				positionY += movingSpeed * delta;
			if (getTilePosition()[1] * 35 - 35 / 4 <= getPosition()->y)
				positionY -= movingSpeed * delta;
		}
	}
	else
		recenter(delta);//If the player is not moving, recenter him
	if (getTilePosition() != destination) {//Apply the movement to the float
		positionX += (destination[0] - getTilePosition()[0])*movingSpeed*delta;
		positionY += (destination[1] - getTilePosition()[1])*movingSpeed*delta;
	}

	position.x = positionX;//Apply the movement to the real position
	position.y = positionY;
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

void Bomberman::recenter(Uint16 delta) {//Move the player toward the center of the tile
	if (getTilePosition()[0] * 35 + 35/4 >= getPosition()->x)
		positionX += movingSpeed * delta;
	if (getTilePosition()[0] * 35 + 35/4 <= getPosition()->x)
		positionX -= movingSpeed * delta;
	if (getTilePosition()[1] * 35 - 35/4 >= getPosition()->y)
		positionY += movingSpeed * delta;
	if (getTilePosition()[1] * 35 - 35/4 <= getPosition()->y)
		positionY -= movingSpeed * delta;
}

void Bomberman::die() {//So simple
	alive = false;
}

std::vector<std::shared_ptr<Bomb>>* Bomberman::getBombs() {
	return &droppedBomb;
}