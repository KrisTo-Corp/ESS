/*
 * userInterface.h
 *
 *  Created on: Jun 11, 2013
 *      Author: tom
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <iostream>
#include "City.h"
#include "Simulator.h"

class userInterface {
	City* city;
	bool in_console;
	bool finished;
public:
	userInterface(City* c, bool b);
	void runUI();
	void printTitle();
	void printMap();
	void printRealTimeMap();
	void printMenu();
	void makeChoice();
	void setFireMenu();
	void startRobberyMenu();
	virtual ~userInterface();
};

#endif /* USERINTERFACE_H_ */
