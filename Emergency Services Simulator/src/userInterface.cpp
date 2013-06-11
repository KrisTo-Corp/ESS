/*
 * userInterface.cpp
 *
 *  Created on: Jun 11, 2013
 *      Author: tom
 */

#include "userInterface.h"
#include <cstdlib>

userInterface::userInterface(City* c, bool b) {
	city = c;
	in_console = b;
	finished = false;
}

userInterface::~userInterface() {
	// TODO Auto-generated destructor stub
}

void userInterface::runUI(){
	printTitle();
	printMap();
	std::cout << std::endl;
	std::cout << "Press 'ENTER' to continue...";
	std::cin.ignore();
	while (!finished){
		printRealTimeMap();
		printMenu();
		makeChoice();
	}
	std::cout << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "THANK YOU FOR USING THE EMERGENCY SERVICES SIMULATOR !!!" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << std::endl;

}

void userInterface::printTitle(){

	if (in_console) std::cout << "\033[2J\033[1;1H";

	std::cout << std::endl;
	std::cout << "  _____                                                  ____                  _                 ____  _                 _       _             " << std::endl;
	std::cout << " | ____|_ __ ___   ___ _ __ __ _  ___ _ __   ___ _   _  / ___|  ___ _ ____   _(_) ___ ___  ___  / ___|(_)_ __ ___  _   _| | __ _| |_ ___  _ __ " << std::endl;
	std::cout << " |  _| | '_ ` _ \\ / _ \\ '__/ _` |/ _ \\ '_ \\ / __| | | | \\___ \\ / _ \\ '__\\ \\ / / |/ __/ _ \\/ __| \\___ \\| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|" << std::endl;
	std::cout << " | |___| | | | | |  __/ | | (_| |  __/ | | | (__| |_| |  ___) |  __/ |   \\ V /| | (_|  __/\\__ \\  ___) | | | | | | | |_| | | (_| | || (_) | |   " << std::endl;
	std::cout << " |_____|_| |_| |_|\\___|_|  \\__, |\\___|_| |_|\\___|\\__, | |____/ \\___|_|    \\_/ |_|\\___\\___||___/ |____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|   " << std::endl;
	std::cout << "                           |___/                 |___/                                                                                         " << std::endl << std::endl;
}

void userInterface::printMap(){
	std::cout << *(city->getMatrix()) << std::endl;
}

void userInterface::printRealTimeMap(){

	if (in_console) std::cout << "\033[2J\033[1;1H";
	std::cout << *(city->getMatrix()) << std::endl << std::endl;
}

void userInterface::printMenu(){
	std::cout << "Welcome to the menu:" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "\t 1. Set a fire." << std::endl;
	std::cout << "\t 2. Start a robbery." << std::endl;
	std::cout << "\t 3. Simulate turn." << std::endl;
	std::cout << "\t 4. Finish the simulation." << std::endl << std::endl;
}

void userInterface::makeChoice(){
	bool validnumber = false;
	int number = -1;
	while (!validnumber){
		std::cout << "Please enter the number corresponding to your choice: ";
		std::string number_str;
		std::cin >> number_str;
		number = atof(number_str.c_str());
		if (number > 0 && number <= 4) validnumber = true;
	}

	if (number == 1){
		setFireMenu();
	}
	else if (number == 2){
		startRobberyMenu();
	}
	else if (number == 3){
		if (in_console) std::cout << "\033[2J\033[1;1H";
		std::cout << std::endl;
		std::cout << "UPDATE REPORT:" << std::endl;
		std::cout << "--------------" << std::endl;
		singleSimulate(city);
		std::cout << std::endl;
		std::cout << "Press 'ENTER' to continue...";
		std::cin.ignore();
		std::cin.get();
	}
	else if (number == 4){
		finished = true;
	}
}

void userInterface::setFireMenu(){
	if (in_console) std::cout << "\033[2J\033[1;1H";

	std::cout << std::endl;
	std::cout << "Welcome to the set fire menu." << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "\t 1. Enter the coordinates for a fire." << std::endl;
	std::cout << "\t 2. Print the map." << std::endl;
	std::cout << "\t 3. Leave to the main menu." << std::endl << std::endl;

	bool validnumber = false;
	int number = -1;
	while (!validnumber){
		std::cout << "Please enter the number corresponding to your choice: ";
		std::string number_str;
		std::cin >> number_str;
		number = atof(number_str.c_str());
		if (number > 0 && number <= 3) validnumber = true;
	}

	if (number == 1){
		std::cout << std::endl;
		std::string x_str;
		std::string y_str;
		int x = -1;
		int y = -1;
		std::cout << "Please enter the x-coordinate: ";
		std::cin >> x_str;
		std::cout << "Please enter the y-coordinate: ";
		std::cin >> y_str;
		x = atof(x_str.c_str());
		y = atof(y_str.c_str());

		bool valid = city->validFireCoordinates(x, y);

		if (!valid){
			std::cout << std::endl;
			std::cout << "Sorry these coordinates were not valid." << std::endl;
			std::cout << "Now returning to the menu." << std::endl;
			std::cout << std::endl;
			std::cout << "Press 'ENTER' to continue...";
			std::cin.ignore();
			std::cin.get();
			setFireMenu();
		}
		else {
			city->setFire(x, y);
			std::cout << std::endl;
			std::cout << "The fire was set succesfully." << std::endl;
			std::cout << "Now returning to the main menu." << std::endl;
			std::cout << std::endl;
			std::cout << "Press 'ENTER' to continue...";
			std::cin.ignore();
			std::cin.get();
			return;
		}
	}
	else if (number == 2){
		printRealTimeMap();
		std::cout << std::endl;
		std::cout << "Press 'ENTER' to continue...";
		std::cin.ignore();
		std::cin.get();
		setFireMenu();
	}
	else if (number == 3){
		return;
	}
}

void userInterface::startRobberyMenu(){
	if (in_console) std::cout << "\033[2J\033[1;1H";

	std::cout << std::endl;
	std::cout << "Welcome to the start robbery menu." << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "\t 1. Enter the coordinates for a robbery." << std::endl;
	std::cout << "\t 2. Print the map." << std::endl;
	std::cout << "\t 3. Leave to the main menu." << std::endl << std::endl;

	bool validnumber = false;
	int number = -1;
	while (!validnumber){
		std::cout << "Please enter the number corresponding to your choice: ";
		std::string number_str;
		std::cin >> number_str;
		number = atof(number_str.c_str());
		if (number > 0 && number <= 3) validnumber = true;
	}

	if (number == 1){
		std::cout << std::endl;
		std::string x_str;
		std::string y_str;
		int x = -1;
		int y = -1;
		std::cout << "Please enter the x-coordinate: ";
		std::cin >> x_str;
		std::cout << "Please enter the y-coordinate: ";
		std::cin >> y_str;
		x = atof(x_str.c_str());
		y = atof(y_str.c_str());

		bool valid = city->validRobberyCoordinates(x, y);

		if (!valid){
			std::cout << std::endl;
			std::cout << "Sorry these coordinates were not valid." << std::endl;
			std::cout << "Now returning to the menu." << std::endl;
			std::cout << std::endl;
			std::cout << "Press 'ENTER' to continue...";
			std::cin.ignore();
			std::cin.get();
			startRobberyMenu();
		}
		else {
			city->robStore(x, y);
			std::cout << std::endl;
			std::cout << "The robbery was started succesfully." << std::endl;
			std::cout << "Now returning to the main menu." << std::endl;
			std::cout << std::endl;
			std::cout << "Press 'ENTER' to continue...";
			std::cin.ignore();
			std::cin.get();
			return;
		}
	}
	else if (number == 2){
		printRealTimeMap();
		std::cout << std::endl;
		std::cout << "Press 'ENTER' to continue...";
		std::cin.ignore();
		std::cin.get();
		startRobberyMenu();
	}
	else if (number == 3){
		return;
	}
}

