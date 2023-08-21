#include "Disk.h"
#include <iostream>


Disk::Disk():
	isUp(false),
	y_pos_holder(0),
	center(0),
	position(Vector<float>{0,0}),
	size(Vector<float>{0,0})
{
}

void Disk::setPosHoleder(int value)
{
	y_pos_holder = value;
}

void Disk::setPosition(Vector<float> pos)
{
	position = pos;
}

void Disk::setSize(Vector<float> value)
{
	size = value;
	center =	value.getX()/2;
}
float Disk::getCenter() {
	return center;
}

Vector<float> Disk::getPosition()
{
	return position;
}

Vector<float> Disk::getSize()
{
	return size;
}

bool Disk::addToY(float value)
{
	std::cout << y_pos_holder << std::endl;
	
	if (y_pos_holder != 0) {
		if ((int)(position.getY() + value) > y_pos_holder) {
			y_pos_holder = 0;
			return true;
		}
	}
	position.toY(value);
	return false;
	
}

void Disk::addToX(float value)
{
	position.toX(value);
}

bool Disk::getUp()
{
	return isUp;
}

void Disk::setUp(bool value)
{
	isUp = value;
}
