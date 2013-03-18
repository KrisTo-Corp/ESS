//============================================================================
// Name        : TicTacToeTests.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include "City.h"


int main(int argc, char **argv) {

	srand(time(NULL));

	if (argc < 2){
		std::cerr << "Usage: ./Release \"XML FILE\" \"OUTPUT FILE\"(optional)" << std::endl << std::endl;
	}
	else if (argc == 2) {
		City city(argv[1], "output.txt");
		city.update();
		city.close();
		std::cout << "output was written to \"output.txt\"" << std::endl;
	}
	else{
		City city(argv[1], argv[2]);
		city.update();
		city.close();
		std::cout << "output was written to " << argv[2] << std::endl;
	}
}
