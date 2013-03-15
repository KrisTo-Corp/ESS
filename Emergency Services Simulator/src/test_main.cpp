//=======================================================================================
// Name        : test_main.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Main test file in C++, Ansi-style
//=======================================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "City.h"
#include "CityObjects.h"
#include "Structures.h"
#include "Roads.h"
#include "Vehicles.h"
#include "Matrix.h"

int main(int argc, char **argv) {

	srand(time(NULL));

	City city("stad.xml");

	city.update();

	std::cout << "Finished running, biatch v1.0 shizz" << std::endl;
}

/*
 * TODO: -> Find min and max coordinates in order to make our matrix of variable size depending on the XML file.
 * 			We need to include a method that finds these coordinates and passes them to the matrix constructor...
 * 			Maybe we could make a new Matrix object in our City constructor (Since we have parsed the city by then) and copy construct our city's matrix with the new one we made? :D
 *
 * TODO: -> Output
 * 	        What we have so far is friggin' awesome. Great work with adding the coordinates!
 * 	        What we need more:
 *
 * 	        Burning houses:
 * 	        	-> House on location (x,y)
 * 	        Firetrucks on their way:
 * 	        	-> {FIRETRUCK NAME} on location (x,y) in Javastreet.
 * 	        Available firetrucks in firedepartment {FIREDEPNAME}:
 * 	        	-> {FIRETRUCK NAME}
 *
 * TODO: Contracts
 *
 * TODO: TESTS, TESTS, TESTS! We need to check whether or not our parser reacts in a proper way if we feed it wrong input.
 *
 *
 */
