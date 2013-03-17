//=======================================================================================
// Name        : Vehicles.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Vehicles in C++, Ansi-style
//=======================================================================================

#include "Vehicles.h"

#include <iostream>

//====================
//	CLASS VEHICLES
//====================

Vehicles::Vehicles(): name(""), location(0, 0) {
	_initCheck = this;

	ENSURE(init(), "Object 'Vehicles' was not properly initialized.");

}

Vehicles::Vehicles(int x, int y, const std::string n): name(n), location(x, y) {
	_initCheck = this;

	ENSURE(init(), "Object 'Vehicles' was not properly initialized.");
}

Vehicles::~Vehicles()
{
}

const std::string Vehicles::getName()const {
	return name;
}


bool Vehicles::init() {

	return _initCheck == this;
}

void Vehicles::resetInit() {
	_initCheck = this;
}


//====================
//	CLASS FIRETRUCK
//====================

Firetruck::Firetruck(): Vehicles(0, 0, ""), basename("") {
	base = NULL;
	goToTemp = false;
	available = true;
	atHome = true;
}

Firetruck::Firetruck(const int x, const int y, const std::string n, const std::string bn): Vehicles(x, y, n), basename(bn) {
	base = NULL;
	goToTemp = false;
	available = true;
	atHome = true;
}

Firetruck::~Firetruck()
{
}

void Firetruck::linkBase(Fire_Department* dep_ptr) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling linkBase().");

	base = dep_ptr;

	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match Firetruck's base*.");

}

std::string Firetruck::getBasename() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBasename().");

	return basename;
}

Fire_Department* Firetruck::getBaseptr() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	return base;
}

void Firetruck::move(std::string direction) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling move().");

	// Contract that checks if direction is legit.

	int curX = coord.getX();
	int curY = coord.getY();

	if (direction == "up") {
		coord.setY(curY + 1);
	}
	else if (direction == "down") {
		coord.setY(curY - 1);
	}
	else if (direction == "left") {
		coord.setX(curX - 1);
	}
	else if (direction == "right") {
		coord.setX(curX + 1);
	}
	else {
		std::cout << "This is not a valid direction." << std::endl;
	}
}

void Firetruck::setCoord(Coordinate location) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setCoord().");

	coord = location;
}

Coordinate Firetruck::getCoord() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getCoord().");

	return coord;
}

void Firetruck::setTempDest(Coordinate c) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getTempDest().");

	tempDestination = c;
}

Coordinate Firetruck::getTempDest() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getTempDest().");

	return tempDestination;
}

void Firetruck::setGoToTemp(bool v) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setGoToTemp().");

	goToTemp = v;

	ENSURE((getGoToTemp() == v), "Setted GoToTemp does not match Firetruck's GoToTemp.");
}

bool Firetruck::getGoToTemp() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getGoToTemp().");

	return goToTemp;
}

bool Firetruck::getAvailable() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getAvailable().");

	return available;
}

void Firetruck::setAvailable(bool state) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setAvailable().");

	available = state;
}

void Firetruck::setDestination(Coordinate dest) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setDestination().");

	destination = dest;

	ENSURE((getDestination() == dest), "Setted destination does not match Firetruck's destination.");
}

Coordinate Firetruck::getDestination() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getDestination().");

	return destination;
}

Structures* Firetruck::getTarget() {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getTarget().");

	return target;
}

void Firetruck::setTarget(Structures* t) {
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setTarget().");

	target = t;

	ENSURE((getTarget() == t), "Setted target does not match Firetruck's target.");
}

bool Firetruck::getIsHome(){
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getIsHome().");

	return atHome;
}

void Firetruck::setIsHome(bool b){
	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setIsHome().");

	atHome = b;

	ENSURE((getIsHome() == b), "Setted atHome does not match Firetruck's atHome.");
}

std::ostream& operator <<(std::ostream& s, Firetruck& truck){
	s << "Vehicle: Firetruck \n";
	s << "Name: " << truck.name << "\n";
	s << "Basename: " << truck.basename << "\n";
	s << "Location: " << truck.location << "\n";

	return s;
}



