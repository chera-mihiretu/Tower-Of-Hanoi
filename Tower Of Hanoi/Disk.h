#pragma once
#include "Vector.h"
class Disk {
private:
	Vector<float> position;
	Vector<float> size;
	bool isUp;
	float center;
	int y_pos_holder;
public:
	Disk();
	void setPosHoleder(int value);
	void setPosition(Vector<float> pos);
	void setSize(Vector<float> value);
	Vector<float> getPosition();
	Vector<float> getSize();
	bool addToY(float value);
	void addToX(float value);
	bool getUp();
	void setUp(bool value);
	float getCenter();
};