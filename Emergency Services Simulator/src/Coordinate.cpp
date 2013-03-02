/*
 * Coordinate.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <sstream>

#include "Coordinate.h"

Coordinate::Coordinate(): x(0), y(0)
{
}

Coordinate::Coordinate(int x_value, int y_value): x(x_value), y(y_value)
{
}

std::ostream& operator <<(std::ostream& stream, Coordinate& o){
	stream << "(" << o.x << ", " << o.y << ")";
	return stream;
}

Coordinate::~Coordinate()
{
}

