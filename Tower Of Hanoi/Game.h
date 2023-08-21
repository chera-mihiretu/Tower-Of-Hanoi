#pragma once
#include "Inviroment.h"
#include "Main_Menu.h"
#include "raylib.h"
#include <assert.h>
#include <string>
class Game {
public:
	Game(int width, int height, std::string _title, int FPS); 
	Game(Game& other) = delete;
	Game(const Game& other) = delete;
	~Game() noexcept;
	void checkGameOver();
private:
	bool close;
	const int width;
	const int height;

public:
	Inviroment* inv;
	Main_Menu* menu;
	void Draw();
	void Tick();
	bool GameRunning();
};