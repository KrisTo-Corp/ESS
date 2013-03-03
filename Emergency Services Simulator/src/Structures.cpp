//=======================================================================================
// Name        : Structures.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Structures in C++, Ansi-style
//=======================================================================================
#include "Structures.h"

//=====================
//	CLASS STRUCTURES
//=====================

Structures::Structures(): CityObjects(none), name(""), location(0, 0), width(0), length(0)
{
}

Structures::Structures(const int x, const int y, const std::string n, const int w, const int l, Eobjects t): CityObjects(t), name(n), location(x, y), width(w), length(l)
{
}

Structures::~Structures()
{
}

std::string Structures::getName() const {
	return name;
}

Coordinate Structures::getLocation() {
	return location;
}


int Structures::getWidth() const {
	return width;
}

int Structures::getLength() const {
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
	s << "Structure: House \n";
	s << "Name: " << house.name << "\n";
	s << "Hitpoints: " << house.hitpoints << "\n";
	s << "Location:" << house.location << "\n";

	return s;
}

//==========================
//	CLASS FIRE DEPARTMENTS
//==========================

Fire_Department::Fire_Department(): Structures(0, 0, "", 4, 4, department), entrance(0, 0)
{
}

Fire_Department::Fire_Department(const int x, const int y, const int x_entrance, const int y_entrance, const std::string n): Structures(x, y, n, 4, 4, department), entrance(x_entrance, y_entrance)
{
}

Fire_Department::~Fire_Department()
{
}

std::ostream& operator <<(std::ostream& s, Fire_Department& department){
	s << "Structure: Fire Department \n";
	s << "Name: " << department.name << "\n";
	s << "Entrance: " << department.entrance << "\n";
	s << "Location: " << department.location << "\n";

	return s;
}



