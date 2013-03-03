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

	City city("stad.xml");

	std::cout << city << std::endl;
}
