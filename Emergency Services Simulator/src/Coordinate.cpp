/*
 * Coordinate.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <sstream>

#include "Coordinate.h"

Coordinate::Coordinate(): x(0), y(0) {

	_initCheck = this;
}

Coordinate::Coordinate(int x_value, int y_value): x(x_value), y(y_value) {

	_initCheck = this;
}

int Coordinate::getX()const {
	return x;
}

int Coordinate::getY()const {
	return y;
}

std::ostream& operator <<(std::ostream& stream, Coordinate& o){
	stream << "(" << o.x << ", " << o.y << ")";
	return stream;
}

bool Coordinate::properlyInitialized(){
	// PRIVATE METHOD DOES NOT HAVE POST OR PRE CONDITIONS.

	return _initCheck == this;
}


