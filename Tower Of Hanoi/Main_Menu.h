#pragma once
#include "raylib.h"
#include "FitToRaylib.h"
#include "showDialog.h"
#include <sstream>
#include <string>
#include <iostream>
class Main_Menu {
private:
	bool pauseGame;
	float timer;
	int playedTime[3];
	static int diskNo;
	int width;
	int height;
	int start;
	bool onDialog;
	bool onRestart;
	Dialog showDial;
	Dialog restart;
	Dialog gameOverD;
	bool rest;

public:
	Main_Menu(int x_start, int x, int y);
	void restartGame();
	void DrawIcons();
	void setDiskNo(int value);
	static int getDiskNo();
	void resetTime();
	void add_second();
	std::string toString(int num);
	std::string callTo();
	int handleClick(int x, int y);
	bool restartClicked();
	int gameOver();
	void drawDiskSelector();
	
};
