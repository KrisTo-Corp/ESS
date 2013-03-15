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
#include <utility>

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

	City* _initCheck;

	Matrix matrix;

public:
	bool properlyInitialized(int, int);

	City(std::string filename);
//	ENSURE(init(), "Object 'City' was not properly initialized.");

	virtual ~City();

	friend std::ostream& operator <<(std::ostream& s, City& city);
//	REQUIRE(city.init(), "Object 'City' was not properly initialized when calling overloaded operator '<<'");

	void update();

private:
	bool init();
	std::pair<int, int> parseCity(std::string filename);
	void link_trucks_to_bases();
	bool validCoordCheck(int x, int y);
	int compareCoord(int, int);
	CityObjects* setFire();
	Coordinate getAdjecantStreet(Coordinate);
	std::string checkOrientation(Coordinate);
	Crossroad closestCrossroad(Coordinate);
	int calculateDistance(Coordinate, Coordinate);
};

#endif /* CITY_H_ */
