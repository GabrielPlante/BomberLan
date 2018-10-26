#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(int x, int y, int nbrOfParticles, float speed, COLOR color, int lifeTime)
{
	for (int i = 0; i != nbrOfParticles; ++i) {
		std::unique_ptr<Particle> particle{ new Particle(x, y, color, speed, lifeTime) };
		particleList.push_back(std::move(particle));
	}
}

bool ParticleEmitter::refresh() {
	if (!particleList.size())
		return false;
	auto it = particleList.begin();
	while (it != particleList.end()){
		if (!(**it).refresh()) {
			particleList.clear();
			break;
		}
		else ++it;
	}
	return true;
}

bool ParticleEmitter::renderCopy(SDL_Renderer* gRenderer) {
	if (!refresh())
		return false;
	for (auto it = particleList.begin(); it != particleList.end(); ++it)
		(**it).Particle::renderCopy(gRenderer);
	return true;
}

ParticleEmitter::~ParticleEmitter()
{
}
