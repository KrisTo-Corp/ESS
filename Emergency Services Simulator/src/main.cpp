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
#include "Simulator.h"

int main(int argc, char **argv) {

	srand(time(NULL));

	if (argc < 2){
		std::cerr << "Usage: ./Release \"XML FILE\" \"OUTPUT FILE\"(optional)" << std::endl << std::endl;
	}
	else if (argc == 2) {
		std::ofstream filestream("output.txt");
		City city(argv[1], filestream);
		simulateCity(city);
		filestream.close();
		std::cout << "output was written to \"output.txt\"" << std::endl;
	}
	else{
		std::string argv2 = argv[2];
		if (argv2 == "cout") {
			City city(argv[1], std::cout);
			simulateCity(city);
		}
		else {
			std::ofstream filestream(argv[2]);
			City city(argv[1], filestream);
			simulateCity(city);
			filestream.close();
			std::cout << "output was written to " << argv2 << std::endl;
		}
	}
}
