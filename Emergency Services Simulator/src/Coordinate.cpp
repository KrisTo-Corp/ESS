//=======================================================================================
// Name        : Coordinate.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Coordinate in C++, Ansi-style
//=======================================================================================

#include <sstream>

#include "Coordinate.h"

Coordinate::Coordinate(): x(0), y(0) {
	_initCheck = this;

	ENSURE(init(), "Object 'Coordinate' was not properly initialized.");
}

Coordinate::Coordinate(int x_value, int y_value): x(x_value), y(y_value) {
	_initCheck = this;

	ENSURE(init(), "Object 'Coordinate' was not properly initialized.");
}

Coordinate::~Coordinate()
{
}

int Coordinate::getX() const {
	return x;
}

int Coordinate::getY() const {
	return y;
}

void Coordinate::setX(int val) {
	x = val;
}

void Coordinate::setY(int val) {
	y = val;
}

std::ostream& operator <<(std::ostream& s, Coordinate& coordinate){
	s << "(" << coordinate.getX() << ", " << coordinate.getY() << ")";
	return s;
}

bool Coordinate::init() {
	return _initCheck == this;
}
