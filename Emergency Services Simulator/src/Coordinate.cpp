//=======================================================================================
// Name        : Coordinate.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Coordinate in C++, Ansi-style
//=======================================================================================

#include <sstream>
#include <iostream>

#include "Coordinate.h"

Coordinate::Coordinate(): x(0), y(0) {
	_initCheck = this;

	ENSURE(properlyInitialized(), "Object 'Coordinate' was not properly initialized.");
}

Coordinate::Coordinate(int x_value, int y_value): x(x_value), y(y_value) {
	_initCheck = this;

	ENSURE(properlyInitialized(), "Object 'Coordinate' was not properly initialized.");
}

Coordinate::Coordinate(const Coordinate &cSource){
	x = cSource.x;
	y = cSource.y;
	_initCheck = this;
}

Coordinate& Coordinate::operator= (const Coordinate &cSource){
	x = cSource.x;
	y = cSource.y;
	_initCheck = this;

	return *this;
}

Coordinate::~Coordinate()
{
}

int Coordinate::getX(){
	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling getX().");

	return x;
}

int Coordinate::getY(){
	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling getY().");

	return y;
}

void Coordinate::setX(int val) {
	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling setX().");

	x = val;

	ENSURE((getX() == val), "Coordinate's x didn't match setted x.");
}

void Coordinate::setY(int val) {
	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling setY().");

	y = val;

	ENSURE((getY() == val), "Coordinate's y didn't match setted y.");
}

std::ostream& operator <<(std::ostream& s, Coordinate& coordinate){
	s << "(" << coordinate.getX() << ", " << coordinate.getY() << ")";
	return s;
}

std::string Coordinate::getString() {
	REQUIRE(this->properlyInitialized(), "Object 'Coordinate' was not properly initialized when calling getString().");

	std::stringstream ss;
	ss << x;
	std::string sx = ss.str();
	ss.str("");
	ss << y;
	std::string sy = ss.str();
	std::string s =  "(" + sx + ", " + sy + ")";
	return s;
}

bool Coordinate::operator==(const Coordinate &c) const{
	Coordinate comp = c;
	if (this->x == comp.getX() && this->y == comp.getY()) {
		return true;
	}
	else {
		return false;
	}
}

bool Coordinate::operator!=(const Coordinate &c) const{
	if (*this == c) {
		return false;
	}
	else {
		return true;
	}
}

bool Coordinate::properlyInitialized(){
	return _initCheck == this;
}

// TEST THE DEFAULT COORDINATE CONSTRUCTOR.
TEST_F(CoordinateTest, DefaultConstructor){
	EXPECT_TRUE(coordinate.properlyInitialized());
	EXPECT_EQ(0, coordinate.getX());
	EXPECT_EQ(0, coordinate.getY());
}

// TEST THE SPECIFIED COORDINATE CONSTRUCTOR.
TEST_F(CoordinateTest, Constructor){
	coordinate = Coordinate(1, 1);
	EXPECT_TRUE(coordinate.properlyInitialized());
	EXPECT_EQ(1, coordinate.getX());
	EXPECT_EQ(1, coordinate.getY());
}

// TEST THE SET AND GET FUNCTIONS FROM COORDINATE
TEST_F(CoordinateTest, SetFunctions){
	coordinate.setX(999);
	EXPECT_EQ(999, coordinate.getX());
	coordinate.setY(-549);
	EXPECT_EQ(-549, coordinate.getY());
}
