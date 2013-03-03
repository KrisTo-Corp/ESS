//============================================================================
// Name        : City.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - Kristof De Middelaer & Tom Roels - University of Antwerp
// Description : City in C++, Ansi-style
//============================================================================

#include "City.h"

City::City(const std::string filename){
	REQUIRE(typeid(filename) == typeid(std::string), "The city constructor requires a string as filename.");

	_initCheck = this;
	parseCity(filename);
	link_trucks_to_bases();
	matrix.addHouses(houses);
	matrix.addFiredeps(departments);
	crossroads = matrix.addStreets(streets);
	matrix.addCrossroads(crossroads);

	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");
}

std::ostream& operator<<(std::ostream& stream, City& o){
	REQUIRE(o.properlyInitialized(), "The city was not properly initialized when pushing to stream.");

	stream << o.matrix << std::endl;
	return stream;
}

void City::link_trucks_to_bases() {
	// PRIVATE METHOD DOES NOT HAVE POST OR PRE CONDITIONS.

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
			std::cerr << "The basename: '" + it_t->getBasename() + "', did not exist. Truck with name: '" + it_t->getName() + "', was not linked.\n";
		}
	}
}

bool City::properlyInitialized(){
	// PRIVATE METHOD DOES NOT HAVE POST OR PRE CONDITIONS.

	return _initCheck == this;
}

