#pragma once
template <typename dataType> class Vector {
private:
	dataType x;
	dataType y;
public:
	Vector() = default;
	Vector(dataType x, dataType y) {
		this->x = x;
		this->y = y;
	}
	dataType getX() {
		return x;
	}
	dataType getY() {
		return y;
	}
	void toX(dataType value) {
		this->x += value;
	}
	void toY(dataType value) {
		this->y += value;
	}
};