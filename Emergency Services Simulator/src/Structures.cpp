//=======================================================================================
// Name        : Structures.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Structures in C++, Ansi-style
//=======================================================================================
#include "Structures.h"

#include <iostream>


//=====================
//	CLASS STRUCTURES
//=====================

Structures::Structures(): CityObjects(none), name(""), location(0, 0), width(0), length(0)
{
	ENSURE(init(), "Object 'Structures' was not properly initialized.");
}

Structures::Structures(const int x, const int y, const std::string n, const int w, const int l, Eobjects t): CityObjects(t), name(n), location(x, y), width(w), length(l)
{
	ENSURE(init(), "Object 'Structures' was not properly initialized.");
}

Structures::~Structures() {
}

std::string Structures::getName() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return name;
}

Coordinate Structures::getLocation() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return location;
}

int Structures::getWidth() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return width;
}

int Structures::getLength() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return length;
}

Structures::Structures(const Structures& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;

	_initCheck = this;
}

Structures& Structures::operator =(const Structures& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;

	_initCheck = this;

	return *this;
}



//================
//	CLASS HOUSE
//================

House::House(): Structures(0, 0, "", 2, 2, house) {
	hitpoints = 0;

	ENSURE(init(), "Object 'House' was not properly initialized.");
}

House::House(const int x, const int y, int hp, const std::string n): Structures(x, y, n, 2, 2, house) {
	hitpoints = hp;

	ENSURE(init(), "Object 'House' was not properly initialized.");
}

House::~House()
{
}

std::ostream& operator <<(std::ostream& s, House& house){
	REQUIRE(house.init(), "Object 'House' was not properly initialized when calling overloaded operator '<<'");

	s << "Structure: House \n";
	s << "Name: " << house.name << "\n";
	s << "Hitpoints: " << house.hitpoints << "\n";
	s << "Location:" << house.location << "\n";

	return s;
}

House::House(const House& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	hitpoints = c.hitpoints;

	_initCheck = this;
}

House& House::operator =(const House& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	hitpoints = c.hitpoints;

	_initCheck = this;

	return *this;
}

void House::decreaseHP(){
	REQUIRE(init(), "Object 'House' was not properly initialized when calling decreaseHP()");

	double oldHP = hitpoints;
	hitpoints = hitpoints - (1.0/(width*length));

	ENSURE(hitpoints == oldHP - (1.0/(width*length)), "HP of house was not decreased successfully.");
}

double House::getHP(){
	REQUIRE(init(), "Object 'House' was not properly initialized when calling getHP()");

	return hitpoints;
}


//==========================
//	CLASS FIRE DEPARTMENTS
//==========================

Fire_Department::Fire_Department(): Structures(0, 0, "", 4, 4, department), entrance(0, 0) {
	ENSURE(init(), "Object 'Fire_Department' was not properly initialized.");

}

Fire_Department::Fire_Department(const int x, const int y, const int x_entrance, const int y_entrance, const std::string n): Structures(x, y, n, 4, 4, department), entrance(x_entrance, y_entrance) {
	ENSURE(init(), "Object 'Fire_Department' was not properly initialized.");
}

Fire_Department::~Fire_Department()
{
}

void Fire_Department::addTruck(Firetruck* t) {
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling addTruck()");

	trucks.push_back(t);

	ENSURE((trucks[trucks.size()-1] == t), "Firetruck was not succesfully added to trucks Vector");
}

Firetruck* Fire_Department::useTruck() {
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling useTruck()");

	int size = trucks.size();
	if (trucks.size() != 0) {
		Firetruck* readyTruck = *(trucks.begin());
		trucks.erase(trucks.begin());
		return readyTruck;
		ENSURE((size - 1 == trucks.size()), "Firetruck was not succesfully added to trucks Vector");
	}
}

Coordinate& Fire_Department::getEntrance() {
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling getEntrance().");

	return entrance;
}

std::ostream& operator <<(std::ostream& s, Fire_Department& department){
	REQUIRE(department.init(), "Object 'House' was not properly initialized when calling overloaded operator '<<'");

	s << "Structure: Fire Department \n";
	s << "Name: " << department.name << "\n";
	s << "Entrance: " << department.entrance << "\n";
	s << "Location: " << department.location << "\n";

	return s;
}

int Fire_Department::getAmountTrucks(){
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling getAmountTrucks()");

	return trucks.size();
}

Fire_Department::Fire_Department(const Fire_Department& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	trucks = c.trucks;

	_initCheck = this;
}

Fire_Department Fire_Department::operator =(const Fire_Department& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	trucks = c.trucks;

	_initCheck = this;

	return *this;
}



