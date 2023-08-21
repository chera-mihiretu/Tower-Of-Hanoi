#include "Game.h"
#include "Game_Constants.h"
// This game is developed by using  a c library called raylib you can install using vcpkg if you didn't installed it yet
int main() {
	Game* game = new Game(my_home::width, my_home::height, my_home::game_title, my_home::FPS);
	while (game->GameRunning()) {
		game->Tick();
	}
	
	return 0;
}