#pragma once
#include "Rect.h"
class Renderable : public Rect
{
public:
	Renderable(int x, int y, int w, int h, std::string path, SDL_Renderer* gRenderer);
	void renderCopy(SDL_Renderer* gRenderer) override;
	SDL_Texture* getTexture();
	~Renderable();
private:
	SDL_Texture* texture = nullptr;
};

