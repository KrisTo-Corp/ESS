/*
 * Coordinate.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <sstream>

#include "Coordinate.h"

Coordinate::Coordinate() {
	x = 0;
	y = 0;
}

Coordinate::Coordinate(int x_value, int y_value) {
	x = x_value;
	y = y_value;
}

std::string Coordinate::print(){
	std::stringstream s;
	s << "(" << x << ", " << y << ")";
	return s.str();
}

Coordinate::~Coordinate()
{
}

