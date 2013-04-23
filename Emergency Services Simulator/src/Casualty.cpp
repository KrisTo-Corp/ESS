/*
 * Casualty.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: kristof
 */

#include "Casualty.h"

Casualty::Casualty(Structures* s) {
	hp = 10;
	state = hurt;
	home = s;

}

Casualty::~Casualty() {
	// TODO Auto-generated destructor stub
}

void Casualty::decreaseHP() {
	if (hp <= 0){
		state = dead;
	}
	else if (state == hurt || state == beingrescued) {
		hp--;
	}
}
int Casualty::getHP() {
	return hp;
}

status Casualty::getPState() {
	return state;
}

void Casualty::setPassengerState(status s) {
	state = s;
}

Structures* Casualty::getHome(){
	return home;
}
