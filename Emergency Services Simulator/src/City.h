//============================================================================
// Name        : City.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - Kristof De Middelaer & Tom Roels - University of Antwerp
// Description : City in C++, Ansi-style
//============================================================================

#ifndef CITY_H_
#define CITY_H_

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

#include "CityObjects.h"
#include "Structures.h"
#include "Vehicles.h"
#include "Roads.h"
#include "Matrix.h"
#include "DesignByContract.h"

class City {
private:
	std::list<House> houses;
	std::list<Fire_Department> departments;
	std::list<Street> streets;
	std::list<Crossroad> crossroads;
	std::list<Firetruck> trucks;

	Matrix matrix;

	City* _initCheck;

public:
	City(std::string filename);
//	REQUIRE(typeid(filename) == typeid(std::string), "The city constructor requires a string as filename.");
//	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");

	friend std::ostream& operator <<(std::ostream& stream, City& o);
//	REQUIRE(o.properlyInitialized(), "The city was not properly initialized when pushing to stream.");

private:
	void parseCity(std::string);

	void link_trucks_to_bases();

	bool properlyInitialized();
};

#endif /* CITY_H_ */
