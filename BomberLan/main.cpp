#include "Window.h"
#include "Bomberman.h"
#include "Map.h"
#include "Event.h"

int main( int argc, char* args[] )
{
	try {
		Window mainWindow(630, 630);
		Map map{ mainWindow.getRenderer() };
		std::array<Bomberman, 4> players{
			Bomberman{13, 4, mainWindow.getRenderer(), &map, GREEN},
			Bomberman{4, 13, mainWindow.getRenderer(), &map, YELLOW},
			Bomberman{13, 13, mainWindow.getRenderer(), &map, ORANGE, 2},
			Bomberman{4, 4, mainWindow.getRenderer(), &map, BLUE, 1} };//The player is put last so it is renderer above the others

		map.addPlayers({ &players[0], &players[1], &players[2], &players[3] });

		Event event({ &players[3],&players[2] });
		while (event.checkEvent()) {//The game loop
			mainWindow.clear();
			map.renderCopy(mainWindow.getRenderer());
			for (auto it = players.begin(); it != players.end(); ++it)
				it->refresh();
			for (auto it = players.begin(); it != players.end(); ++it)
				it->renderCopy();
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