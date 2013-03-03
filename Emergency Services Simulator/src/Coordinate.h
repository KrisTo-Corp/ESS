//=======================================================================================
// Name        : Coordinate.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Coordinate in C++, Ansi-style
//=======================================================================================

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <string>
#include <ostream>

class Coordinate {
private:
	int x;
	int y;

public:
	Coordinate();
	Coordinate(const int x_value, const int y_value);
	virtual ~Coordinate();

	int getX()const;
	int getY()const;
	friend std::ostream& operator <<(std::ostream& s, Coordinate& coordinate);
};

#endif /* COORDINATE_H_ */
