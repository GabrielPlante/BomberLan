#include "Window.h"

Window::Window(const int screenWith, const int screenHeight)
{
	SCREEN_HEIGHT = screenHeight;
	SCREEN_WIDTH = screenWith;

	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL_INIT_VIDEO failed");
	//Create window
	gWindow = SDL_CreateWindow("BomberLan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr)
		throw std::runtime_error("SDL_CreateWindow failed");
	//Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr)
		throw std::runtime_error("SDL_CreateRenderer failed");
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

	//Start map
	map = std::unique_ptr<Map>(new Map(gRenderer));

	//Create player (will change)
	std::unique_ptr<Bomberman> joueur{ new Bomberman(35+35/2-18/2,35+35/2-36/2,gRenderer) };//To put it inside a tile
	listeJoueur.push_back(std::move(joueur));
}
void Window::refresh()
{
	SDL_RenderClear(gRenderer);//Clear screen
	map->renderCopy(gRenderer);//Render the map to the screen
	for (auto x = listeJoueur.begin(); x != listeJoueur.end(); ++x)
		(**x).renderCopy(gRenderer);
	SDL_RenderPresent(gRenderer);//Update screen
	SDL_Delay(5);//Delay to make the processor breathe
}

Window::~Window()
{
	//Destroy
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( gWindow );
	gRenderer = nullptr;
	gWindow = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}
