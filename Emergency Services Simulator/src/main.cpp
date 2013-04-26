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

	if (argc < 3){
		std::cerr << "Usage: ./Release \"XML FILE\" \"OUTPUT NAME\" \"VEHICLES XML FILE\ (optional)" << std::endl << std::endl;
	}
	else if (argc == 3) {
		std::string argv2 = argv[2];
		if (argv2 == "cout") {
			City city(argv[1], std::cout);
			simulateCity_Test(city, Coordinate(20, 1), Coordinate(8, 14), 10, Coordinate(10, 11), Coordinate(13, 8), 15);
		}
		else if (argv2 == "html") {
			std::ofstream filestream("ems.html");
			City city(argv[1], filestream, "empty", true);
			simulateCity_Test(city, Coordinate(20, 1), Coordinate(8, 14), 10, Coordinate(10, 11), Coordinate(13, 8), 15);
			city.o.closeHTML();
		}
		else {
			std::ofstream filestream(argv[2]);
			City city(argv[1], filestream);
			std::cout << "constructed" << std::endl;
			simulateCity_Test(city, Coordinate(20, 1), Coordinate(8, 14), 10, Coordinate(10, 11), Coordinate(13, 8), 15);
			std::cout << "simulated" << std::endl;
			filestream.close();
			std::cout << "output was written to " << argv2 << std::endl;
		}
	}
	else{
		std::string argv2 = argv[2];
		if (argv2 == "cout") {
			City city(argv[1], std::cout, argv[3]);
			simulateCity_Test(city, Coordinate(20, 1), Coordinate(8, 14), 10, Coordinate(10, 11), Coordinate(13, 8), 15);
		}
		else if (argv2 == "html") {
			std::ofstream filestream("ems.html");
			City city(argv[1], filestream, argv[3], true);
			simulateCity_Test(city, Coordinate(20, 1), Coordinate(8, 14), 10, Coordinate(10, 11), Coordinate(13, 8), 15);
			city.o.closeHTML();
		}
		else {
			std::ofstream filestream(argv[2]);
			City city(argv[1], filestream, argv[3]);
			simulateCity_Test(city, Coordinate(20, 1), Coordinate(8, 14), 10, Coordinate(10, 11), Coordinate(13, 8), 15);
			filestream.close();
			std::cout << "output was written to " << argv2 << std::endl;
		}
	}
}
