//=======================================================================================
// Name        : Vehicles.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Vehicles in C++, Ansi-style
//=======================================================================================

#include "Vehicles.h"

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


bool Vehicles::init() {
	return _initCheck == this;
}

//====================
//	CLASS FIRETRUCK
//====================

Firetruck::Firetruck(): Vehicles(0, 0, ""), basename("") {
	base = NULL;

	_initCheck = this;

	ENSURE(init(), "Object 'Firetruck' was not properly initialized.");

}

Firetruck::Firetruck(const int x, const int y, const std::string n, const std::string bn): Vehicles(x, y, n), basename(bn) {
	base = NULL;

	_initCheck = this;

	ENSURE(init(), "Object 'Firetruck' was not properly initialized.");
}

Firetruck::~Firetruck()
{
}

void Firetruck::linkBase(Fire_Department* dep_ptr) {
	//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling linkBase().");

	base = dep_ptr;
}

std::string Firetruck::getBasename() const {
	//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBasename().");

	return basename;
}

Fire_Department* Firetruck::getBaseptr() {
	//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	return base;
}

std::ostream& operator <<(std::ostream& s, Firetruck& truck){
	s << "Vehicle: Firetruck \n";
	s << "Name: " << truck.name << "\n";
	s << "Basename: " << truck.basename << "\n";
	s << "Location: " << truck.location << "\n";

	return s;
}



