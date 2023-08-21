#pragma once

#include <string>
namespace my_home {
	static constexpr int height = 400;
	static constexpr int width = 800;
	static constexpr int FPS = 60;
	static const std::string game_title = "Tower of Hanoi";
	static const std::string howToPlay = 
		"Target of the game is to move all disks at\n the first pole to the third pole\n each time you can only move one disk \n you are can only place small disk on larger\none.";
}
