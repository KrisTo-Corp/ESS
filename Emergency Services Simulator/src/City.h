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
#include <fstream>
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
	std::ofstream output;

	bool validCity;

	City* _initCheck;

	Matrix matrix;

public:
	bool properlyInitialized(int, int);

	City();

	City(std::string filename, std::string outputname);
//	ENSURE(init(), "Object 'City' was not properly initialized.");

	virtual ~City();

	friend std::ostream& operator <<(std::ostream& s, City& city);
//	REQUIRE(city.init(), "Object 'City' was not properly initialized when calling overloaded operator '<<'");

	int getAmountHouses();
	int getAmountDepartments();
	int getAmountStreets();
	int getAmountCrossroads();
	int getAmountTrucks();
	CityObjects* getObject(int, int);
	Firetruck* getTruck(int);

	City& operator =(const City&);

	void update();
	void update_test();

	void close();

	bool properlyInitialized();
	std::pair<int, int> parseCity(std::string filename);
	void link_trucks_to_bases();
	bool validCoordCheck(int x, int y);
	int compareCoord(int, int);
	CityObjects* setFire();
	CityObjects* setFire(int, int);
	Coordinate getAdjecantStreet(CityObjects*, Coordinate);
	std::string checkOrientation(Coordinate);
	Crossroad closestCorrectCrossroad(Coordinate, Street*);
	Crossroad closestCrossroad(Coordinate);
	int calculateDistance(Coordinate, Coordinate);
	void driveTruck(Firetruck*);
	bool integrityCheck();
};

#endif /* CITY_H_ */
