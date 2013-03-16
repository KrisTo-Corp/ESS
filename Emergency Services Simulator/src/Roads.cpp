//=======================================================================================
// Name        : Roads.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Roads in C++, Ansi-style
//=======================================================================================

#include <iostream>

#include "Roads.h"

//================
//	CLASS ROADS
//================


Roads::Roads(): CityObjects(none), name("") {
}

Roads::Roads(const std::string n, Eobjects t): CityObjects(t), name(n) {
}

Roads::~Roads()
{
}

std::string Roads::getName() {
	REQUIRE(init(), "Object 'Roads' was not properly initialized when calling getName()");

	return name;
}


//=================
//	CLASS STREET
//=================

Street::Street(): Roads("", street), start(0, 0), end(0, 0)
{
}

Street::Street(const int x_start, const int y_start, const int x_end, const int y_end, const std::string n): Roads(n, street), start(x_start, y_start), end(x_end, y_end)
{
}

Street::~Street()
{
}

Coordinate Street::getStart(){
	return start;
}

Coordinate Street::getEnd(){
	return end;
}

std::ostream& operator <<(std::ostream& s, Street& street){
	s << "Road: Street \n";
	s << "Name: " << street.name << "\n";
	s << "Start: " << street.start << "\n";
	s << "End: " << street.end << "\n";

	return s;
}

//===================
//	CLASS CROSSROAD
//===================

Crossroad::Crossroad(): Roads("", crossroad), location(0, 0)
{
}

Crossroad::Crossroad(const int x, const int y, const std::string n, const std::string street1, const std::string street2): Roads(n, crossroad), location(x, y)
{
	s1 = street1;
	s2 = street2;
}

Crossroad::~Crossroad()
{
}

Coordinate Crossroad::getLocation(){
	return location;
}

std::string Crossroad::getStreet1() {
	return s1;
}

std::string Crossroad::getStreet2() {
	return s2;
}

std::ostream& operator <<(std::ostream& s, Crossroad& crossroad){
	s << "Road: Crossroad \n";
	s << "Name: " << crossroad.name << "\n";
	s << "Location: " << crossroad.location << "\n";

	return s;
}

