#include "Game.h"
Game::Game(int width, int height, std::string _title, int FPS) :
	width(width),
	height(height), 
	close(false)
	
{
	assert(!IsWindowReady());
	InitWindow(width, height, _title.c_str());
	SetTargetFPS(FPS);
	inv = new Inviroment(my_home::width - my_home::width / 4, my_home::height);
	menu = new Main_Menu(my_home::width - my_home::width / 4, my_home::width / 4, my_home::height);
	
	

}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
	CloseWindow();
}

void Game::checkGameOver()
{
	if (menu->restartClicked()) {
		inv = new Inviroment(my_home::width - my_home::width / 4, my_home::height);
		menu = new Main_Menu(my_home::width - my_home::width / 4, my_home::width / 4, my_home::height);
	}
	if (inv->gameOver()) {
		if (menu->gameOver()==1) {
			inv = new Inviroment(my_home::width - my_home::width / 4, my_home::height);
			menu = new Main_Menu(my_home::width - my_home::width / 4, my_home::width / 4, my_home::height);
		}
		else if (menu->gameOver() == 0) {
			close = true;
		}
	}
}
int Main_Menu::diskNo = 3;
void Game::Tick()
{
	BeginDrawing();
	ClearBackground(WHITE);
	Draw();
	checkGameOver();
	EndDrawing();
}

bool Game::GameRunning()
{
	if (!close)
		return !WindowShouldClose();
	else
		return false;
}



void Game::Draw()
{
	inv->DrawBoard();
	inv->DrawPoles();
	inv->DrawGround();
	inv->Update();
	inv->DrawPlates();
	menu->drawDiskSelector();
	if(!inv->gameOver())
		menu->DrawIcons();
	
	
}



