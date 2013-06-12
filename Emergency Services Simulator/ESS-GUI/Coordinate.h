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
//	ENSURE(properlyInitialized(), "Object 'Coordinate' was not properly initialized.");

	Coordinate(const int x_value, const int y_value);
//	ENSURE(properlyInitialized(), "Object 'Coordinate' was not properly initialized.");

	int getX();
//	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling getX().");

	int getY();
//	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling getY().");

	void setX(int val);
//	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling setX().");
//	ENSURE((getX() == val), "Coordinate's x didn't match setted x.");

	void setY(int val);
//	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling setY().");
//	ENSURE((getY() == val), "Coordinate's y didn't match setted y.");

	friend std::ostream& operator <<(std::ostream& s, Coordinate& coordinate);

	std::string getString();
//	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling getString().");

	bool operator==(const Coordinate &c) const;

	bool operator!=(const Coordinate &c) const;

	Coordinate(const Coordinate &cSource);

	Coordinate& operator= (const Coordinate &cSource);

	bool properlyInitialized();

	virtual ~Coordinate();
};

#endif /* COORDINATE_H_ */
