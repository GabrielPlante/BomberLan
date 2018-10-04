#include <iostream>
#include <../../Window.h>

int main( int argc, char* args[] )
{
	try {
		Window mainWindow(630, 630);
	
		SDL_Event event;
		bool quit{ false };
	
		while (!quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT)
					quit = true;
			}
			mainWindow.refresh();
		}
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}