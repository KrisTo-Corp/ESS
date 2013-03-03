//============================================================================
// Name        : TicTacToeMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

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


/*
	Matrix m(2, 2);

	House house(0, 0, 0, "house");
	Fire_Department dep(0, 0, 0, 0, "depar");
	Street s(0, 0, 0, 0, "stree");
	Crossroad c(0, 0, "cross");

	m.addObject(0, 0, &house);
	m.addObject(0, 1, &dep);
	m.addObject(1, 0, &s);
	m.addObject(1, 1, &c);

	std::cout << m << std::endl;
*/


}
