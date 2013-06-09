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
		bool found_dot = false;
		bool html = false;
		for(int i = 0; i < argv2.size(); i++){
			if(argv2[i] == '.'){
				found_dot = true;
			}
			if (found_dot){
				if (argv2[i+1] == 'h' && argv2[i+2] == 't' && argv2[i+3] == 'm' && argv2[i+4] == 'l'){
					html = true;
				}
			}
		}

		if (argv2 == "console") {
			City city(argv[1], std::cout);
			simulateCity(city);

			/*
			 * Experimental CGFX integration
			 */
			Matrix* theMatrix = city.getMatrix();
			theMatrix->generateGFX();
			return 0;
		}
		if (html) {
			std::ofstream filestream(argv[2]);
			City city(argv[1], filestream, "empty", true);
			simulateCity(city);
			city.o.closeHTML();
			std::cout << "Output was written to " << argv2 << ".\n";
			return 0;
		}
		else {
			std::ofstream filestream(argv[2]);
			City city(argv[1], filestream);
			simulateCity(city);
			filestream.close();
			std::cout << "Output was written to " << argv2 << ".\n";
			return 0;
		}
	}

	else{

		std::string argv2 = argv[2];
		bool found_dot = false;
		bool html = false;
		for(int i = 0; i < argv2.size(); i++){
			if(argv2[i] == '.'){
				found_dot = true;
			}
			if (found_dot){
				if (argv2[i+1] == 'h' && argv2[i+2] == 't' && argv2[i+3] == 'm' && argv2[i+4] == 'l'){
					html = true;
				}
			}
		}

		if (argv2 == "console") {
			City city(argv[1], std::cout, argv[3]);
			simulateCity(city);

			/*
			 * Experimental CGFX integration
			 */
			Matrix* theMatrix = city.getMatrix();
			theMatrix->generateGFX();
			return 0;
		}
		if (html) {
			std::ofstream filestream(argv[2]);
			City city(argv[1], filestream, argv[3], true);
			simulateCity(city);
			city.o.closeHTML();
			std::cout << "Output was written to " << argv2 << ".\n";
			return 0;
		}
		else {
			std::ofstream filestream(argv[2]);
			City city(argv[1], filestream, argv[3]);
			simulateCity(city);
			filestream.close();
			std::cout << "Output was written to " << argv2 << ".\n";
			return 0;
		}
	}
}
