#pragma once
#include <string>
#include "FitToRaylib.h"
#include "Game_Constants.h"
class Dialog {
private:
	std::string MainMessage;
	std::string detail;
	bool yesNo;
	int increament;
public:
	Dialog() = default;
	Dialog(std::string DesplayMessage, std::string detail);
	Dialog(std::string DesplayMessage, bool yesNo);
	void Draw();
	int handleClick();
	void DrawTheDialog();
	void reset();
	int response();
	void setDetail(std::string message);
};

inline Dialog::Dialog(std::string DesplayMessage, std::string detail):
	MainMessage(DesplayMessage),
	detail(detail),
	yesNo(false)
{
	increament = 0;
}

inline Dialog::Dialog(std::string DesplayMessage, bool yesNo)
	:
	MainMessage(DesplayMessage),
	yesNo(yesNo)


{
	increament = 0;
}

inline void Dialog::Draw()
{

	if (increament >= 10) {
		dialog::DrawTextD(my_home::width/2, my_home::height/4, 50, MainMessage, BLUE);
		dialog::DrawTextD(my_home::width / 2,my_home::height / 4 + 60, 20, detail, BLACK);
		if (yesNo) {
			for (int number = 0; number < 2; number++) {
				dialog::DrawButton(my_home::width / 2, my_home::height / 2 + number * 50, 30, (number == 0) ? "Yes" : "No");
			}
		}
		
		
	}
}

inline int Dialog::handleClick()
{

	if (increament >= 10) {

	}else{
		return -1;
	}
}

inline void Dialog::DrawTheDialog()
{
	if (increament < 10) {
		dialog::DrawDialogBox(
			my_home::width / 2 - (my_home::width/(13-increament) + my_home::width/12),
			my_home::height/2 - (my_home::height/(13-increament) + my_home::height/12),
			(my_home::width / (13 - increament)*2 + my_home::width / 6),
			(my_home::height / (13 - increament))*2 + my_home::height/ 6);
		increament++;
	}
	else {
		dialog::DrawDialogBox(
			my_home::width / 2 - (my_home::width / (13 - increament) + my_home::width / 12),
			my_home::height / 2 - (my_home::height / (13 - increament) + my_home::height / 12),
			(my_home::width / (13 - increament) * 2 + my_home::width / 6),
			(my_home::height / (13 - increament)) * 2 + my_home::height / 6);
	}
}

inline void Dialog::reset()
{
	increament = 0;
}

inline int Dialog::response()
{
	int x,y;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		x = GetTouchX();
		y = GetTouchY();
		if (x > my_home::width / 2 - MeasureText("Yes", 50) && x < my_home::width / 2 + MeasureText("Yes", 50)) {
			if (y > my_home::height / 2 && y < my_home::height / 2 + 50) {
				return 1;
			}
		}
		if (x > my_home::width / 2 - MeasureText("No", 50) && x < my_home::width / 2 + MeasureText("No", 50)) {
			if (y > my_home::height / 2+50 && y < my_home::height / 2 + 100) {
				return 0;
			}
		}
		if (x < (my_home::width / 2 - (my_home::width / (13 - increament) + my_home::width / 12)))
			return -1;
		if (x >(my_home::width / 2 - (my_home::width / (13 - increament) + my_home::width / 12)+ 
			(my_home::width / (13 - 10) * 2 + my_home::width / 6)))
			return -1;
		if (y > my_home::height / 2 - (my_home::height / (13 - 10) + my_home::height / 12) + (my_home::height / (13 - increament)) * 2 + my_home::height / 6)
			return -1;
		if (y < (my_home::height / 2 - (my_home::height / (13 - increament) + my_home::height / 12)))
			return -1;


	}

	if (IsKeyPressed(KEY_Y)) {
		return 1;
	}
	else if (IsKeyPressed(KEY_N)) {
		return 0;
	}
	else if (IsKeyPressed(KEY_ENTER)) {
		return -2;
	}
	

	return -2;
}

inline void Dialog::setDetail(std::string message)
{
	detail = message;
}

