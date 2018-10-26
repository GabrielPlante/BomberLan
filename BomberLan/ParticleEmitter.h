#pragma once
#include "Particle.h"
#include <vector>
class ParticleEmitter
{
public:
	ParticleEmitter(int x, int y, int nbrOfParticles, float speed, COLOR color = BLACK, int lifeTime = 30);
	bool renderCopy(SDL_Renderer* gRenderer);
	~ParticleEmitter();
private:
	bool refresh();
	std::vector<std::unique_ptr<Particle>> particleList;
};

