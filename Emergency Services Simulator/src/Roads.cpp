/*
 * Roads.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <iostream>

#include "Roads.h"

Roads::Roads(): name(""), CityObjects(none)
{
}

Roads::Roads(const std::string n, Eobjects t): name(n), CityObjects(t)
{
}

std::string Roads::getName() const{
	return name;
}

Roads::~Roads()
{
}

Street::Street(): Roads("", street), start(0, 0), end(0, 0)
{
}

Street::Street(const int x_start, const int y_start, const int x_end, const int y_end, const std::string n): Roads(n, street), start(x_start, y_start), end(x_end, y_end)
{
}

Coordinate Street::getStart(){
	return start;
}

Coordinate Street::getEnd(){
	return end;
}

std::ostream& operator <<(std::ostream& stream, Street& o){
	stream << "Road: Street \n";
	stream << "Name: " << o.name << "\n";
	stream << "Start: " << o.start << "\n";
	stream << "End: " << o.end << "\n";

	return stream;
}

Crossroad::Crossroad(): Roads("", crossroad), location(0, 0)
{
}

Crossroad::Crossroad(const int x, const int y, const std::string n): Roads(n, crossroad), location(x, y)
{
}

Coordinate Crossroad::getLocation(){
	return location;
}

std::ostream& operator <<(std::ostream& stream, Crossroad& o){
	stream << "Road: Crossroad \n";
	stream << "Name: " << o.name << "\n";
	stream << "Location: " << o.location << "\n";

	return stream;
}

