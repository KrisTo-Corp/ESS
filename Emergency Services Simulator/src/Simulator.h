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

void simulateCity_Test(City&, Coordinate, Coordinate);


#endif /* SIMULATOR_H_ */
