#include "Inviroment.h"
#include <iostream>
namespace charchters {
	/**
	U - move Up
	D - Move Down
	S- Move Side Left
	T - Movr Side Right
	! - cannot be changed
	* - changable
	*/
	const char moveUp = 'U';
	const char moveDown = 'D';
	const char moveSide = 'S';
	const char noModify = '!';
	const char modify = '*';
	const char one = '0';
	const char two = '1';
	const char three = '2';
}
namespace ch = charchters;
Inviroment::Inviroment(int x, int y) :
	width(x),
	height(y)
{
	pole_pos[0] = (width / 2 - width / 4)- ((width / 2 - width / 4)%5); //first pole position
	pole_pos[1] = width / 2-((width/2)%5); // second pole position 
	pole_pos[2] = (width / 2 + width / 4)-((width / 2 + width / 4)%5);// third pole position
	pole_height = height - (height / 4 + height / 4); //pole hight
	disk.resize(Main_Menu::getDiskNo());
	int size = disk.size();
	for (int count = 0; count < size; count++) {
		disk[count].setSize({ (float)width / 4 - count * 15, 20 });
		disk[count].setPosition({ (float)pole_pos[0], (float)height - height / 4 - (count + 1) * 20 });

	}
	clickType[0] = 'N'; //Wich type of movement that should be done
	clickType[1] = '0'; //How much step the disk should move (=to where position
	clickType[2] = '*'; //if the character can be modified

}

void Inviroment::DrawPlates()
{
	for (Disk& dis : disk) {
		fit::DrawRoundRect({ (float)dis.getPosition().getX() - dis.getCenter(),dis.getPosition().getY() }
		, { dis.getSize().getX(), dis.getSize().getY() }, 10, 20, BROWN);
	}
	clicks();
	Update();

	

}

void Inviroment::DrawPoles()
{
	for (int i = 0; i < 3; i++) {
		fit::DrawRect({ (float)pole_pos[i] - 10, (float)height / 4 }, { 20,(float)pole_height }, DARKBROWN);
	}
	
	
}



void Inviroment::DrawGround()
{
	fit::DrawRect({ (float)width / 16, (float)height - height / 4 }, { (float)width - (width / 8), 20 }, GRAY);
}

void Inviroment::DrawBoard()
{
	fit::DrawBoarder({ 0,0 }, { (float)width, (float)height }, 20, DARKGRAY);
}

void Inviroment::Update()
{

	for (Disk& d : disk) {
		if (d.getUp()) {
			bool thePoleHasNoDisk = true;
			switch (clickType[0])
			{
			case ch::moveUp:
				if (d.getPosition().getY() >= (height / 4 - d.getSize().getY()*2)) {
					d.addToY(-5);
				}
				else {
					setType(ch::noModify, true);
				}
				
				break;
			case ch::moveSide:
				/*
				after moving the disk first we need to make sure the pole has no disk
				* if it does but no movement then the current disk size is bigger than the choosed
				  pole position
				*/
				thePoleHasNoDisk = true; 
				for (int i = disk.size()-1; i >= 0; i--) {
					if (disk[i].getPosition().getX() == pole_pos[toWhere(clickType[1])]) {
						if (disk[i].getSize().getX() > d.getSize().getX()) {
							if ((int)d.getPosition().getX() > pole_pos[toWhere(clickType[1])]) {
								d.addToX(-5);
							}
							else if ((int)d.getPosition().getX() < pole_pos[toWhere(clickType[1])]) {
								d.addToX(5);
								
							}
							else {
								d.setPosHoleder(disk[i].getPosition().getY() - 20);
								setType(ch::moveDown, false, true);
							}
						}
						else if(disk[i].getSize().getX() == d.getSize().getX()){
							continue;
						}
						else {
							setType(ch::moveDown, false, true);
						}

						thePoleHasNoDisk = false;
						break;
					}
				}
				if (thePoleHasNoDisk) {
					if ((int)d.getPosition().getX() > pole_pos[toWhere(clickType[1])]) {
						d.addToX(-5);
						
					}
					else if ((int)d.getPosition().getX() < pole_pos[toWhere(clickType[1])]) {
						d.addToX(5);
					}
					else {
						
						d.setPosHoleder((int)height - height / 4 - 20);
						setType(ch::moveDown, false, true);

					}
				}
				break;

			case ch::moveDown:
				if (d.addToY(5)) {
					setType(ch::noModify, true);
					d.setUp(false);
				}
			}
			break;
		}
		
	}
}

int Inviroment::wichPole(float x)
{
	for (int i = 0; i < 3; i++) {
		if (x > pole_pos[i] - (width / 16) && x < pole_pos[i] + (width / 16)) {
			return i;
		}
	}
	return -1;
}

void Inviroment::setType(char type, bool done, bool special, char to)
{
	/*
		done = used when the movement is done only called by built in function not by click
		special = used to be called when a direction is called, only called by built in function
		to = is used to specifiy where the disk should go
	*/
	if (clickType[2] != '!') {
		clickType[0] = type;
		if (type == ch::moveSide) {
			clickType[1] = to;
		}
		clickType[2] = '!';
	}
	else if (done) {
		clickType[0] = type;
		clickType[2] = '*';
	}
	else if (special) {
		clickType[0] = type;
	}
		
	
}

void Inviroment::clicks()
{
	if (gameOver())
		return;
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		float x = GetTouchX();
		float y = GetTouchY();
		if (y > height / 4 && y < height - height / 4) {
			if (wichPole(x) != -1)
			{
				bool noUp = true;
				for (Disk d : disk) {
					if (d.getUp())
					{
						noUp = false;
					}
				}

				if (noUp) {
					for (int count = disk.size() - 1; count >= 0; count--) {
						if (wichPole(disk[count].getPosition().getX()) == wichPole(x)) {
							setType(ch::moveUp);
							disk[count].setUp(true);
							disk[count].setPosHoleder(disk[count].getPosition().getY());
							break;
						}
					}
				}
				else {
					for (Disk& d : disk) {
						setType(ch::moveSide, false, false, toWhere(wichPole((int)x)));
					}
					
				}
			}
		}
	}
	int KEY[3] = { KEY_ONE, KEY_TWO, KEY_THREE };
	bool no_up = true;
	for (int i = 0; i < 3; i++) {
		if (IsKeyPressed(KEY[i])) {
			for (Disk& d : disk) {
				if (d.getUp())
					no_up = false;
			}
			if (no_up) {
				for (int count = disk.size() - 1; count >= 0; count--) {
					if (wichPole(disk[count].getPosition().getX()) == i) {
						setType(ch::moveUp);
						disk[count].setUp(true);
						disk[count].setPosHoleder(disk[count].getPosition().getY());
						break;
					}
				}
			}
			else {
				for (Disk& d : disk) {
					setType(ch::moveSide, false, false, toWhere(i));
				}
			}
		}
	}
}

char Inviroment::toWhere(int num)
{
	char converted;
	std::stringstream convert;
	convert << num;
	convert >> converted;

	return converted;
}
int Inviroment::toWhere(char num)
{
	int converted;
	std::stringstream convert;
	convert << num;
	convert >> converted;

	return converted;
}

bool Inviroment::gameOver()
{
	bool gameOver = true;
	for (Disk& d:disk)
	{
		if (wichPole(d.getPosition().getX()) != 2) {
			gameOver = false;
		}
	}
	return gameOver;
}

