#pragma once
#include "raylib.h"
#include "Vector.h"
#include "Game_Constants.h"
#include <assert.h>
#include <iostream>
#include <sstream>
namespace fit {
	static void DrawBoarder(Vector<float> pos, Vector<float> size, int thick, Color c);
	static void DrawRect(Vector<float> pos, Vector<float> size, Color c);
	static void DrawRoundRect(Vector<float> pos, Vector<float> size, float roundness, int segment, Color c);
	
}
namespace dialog {
	static void DrawTextD(int x, int y, int font, std::string text, Color c);
	static void DrawButton(int x, int y, int font, std::string Label);
	static void DrawDialogBox(float x, float y, float width, float height);
}
void fit::DrawBoarder(Vector<float> pos, Vector<float> size, int thick, Color c) {
	assert(pos.getX() + size.getX() <= my_home::width &&
		pos.getY() + size.getY() <= my_home::height);	//// The drawing is out of the boundary////
	DrawRectangleLinesEx({pos.getX(), pos.getY(), size.getX(), size.getY()}, thick, c);
}
void fit::DrawRect(Vector<float> pos, Vector<float> size, Color c) {
	assert(pos.getX() + size.getX() <= my_home::width &&
		pos.getY() + size.getY() <= my_home::height);	//// The drawing is out of the boundary////
	DrawRectangleV({ pos.getX(), pos.getY() }, { size.getX(), size.getY() }, c);
}

void fit::DrawRoundRect(Vector<float> pos, Vector<float> size, float roundness, int segment, Color c)
{
	assert(pos.getX() + size.getX() <= my_home::width &&
		pos.getY() + size.getY() <= my_home::height);	//// The drawing is out of the boundary////
	DrawRectangleRounded({ pos.getX(), pos.getY(), size.getX(), size.getY() }, roundness, segment, c);
}


void dialog::DrawTextD(int x, int y, int font, std::string text, Color c)
{
	std::string start = "";
	int line_count = 0;
	for (char a : text) {
		if (a == '\n')
			line_count++;
	}
	if(line_count != 0)
		for (int i = 0; i < 4; i++) {
			start = text.substr(0, text.find("\n"));
			text = text.substr(text.find("\n")+1, -1);
			DrawText(start.c_str(), x - MeasureText(start.c_str(), font) / 2, y + i*20, font, c);
		}
	else
		DrawText(text.c_str(), x - MeasureText(text.c_str(), font) / 2, y, font, c);
	
}

void dialog::DrawButton(int x, int y, int font, std::string Label)
{
	DrawRectangle(x-MeasureText(Label.c_str(), font+20)/2, y, MeasureText(Label.c_str(), font+20), font, BROWN);
	DrawText(Label.c_str() ,x - MeasureText(Label.c_str(), 30) / 2, y, font, WHITE);
}

void dialog::DrawDialogBox(float x, float y, float width, float height)
{
	DrawRectangle(x,y,width, height, RAYWHITE);
	Color color{0,0,0,0};
	for (int i = 5; i > 0; i--) {
		DrawRectangleLinesEx({ x-i,y-i,width+i*2,height+i*2 }, 2, color);
		color.a += 15;
	}
	
}

