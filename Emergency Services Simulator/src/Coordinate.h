/*
 * Coordinate.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <string>
#include <ostream>
#include <typeinfo>

class Coordinate {
private:
	int x;
	int y;

	Coordinate* _initCheck;

public:
	Coordinate();
//	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");

	Coordinate(const int x, const int y);
//	REQUIRE(typeid(x) == typeid(int) && typeid(y) == typeid(int), "The constructor requires 2 integers.");
//	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");

	int getX()const;
//	REQUIRE(this->properlyInitialized(), "The object was not properly initialized when calling getX().");
//	ENSURE(typeid(x) == typeid(int), "getX() should return an integer.");

	int getY()const;
//	REQUIRE(this->properlyInitialized(), "The object was not properly initialized when calling getY().");
//	ENSURE(typeid(y) == typeid(int), "getY() should return an integer.");

	friend std::ostream& operator <<(std::ostream& stream, Coordinate& o);
//	REQUIRE(o.properlyInitialized(), "The coordinate was not properly initialized when pushing to stream.");

private:
	bool properlyInitialized();

};

#endif /* COORDINATE_H_ */
