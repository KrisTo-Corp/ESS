//============================================================================
// Name        : TicTacToeMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "Structures.h"
#include "Roads.h"

int main(int argc, char **argv) {

	House house(4, 3, 20, "House 1");
	Fire_Department dep(5, 1, 2, 3, "Department 1");
	Street street(1, 2, 3, 4, "Leo Metsstraat");
	Crossroad cross(9, 8, "'t hoekske");


	std::cout << house << std::endl;
	std::cout << dep << std::endl;
	std::cout << street << std::endl;
	std::cout << cross << std::endl;



}
