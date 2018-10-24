#pragma once
#include "Rect.h"
#include <math.h>
class Particle : public Rect
{
public:
	Particle(int x, int y, COLOR color);
	~Particle();
	bool refresh() override;
	void renderCopy(SDL_Renderer* gRenderer) override;
private:
	const int lifeTime = 30;
	int age = 0;
	std::array<float, 2> movingSpeed;
	std::array<int, 3> colorOffset;
};

