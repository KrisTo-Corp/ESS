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

int main(int argc, char **argv) {

	House house(4, 3, 20, "House 1");
	Fire_Department dep(5, 1, 2, 3, "Department 1");

	std::cout << house << std::endl;
	std::cout << dep << std::endl;



}
