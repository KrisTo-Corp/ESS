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

Vehicles::Vehicles(): name(""), coord(0, 0) {
	_initCheck = this;

	ENSURE(properlyInitialized(), "Object 'Vehicles' was not properly initialized.");

}

Vehicles::Vehicles(int x, int y, const std::string n): name(n), coord(x, y) {
	_initCheck = this;

	ENSURE(properlyInitialized(), "Object 'Vehicles' was not properly initialized.");
}

Vehicles::~Vehicles()
{
}


bool Vehicles::properlyInitialized() {

	return _initCheck == this;
}

std::string Vehicles::getName() {
	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setCoord().");

	return name;
}

void Vehicles::setCoord(Coordinate location) {
	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setCoord().");

	coord = location;
}

Coordinate Vehicles::getCoord() {
	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getCoord().");

	return coord;
}

Vehicles::Vehicles(const Vehicles& c){
	name = c.name;
	coord = c.coord;

	_initCheck = this;
}

Vehicles& Vehicles::operator =(const Vehicles& c){
	name = c.name;
	coord = c.coord;

	_initCheck = this;
	return *this;
}


//====================
//	CLASS FIRETRUCK
//====================

Firetruck::Firetruck(): Vehicles(0, 0, ""), basename(""), tempDestination(0, 0), destination(0, 0) {
	base = NULL;
	goToTemp = false;
	available = true;
	atHome = true;
	target = NULL;

	ENSURE(properlyInitialized(), "Object 'Firetruck' was not properly initialized.");
}

Firetruck::Firetruck(const int x, const int y, const std::string n, const std::string bn): Vehicles(x, y, n), basename(bn) {
	base = NULL;
	goToTemp = false;
	available = true;
	atHome = true;
	target = NULL;

	ENSURE(properlyInitialized(), "Object 'Firetruck' was not properly initialized.");
}

Firetruck::~Firetruck()
{
}

void Firetruck::linkBase(Fire_Department* dep_ptr) {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling linkBase().");

	base = dep_ptr;

	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match Firetruck's base*.");

}

std::string Firetruck::getBasename() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getBasename().");

	return basename;
}

Fire_Department* Firetruck::getBaseptr() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	return base;
}

void Firetruck::move(std::string direction) {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling move().");
	ENSURE(direction == "up" || direction == "down" || direction == "left" || direction == "right", "An invalid direction was passed as an argument to move() in object 'Firetruck'");

	Coordinate oldLocation = coord;

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

	ENSURE((oldLocation != coord), "Firetruck did not move properly.");
}


void Firetruck::setTempDest(Coordinate c) {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getTempDest().");

	tempDestination = c;

	ENSURE(getTempDest() == c, "Setted tempDestination in Firetruck did not match Firetruck's tempDestination.");
}

Coordinate Firetruck::getTempDest() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getTempDest().");

	return tempDestination;
}

void Firetruck::setGoToTemp(bool v) {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setGoToTemp().");

	goToTemp = v;

	ENSURE((getGoToTemp() == v), "Setted GoToTemp does not match Firetruck's GoToTemp.");
}

bool Firetruck::getGoToTemp() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getGoToTemp().");

	return goToTemp;
}

bool Firetruck::getAvailable() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getAvailable().");

	return available;
}

void Firetruck::setAvailable(bool state) {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setAvailable().");

	available = state;

	ENSURE(getAvailable() == state, "Setted available does not match Firetruck's available");
}

void Firetruck::setDestination(Coordinate dest) {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setDestination().");

	destination = dest;

	ENSURE((getDestination() == dest), "Setted destination does not match Firetruck's destination.");
}

Coordinate Firetruck::getDestination() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getDestination().");

	return destination;
}

Structures* Firetruck::getTarget() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getTarget().");

	return target;
}

void Firetruck::setTarget(Structures* t) {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setTarget().");

	target = t;

	ENSURE((getTarget() == t), "Setted target does not match Firetruck's target.");
}

bool Firetruck::getIsHome(){
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getIsHome().");

	return atHome;
}

void Firetruck::setIsHome(bool b){
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setIsHome().");

	atHome = b;

	ENSURE((getIsHome() == b), "Setted atHome does not match Firetruck's atHome.");
}

std::ostream& operator <<(std::ostream& s, Firetruck& truck){
	s << "Vehicle: Firetruck \n";
	s << "Name: " << truck.name << "\n";
	s << "Basename: " << truck.basename << "\n";
	s << "Location: " << truck.coord << "\n";

	return s;
}

Firetruck::Firetruck(const Firetruck& c){
	coord = c.coord;
	tempDestination = c.tempDestination;
	destination = c.destination;
	target = c.target;
	goToTemp = c.goToTemp;
	available = c.available;
	atHome = c.atHome;
	basename = c.basename;
	base = c.base;
	name = c.name;

	_initCheck = this;
}

Firetruck& Firetruck::operator = (const Firetruck& c){
	coord = c.coord;
	tempDestination = c.tempDestination;
	destination = c.destination;
	target = c.target;
	goToTemp = c.goToTemp;
	available = c.available;
	atHome = c.atHome;
	basename = c.basename;
	base = c.base;
	name = c.name;

	_initCheck = this;

	return *this;

}



