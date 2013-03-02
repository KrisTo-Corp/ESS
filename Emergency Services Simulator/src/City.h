/*
 * City.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef CITY_H_
#define CITY_H_

#include <list>
#include <vector>
#include <string>

#include "CityObjects.h"
#include "Structures.h"
#include "Vehicles.h"
#include "Roads.h"

class City {
private:
	std::list<House> houses;
	std::list<Fire_Department> departments;
	std::list<Street> streets;
	std::list<Crossroad> crossroads;
	std::list<Firetruck> trucks;

public:
	City(std::string);
	void parseCity(std::string);
	virtual ~City();
};

#endif /* CITY_H_ */
