#include "Window.h"
#include "Bomberman.h"
#include "Map.h"
#include "Event.h"

int main( int argc, char* args[] )
{
	try {
		Window mainWindow(630, 630);
		Map map{ mainWindow.getRenderer() };
		Bomberman player{ 4, 4,mainWindow.getRenderer(), &map };
		std::array<Bomberman, 3> enemies{
			Bomberman{13, 4, mainWindow.getRenderer(), &map},
			Bomberman{4, 13, mainWindow.getRenderer(), &map},
			Bomberman{13, 13, mainWindow.getRenderer(), &map} };

	
		Event event;
		while (event.checkEvent(&player)) {
			mainWindow.clear();
			map.renderCopy(mainWindow.getRenderer());
			player.refresh();
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				it->refresh();
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				it->renderCopy();
			player.renderCopy();
			mainWindow.update();
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