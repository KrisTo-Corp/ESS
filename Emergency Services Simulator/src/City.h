//=======================================================================================
// Name        : City.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : City in C++, Ansi-style
//=======================================================================================

#ifndef CITY_H_
#define CITY_H_

#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "CityObjects.h"
#include "Structures.h"
#include "Vehicles.h"
#include "Roads.h"
#include "Matrix.h"

class City {
private:
	std::list<House> houses;
	std::list<Fire_Department> departments;
	std::list<Street> streets;
	std::list<Crossroad> crossroads;
	std::list<Firetruck> trucks;

	Matrix matrix;

public:
	City(std::string filename);
	virtual ~City();

	friend std::ostream& operator <<(std::ostream& s, City& city);

private:
	void parseCity(std::string filename);
	void link_trucks_to_bases();
	bool validCoordCheck(int x, int y);
};

#endif /* CITY_H_ */
