/*
 * Casualty.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: kristof
 */

#include "Casualty.h"

Casualty::Casualty() {
	//id = id_nr;
	hp = 10;
	inCare = false;
}

Casualty::~Casualty() {
	// TODO Auto-generated destructor stub
}

void Casualty::decreaseHP() {
	if (!inCare) {
		hp--;
	}
}
int Casualty::getHP() {
	return hp;
}

bool Casualty::getInCare() {
	return inCare;
}

/*int Casualty::getID() {
	return id;
}*/
