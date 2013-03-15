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

#include "DesignByContract.h"

class Coordinate {
private:
	int x;
	int y;

	Coordinate* _initCheck;
public:
	Coordinate();
//	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");

	Coordinate(const int x_value, const int y_value);
//	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");

	virtual ~Coordinate();

	int getX()const;
	int getY()const;

	void setX(int);
	void setY(int);

	friend std::ostream& operator <<(std::ostream& s, Coordinate& coordinate);

private:
	bool init();
};

#endif /* COORDINATE_H_ */
