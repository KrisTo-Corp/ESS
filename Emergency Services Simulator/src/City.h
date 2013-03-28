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

	bool validCity;

	City* _initCheck;

	Matrix matrix;

public:
	City();

	std::ofstream output;

	City(std::string filename, std::string outputname);
//	ENSURE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized.");

	//City(const std::string filename, std::ofstream stream);


	friend std::ostream& operator <<(std::ostream& s, City& city);
//	REQUIRE(city.properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling overloaded operator '<<'");

	int getAmountHouses();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountHouses()");

	int getAmountDepartments();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountDepartments()");

	int getAmountStreets();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountStreets()");

	int getAmountCrossroads();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountCrossroads()");

	int getAmountTrucks();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountTrucks()");

	CityObjects* getObject(int, int);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountTrucks()");

	Firetruck* getTruck(int);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountTrucks()");

	City& operator =(const City&);

	void update();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update()");

	void update_test();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update_test()");

	void close();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling close()");
//	ENSURE(!(output.is_open()), "File did not close properly when calling close()");

	std::pair<int, int> parseCity(std::string filename);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling parseCity()");

	bool validCoordCheck(int x, int y);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling validCoordCheck()");

	CityObjects* setFire();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling setFire()");
//	ENSURE(->getState() == burning, "setFire() did not correctly set fire to a house.");

	CityObjects* setFire(int, int);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling setFire()");
//	ENSURE(->getState() == burning, "setFire() did not correctly set fire to the given house.");

	Coordinate getAdjecantStreet(CityObjects*, Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAdjecantStreet()");

	std::string checkOrientation(Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling checkOrientation()");
//	REQUIRE((matrix.getObject(coord.getX(), coord.getY()))->getType() == street || (matrix.getObject(coord.getX(), coord.getY()))->getType() == crossroad, "I can not determine the orientation of anything non-street.");

	Crossroad closestCorrectCrossroad(Coordinate, Street*);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling closestCorrectCrossroad()");

	Crossroad closestCrossroad(Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling closestCrossroad()");

	int calculateDistance(Coordinate, Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling calculateDistance()");

	void driveTruck(Firetruck*);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling driveTruck()");

	bool integrityCheck();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling integrityCheck()");

	int compareCoord(int, int);

	void link_trucks_to_bases();

	bool properlyInitialized(int, int);

	bool properlyInitialized();

	std::list<Firetruck>* getTruckList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getTruckList()");

	std::list<House>* getHouseList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getHouseList()");

	std::list<Fire_Department>* getDepList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getDepList()");

	std::list<Street>* getStreetsList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getStreetList()");

	Matrix* getMatrix();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getMatrix()");

	bool getValidCity();

	virtual ~City();
};

#endif /* CITY_H_ */
