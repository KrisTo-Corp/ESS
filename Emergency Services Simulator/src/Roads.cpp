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

Street::Street(int x_start, int y_start, int x_end, int y_end, const std::string n): Roads(n, street), start(x_start, y_start), end(x_end, y_end)
{
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

Crossroad::Crossroad(int x, int y, const std::string n): Roads(n, crossroad), location(x, y)
{
}

std::ostream& operator <<(std::ostream& stream, Crossroad& o){
	stream << "Road: Crossroad \n";
	stream << "Name: " << o.name << "\n";
	stream << "Location: " << o.location << "\n";

	return stream;
}

