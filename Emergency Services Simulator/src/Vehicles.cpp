/*
 * Vehicles.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include "Vehicles.h"

Vehicles::Vehicles(): name(""), location(0, 0)
{
}

Vehicles::Vehicles(int x, int y, const std::string n): name(n), location(x, y)
{
}

Vehicles::~Vehicles()
{
}

Firetruck::Firetruck(): Vehicles(0, 0, ""), basename("")
{
}

Firetruck::Firetruck(int x, int y, const std::string n, const std::string bn): Vehicles(x, y, n), basename(bn)
{
}

std::ostream& operator <<(std::ostream& stream, Firetruck& o){
	stream << "Vehicle: Firetruck \n";
	stream << "Name: " << o.name << "\n";
	stream << "Basename: " << o.basename << "\n";
	stream << "Location: " << o.location << "\n";

	return stream;
}

