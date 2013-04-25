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

Vehicles::Vehicles(): name(""), coord(0, 0), basename(""), tempDestination(0, 0), destination(0, 0) {
	_initCheck = this;

	goToTemp = false;
	available = true;
	atHome = true;
	target = NULL;

	ENSURE(properlyInitialized(), "Object 'Vehicles' was not properly initialized.");

}

Vehicles::Vehicles(int x, int y, const std::string n, std::string bn): name(n), coord(x, y), basename(bn) {
	_initCheck = this;

	goToTemp = false;
	available = true;
	atHome = true;
	target = NULL;

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

std::string Vehicles::getBasename() {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getBasename().");

	return basename;
}

void Vehicles::move(std::string direction) {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling move().");
	ENSURE(direction == "up" || direction == "down" || direction == "left" || direction == "right", "An invalid direction was passed as an argument to move() in object 'Vehicle'");

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

	ENSURE((oldLocation != coord), "Vehicle did not move properly.");
}

void Vehicles::setTempDest(Coordinate c) {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getTempDest().");

	tempDestination = c;

	ENSURE(getTempDest() == c, "Setted tempDestination in Vehicle did not match Vehicle's tempDestination.");
}

Coordinate Vehicles::getTempDest() {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getTempDest().");

	return tempDestination;
}

void Vehicles::setGoToTemp(bool v) {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling setGoToTemp().");

	goToTemp = v;

	ENSURE((getGoToTemp() == v), "Setted GoToTemp does not match Vehicle's GoToTemp.");
}

bool Vehicles::getGoToTemp() {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getGoToTemp().");

	return goToTemp;
}

bool Vehicles::getAvailable() {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getAvailable().");

	return available;
}

void Vehicles::setAvailable(bool state) {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling setAvailable().");

	available = state;

	ENSURE(getAvailable() == state, "Setted available does not match Vehicle's available");
}

void Vehicles::setDestination(Coordinate dest) {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling setDestination().");

	destination = dest;

	ENSURE((getDestination() == dest), "Setted destination does not match Vehicle's destination.");
}

Coordinate Vehicles::getDestination() {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getDestination().");

	return destination;
}

Structures* Vehicles::getTarget() {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getTarget().");

	return target;
}

void Vehicles::setTarget(Structures* t) {
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling setTarget().");

	target = t;

	ENSURE((getTarget() == t), "Setted target does not match Vehicle's target.");
}

bool Vehicles::getIsHome(){
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling getIsHome().");

	return atHome;
}

void Vehicles::setIsHome(bool b){
	REQUIRE(properlyInitialized(), "Object 'Vehicle' was not properly initialized when calling setIsHome().");

	atHome = b;

	ENSURE((getIsHome() == b), "Setted atHome does not match Vehicle's atHome.");
}

//====================
//	CLASS FIRETRUCK
//====================

Firetruck::Firetruck(): Vehicles(0, 0, "", "") {
	base = NULL;

	ENSURE(properlyInitialized(), "Object 'Firetruck' was not properly initialized.");
}

Firetruck::Firetruck(const int x, const int y, const std::string n, const std::string bn): Vehicles(x, y, n, bn) {
	base = NULL;

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

Fire_Department* Firetruck::getBaseptr() {
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	return base;
}

std::ostream& operator <<(std::ostream& s, Firetruck& truck){
	s << "Vehicle: Firetruck \n";
	s << "Name: " << truck.name << "\n";
	s << "Basename: " << truck.basename << "\n";
	s << "Location: " << truck.coord << "\n";

	return s;
}

Firetruck::Firetruck(const Firetruck& c){
	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling copy constructor().");

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

//====================
//	CLASS PoliceCar
//====================

PoliceCar::PoliceCar(): Vehicles(0, 0, "", "") {
	base = NULL;

	ENSURE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized.");
}

PoliceCar::PoliceCar(const int x, const int y, const std::string n, const std::string bn): Vehicles(x, y, n, bn) {
	base = NULL;

	ENSURE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized.");
}

void PoliceCar::linkBase(PoliceStation* dep_ptr) {
	REQUIRE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized when calling linkBase().");

	base = dep_ptr;

	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match PoliceCar's base*.");

}

PoliceStation* PoliceCar::getBaseptr() {
	REQUIRE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized when calling getBaseptr().");

	return base;
}

std::ostream& operator <<(std::ostream& s, PoliceCar& truck){
	s << "Vehicle: Vehicle \n";
	s << "Name: " << truck.name << "\n";
	s << "Basename: " << truck.basename << "\n";
	s << "Location: " << truck.coord << "\n";

	return s;
}

PoliceCar::PoliceCar(const PoliceCar& c){
//	REQUIRE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized when calling copy constructor.");

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

PoliceCar& PoliceCar::operator = (const PoliceCar& c){
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

//====================
//	CLASS Ambulance
//====================

Ambulance::Ambulance(): Vehicles(0, 0, "", "") {
	base = NULL;

	ENSURE(properlyInitialized(), "Object 'Ambulance' was not properly initialized.");
}

Ambulance::Ambulance(const int x, const int y, const std::string n, const std::string bn): Vehicles(x, y, n, bn) {
	base = NULL;

	ENSURE(properlyInitialized(), "Object 'Ambulance' was not properly initialized.");
}

void Ambulance::linkBase(Hospital* dep_ptr) {
	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling linkBase().");

	base = dep_ptr;

	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match Ambulance's base*.");
}

Hospital* Ambulance::getBaseptr() {
	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling getBaseptr().");

	return base;
}

std::ostream& operator <<(std::ostream& s, Ambulance& truck){
	s << "Vehicle: Vehicle \n";
	s << "Name: " << truck.name << "\n";
	s << "Basename: " << truck.basename << "\n";
	s << "Location: " << truck.coord << "\n";

	return s;
}

Ambulance::Ambulance(const Ambulance& c){
	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling copy constructor.");

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

Ambulance& Ambulance::operator = (const Ambulance& c){
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

void Ambulance::setPassenger(Casualty* c){
	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling setPassenger().");

	passenger = c;

	ENSURE(passenger == c, "Method setPassenger() of Ambulance did not correctly set passenger.");
}
Casualty* Ambulance::getPassenger(){
	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling getPassenger().");

	return passenger;
}

bool Ambulance::getContaining(){
	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling getContaining().");

	return containing_passenger;
}
void Ambulance::setContaining(bool b){
	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling setContaining().");

	containing_passenger = b;

	ENSURE(containing_passenger == b, "Method setContaining() of Ambulance did not correctly set bool containing_passenger.");
}


