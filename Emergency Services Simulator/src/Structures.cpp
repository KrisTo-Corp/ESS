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
}

Structures::Structures(const int x, const int y, const std::string n, const int w, const int l, Eobjects t): CityObjects(t), name(n), location(x, y), width(w), length(l)
{
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


//================
//	CLASS HOUSE
//================

House::House(): Structures(0, 0, "", 2, 2, house) {
	hitpoints = 0;
}

House::House(const int x, const int y, int hp, const std::string n): Structures(x, y, n, 2, 2, house) {
	hitpoints = hp;
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

void House::decreaseHP(){
	hitpoints = hitpoints - (1.0/(width*length));
}

double House::getHP(){
	return hitpoints;
}

//==========================
//	CLASS FIRE DEPARTMENTS
//==========================

Fire_Department::Fire_Department(): Structures(0, 0, "", 4, 4, department), entrance(0, 0) {
}

Fire_Department::Fire_Department(const int x, const int y, const int x_entrance, const int y_entrance, const std::string n): Structures(x, y, n, 4, 4, department), entrance(x_entrance, y_entrance)
{
}

Fire_Department::~Fire_Department()
{
}

void Fire_Department::addTruck(Firetruck* t) {
	trucks.push_back(t);
}

Firetruck* Fire_Department::useTruck() {
	if (trucks.size() != 0) {
		Firetruck* readyTruck = *(trucks.begin());
		trucks.erase(trucks.begin());
		return readyTruck;
	}
}

Coordinate& Fire_Department::getEntrance() {
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



