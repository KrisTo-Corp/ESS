//=======================================================================================
// Name        : City.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : City in C++, Ansi-style
//=======================================================================================

#include "City.h"

City::City(const std::string filename){

	std::pair<int, int> maxCoords =	parseCity(filename);


	std::cout << maxCoords.first << " " << maxCoords.second << std::endl;

	for (std::list<Firetruck>::iterator it = trucks.begin(); it != trucks.end(); it++) {
		it->resetInit();
	}

	for (std::list<House>::iterator it = houses.begin(); it != houses.end(); it++) {
		it->resetInit();
	}

	for (std::list<Fire_Department>::iterator it = departments.begin(); it != departments.end(); it++) {
		it->resetInit();
	}

	for (std::list<Street>::iterator it = streets.begin(); it != streets.end(); it++) {
		it->resetInit();
	}

	link_trucks_to_bases();
	matrix.addHouses(houses);
	matrix.addFiredeps(departments);
	crossroads = matrix.addStreets(streets);
	matrix.addCrossroads(crossroads);

	for (std::list<Crossroad>::iterator it = crossroads.begin(); it != crossroads.end(); it++) {
		it->resetInit();
	}
	_initCheck = this;

	ENSURE(init(), "Object 'City' was not properly initialized.");
}

City::~City()
{
}

std::ostream& operator <<(std::ostream& s, City& city) {
	REQUIRE(city.init(), "Object 'City' was not properly initialized when calling overloaded operator '<<'");

	s << city.matrix << "\n";
	return s;
}

void City::link_trucks_to_bases() {
	std::list<Firetruck>::iterator it_t;
	std::list<Fire_Department>::iterator it_dep;
	for (it_t = trucks.begin(); it_t != trucks.end(); it_t++) {
		std::string basename = it_t->getBasename();
		for (it_dep = departments.begin(); it_dep != departments.end(); it_dep++) {
			std::string dep_name = it_dep->getName();
			if (basename == dep_name) {
				Fire_Department* dep_ptr = &(*it_dep);
				it_t->linkBase(dep_ptr);
			}
		}
		if (it_t->getBaseptr() == NULL){
			std::cerr << "Base doesn't exist -> Truck was not linked.\n";
		}
	}
}

bool City::init() {
	return _initCheck == this;
}

bool City::properlyInitialized(int x, int y){
	return matrix.properlyInitialized(x, y);
}
