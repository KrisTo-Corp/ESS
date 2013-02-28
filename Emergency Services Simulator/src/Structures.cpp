/*
 * Structures.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include "Structures.h"

Structures::Structures(): name(""), location(0, 0), width(0), length(0)
{
}

Structures::Structures(int x, int y, const std::string n, int w, int l): name(n), location(x, y), width(w), length(l)
{
}

Structures::~Structures()
{
}

House::House(): Structures(0, 0, "", 2, 2) {
	hitpoints = 0;
}

House::House(int x, int y, int hp, const std::string n): Structures(x, y, n, 2, 2) {
	hitpoints = hp;
}

std::ostream& operator <<(std::ostream& stream, House& o){
	stream << "Structure: House \n";
	stream << "Name: " << o.name << "\n";
	stream << "Hitpoints: " << o.hitpoints << "\n";
	stream << "Location:" << o.location << "\n";

	return stream;
}

Fire_Department::Fire_Department(): Structures(0, 0, "", 4, 4), entrance(0, 0)
{
}

Fire_Department::Fire_Department(int x, int y, int x_entrance, int y_entrance, const std::string n): Structures(x, y, n, 4, 4), entrance(x_entrance, y_entrance)
{
}

std::ostream& operator <<(std::ostream& stream, Fire_Department& o){
	stream << "Structure: Fire Department \n";
	stream << "Name: " << o.name << "\n";
	stream << "Entrance: " << o.entrance << "\n";
	stream << "Location: " << o.location << "\n";

	return stream;
}



