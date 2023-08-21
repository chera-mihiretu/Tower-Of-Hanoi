#pragma once
#include "Disk.h"
#include "FitToRaylib.h"
#include "Main_Menu.h"
#include <vector>
#include "showDialog.h"
class Inviroment {
private:
	const int height;
	const int width;
	std::vector<Disk> disk;
	int pole_pos[3];
	int pole_height;
	char clickType[3];
	
public:
	Inviroment(int x, int y);
	void DrawPlates();
	void DrawPoles();
	void DrawGround();
	void DrawBoard();
	void Update();
	int wichPole(float x);
	void setType(char type, bool done=false, bool special=false, char to='0');
	void clicks();	
	char toWhere(int num);
	int toWhere(char num);
	bool gameOver();
	Dialog gameOverD;
};