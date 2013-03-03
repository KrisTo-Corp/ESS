/*
 * City.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include "City.h"

City::City(const std::string filename){
	parseCity(filename);
	link_trucks_to_bases();
	matrix.addHouses(houses);
	matrix.addFiredeps(departments);
	crossroads = matrix.addStreets(streets);
	matrix.addCrossroads(crossroads);
	std::cout << "ALL INITIALIZED" << std::endl;
}

void City::print() {
	std::cout << matrix << std::endl;
}

void City::printObject(int x, int y) {
	matrix.printObject(x, y);
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
	}

	/*
	 * Check if base exists
	 */
}


City::~City() {
	// TODO Auto-generated destructor stub
}

