/*
 * Simulator.h
 *
 *  Created on: Mar 28, 2013
 *      Author: kristof
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "City.h"
#include "DesignByContract.h"

void simulateCity(City&);

void simulateCity_Test(City& city,
		Coordinate& Fire_location1, Coordinate& Fire_location2, int turns_fire,
		Coordinate& Rob_location1 = Coordinate(-1, -1), Coordinate& Rob_location2 = Coordinate(-1, -1), int turns_robbery = -1);


#endif /* SIMULATOR_H_ */
