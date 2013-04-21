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
#include <sstream>
#include <utility>

#include "helpers.h"
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
	std::list<Store> stores;
	std::list<Hospital> hospitals;
	std::list<PoliceStation> poliStats;
	std::list<PoliceCar> policecars;
	std::list<Ambulance> ambulances;

	bool validCity;

	City* _initCheck;

	Matrix matrix;

public:
	City();

	OutputObject o;

	City(std::string filename, std::ostream&, std::string vehiclesXML = "empty", bool html = false);
//	ENSURE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized.");

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

	int getAmountCars();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountCars()");


	CityObjects* getObject(int, int);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountTrucks()");

	Firetruck* getTruck(int);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountTrucks()");

	void update();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update()");

	void update_test();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update_test()");

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

	void driveTruck(Vehicles*);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling driveTruck()");

	bool integrityCheck();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling integrityCheck()");

	std::list<Firetruck>* getTruckList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getTruckList()");

	std::list<House>* getHouseList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getHouseList()");

	std::list<Fire_Department>* getDepList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getDepList()");

	std::list<Street>* getStreetsList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getStreetList()");

	std::list<Store>* getStoresList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getStoresList()");

	std::list<Hospital>* getHospitalsList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getHospitalsList()");

	std::list<PoliceStation>* getPoliStatsList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getPoliceCarsList()");

	std::list<PoliceCar>* getPoliceCarsList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getPolStatsList()");

	std::list<Ambulance>* getAmbulancesList();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmbulancesList()");

	Matrix* getMatrix();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getMatrix()");

	Store* robStore();
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling robStore()");

	Store* robStore(int, int);
//	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling robStore(int, int)");

	Coordinate getAdjecantBuilding(CityObjects*);

	bool getValidCity();

	void link_vehicles_to_bases();

	bool properlyInitialized(int, int);

	bool properlyInitialized();

	City& operator =(const City&);

	virtual ~City();
};

#endif /* CITY_H_ */
