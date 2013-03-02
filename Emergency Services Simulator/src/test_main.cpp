//============================================================================
// Name        : TicTacToeMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "CityObjects.h"
#include "Structures.h"
#include "Roads.h"
#include "Vehicles.h"
#include "Matrix.h"

int main(int argc, char **argv) {

	Matrix m;

	House house(0, 0, 20, "H1");
	Fire_Department dep(0, 0, 0, 0, "D1");
	Street s(0, 0, 0, 0, "S1");
	Crossroad c(0, 0, "C1");

	m.addObject(&house, 0, 0);
	m.addObject(&dep, 0, 1);
	m.addObject(&s, 1, 0);
	m.addObject(&c, 1, 1);
	m.addObject(&house, 0, 2);
	m.addObject(&dep, 3, 3);


	std::cout << m << std::endl;

}
