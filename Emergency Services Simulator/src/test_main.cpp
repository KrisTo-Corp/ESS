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

	House house;
	Fire_Department dep;
	Street s;
	Crossroad c;

	m.addObject(&house, 0, 0);
	m.addObject(&dep, 0, 1);
	m.addObject(&s, 1, 0);
	m.addObject(&c, 1, 1);


	std::cout << m << std::endl;

}
