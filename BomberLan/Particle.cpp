#include "Particle.h"
#include <stdlib.h>
#include <time.h>

Particle::Particle(int x, int y, COLOR color)
	: Rect(x+35/2-2/2, y+35/2-2/2, 2, 2, color)
{
	for (int i = 0; i != colorOffset.size(); ++i) {
		colorOffset[i] = (rand() % 100);//Change the color slightly
	}

	float speed = (rand() % 100) / 200.0 + 0.03;//Speed

	const float Pi = 3.14159265;
	float direction = rand() % 360;
	movingSpeed[0] = cos(direction*Pi / 180)*speed;
	movingSpeed[1] = sin(direction*Pi / 180)*speed;
	positionX = getPosition()->x;
	positionY = getPosition()->y;
}

bool Particle::refresh() {
	if (age > lifeTime)
		return false;
	positionX += movingSpeed[0] * (lifeTime - age)/10;
	positionY += movingSpeed[1] * (lifeTime - age)/10;
	setPosition(positionX, positionY);
	age++;//Aging is dependant of framerate
	return true;
}

void Particle::renderCopy(SDL_Renderer* gRenderer) {
	setRenderDrawColor(gRenderer, getColor(), colorOffset[0], colorOffset[1], colorOffset[2]);//Render with the color changed
	SDL_RenderFillRect(gRenderer, getPosition());
}

Particle::~Particle()
{
}
