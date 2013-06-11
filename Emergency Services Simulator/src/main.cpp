//============================================================================
// Name        : TicTacToeTests.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>

#include "City.h"
#include "Simulator.h"
#include "userInterface.h"


int main(int argc, char **argv) {

	srand(time(NULL));

	if (argc < 2){
		std::cerr << "Usage: ./Release [MODE]" << std::endl << "\tMode: simulation, UI, GFX." << std::endl << "\tEnter one of the modes for more information !" << std::endl << std::endl;
		return 0;
	}

	std::string mode = argv[1];
	for (int i = 0; i < mode.size(); i++) mode[i] = tolower(mode[i]);

	if (mode == "ui"){
		if (argc == 4){
			std::string inputfile = argv[2];
			std::string realConsole = argv[3];
			bool in_console = false;
			for(int i = 0; i < realConsole.size(); i++) realConsole[i] = tolower(realConsole[i]);
			if (realConsole == "true") in_console = true;

			City city(inputfile, std::cout, "empty", false, true);
			userInterface ui(&city, in_console);
			ui.runUI();
			return 0;
		}
		else if (argc == 5){
			std::string inputfile = argv[2];
			std::string inputfile_vehicles = argv[3];
			std::string realConsole = argv[4];
			bool in_console = false;
			for(int i = 0; i < realConsole.size(); i++) realConsole[i] = tolower(realConsole[i]);
			if (realConsole == "true") in_console = true;

			City city(inputfile, std::cout, inputfile_vehicles, false, true);
			userInterface ui(&city, in_console);
			ui.runUI();
			return 0;
		}
		else {
			std::cerr << "Usage: ./Release [SIMULATION] [CITY XML FILE] [VEHICLE XML FILE]* [REAL CONSOLE]" << std::endl << "\t* OPTIONAL" << std::endl << std::endl;
			return 0;
		}
	}

	else if (mode == "simulation"){
		if (argc == 4){
			std::string inputfile = argv[2];
			std::string outputfile = argv[3];
			bool found_dot = false;
			bool html = false;
			for(int i = 0; i < outputfile.size(); i++){
				if(outputfile[i] == '.'){
					found_dot = true;
				}
				if (found_dot){
					if (outputfile[i+1] == 'h' && outputfile[i+2] == 't' && outputfile[i+3] == 'm' && outputfile[i+4] == 'l'){
						html = true;
					}
				}
			}

			if (outputfile == "console"){
				City city(inputfile, std::cout);
				simulateCity(city);
				return 0;
			}
			else if (html){
				std::ofstream outputstream(outputfile.c_str());
				City city(inputfile, outputstream, "empty", true);
				simulateCity(city);
				city.o.closeHTML();
				std::cout << "Output was written to " << outputfile << ".\n";
				return 0;
			}
			else {
				std::ofstream outputstream(outputfile.c_str());
				City city(inputfile, outputstream);
				simulateCity(city);
				std::cout << "Output was written to " << outputfile << ".\n";
				return 0;
			}
		}
		else if (argc == 5){
			std::string inputfile = argv[2];
			std::string inputfile_vehicles = argv[3];
			std::string outputfile = argv[4];
			bool found_dot = false;
			bool html = false;
			for(int i = 0; i < outputfile.size(); i++){
				if(outputfile[i] == '.'){
					found_dot = true;
				}
				if (found_dot){
					if (outputfile[i+1] == 'h' && outputfile[i+2] == 't' && outputfile[i+3] == 'm' && outputfile[i+4] == 'l'){
						html = true;
					}
				}
			}

			if (outputfile == "console"){
				City city(inputfile, std::cout, inputfile_vehicles);
				simulateCity(city);
				return 0;
			}
			else if (html){
				std::ofstream outputstream(outputfile.c_str());
				City city(inputfile, outputstream, inputfile_vehicles, true);
				simulateCity(city);
				city.o.closeHTML();
				std::cout << "Output was written to " << outputfile << ".\n";
				return 0;
			}
			else {
				std::ofstream outputstream(outputfile.c_str());
				City city(inputfile, outputstream, inputfile_vehicles);
				simulateCity(city);
				std::cout << "Output was written to " << outputfile << ".\n";
				return 0;
			}
		}
		else {
			std::cerr << "Usage: ./Release [SIMULATION] [CITY XML FILE] [VEHICLE XML FILE]* [OUTPUT FILE]" << std::endl << "\t* OPTIONAL" << std::endl << std::endl;
			return 0;
		}
	}

	else if (mode == "gfx"){
		if (argc == 4){
			std::string inputfile = argv[2];
			std::string outputfile = argv[3];
			City city(inputfile, std::cout, "empty", false, true);
			city.getMatrix()->generateGFX(outputfile);
			std::string command = "./GFXexecutable";
			command += " " + outputfile;
			system(command.c_str());
			std::cout << "Ini file was generated: " << outputfile << "." << std::endl;
			outputfile[outputfile.size()-1] = 'p';
			outputfile[outputfile.size()-2] = 'm';
			outputfile[outputfile.size()-3] = 'b';
			std::cout << "Image was generated: " << outputfile << "." << std::endl;
		}
	}
}
