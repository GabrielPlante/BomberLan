#include "Window.h"

int main( int argc, char* args[] )
{
	try {
		Window mainWindow(630, 630);
	
		Event event;
		while (event.checkEvent()) {
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