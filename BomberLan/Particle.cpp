#include "Particle.h"
#include <stdlib.h>
#include <time.h>

Particle::Particle(int x, int y, COLOR color, float speed, int lifeTime)
	: Rect(x+35/2-2/2, y+35/2-2/2, 2, 2, color)
{
	for (int i = 0; i != colorOffset.size(); ++i) {
		colorOffset[i] = (rand() % 100);//Change the color slightly
	}

	this->lifeTime = lifeTime;

	double randomSpeed = ((rand() % 100)+20)*speed/100;//The random speed adapted to speed
	const double Pi = 3.14159265;
	double direction = rand() % 360;//The random direction
	movingSpeed[0] = cos(direction*Pi / 180)*randomSpeed;//The real moving speed
	movingSpeed[1] = sin(direction*Pi / 180)*randomSpeed;
	positionX = getPosition()->x;
	positionY = getPosition()->y;
}

bool Particle::refresh() {
	if (age > lifeTime)
		return false;
	positionX += movingSpeed[0] * (lifeTime - age)/lifeTime;
	positionY += movingSpeed[1] * (lifeTime - age)/lifeTime;
	applyPosition();
	age++;//Aging is dependant of framerate
	return true;
}

void Particle::renderCopy(SDL_Renderer* gRenderer) {
	int offsetA = 0;
	//if (age > lifeTime - lifeTime / 3) {
		offsetA = age/* - (lifeTime - lifeTime / 3)*/ * (255 / (lifeTime/* - lifeTime / 3*/));
	//}
	setRenderDrawColor(gRenderer, getColor(), colorOffset[0], colorOffset[1], colorOffset[2], offsetA);//Render with the color changed
	SDL_RenderFillRect(gRenderer, getPosition());
}

Particle::~Particle()
{
}
