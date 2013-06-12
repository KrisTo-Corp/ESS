/*
 * Casualty.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: kristof
 */

#include "Casualty.h"

Casualty::Casualty() {
	hp = 10;
	state = hurt;
	home = NULL;

	_initCheck = this;
}

Casualty::Casualty(Structures* s) {
	hp = 10;
	state = hurt;
	home = s;

	_initCheck = this;

	ENSURE(properlyInitialized(), "Object 'Casualty' was not properly initialized.");
}

Casualty::~Casualty() {
	// TODO Auto-generated destructor stub
}

void Casualty::decreaseHP() {
	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling decreaseHP().");

	if (hp <= 0){
		state = dead;
		ENSURE(state == dead, "Method decreaseHP() of object 'Casualty' did not properly change state to 'dead'.");
	}
	else if (state == hurt || state == beingrescued) {
		int oldHp = hp;
		hp--;
		ENSURE(hp == oldHp-1, "Method decreaseHP() of object 'Casualty' did not properly decrease casualty's hp.");
	}
}
int Casualty::getHP() {
	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling getHP().");

	return hp;
}

status Casualty::getPState() {
	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling getPState().");

	return state;
}

void Casualty::setPassengerState(status s) {
	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling setPassengerState().");

	state = s;

	ENSURE(state == s, "Method setPassengerState(status) of object 'Casualty' did not properly set casualty's state.");
}

Structures* Casualty::getHome(){
	return home;
}

bool Casualty::properlyInitialized() {
	return _initCheck == this;
}

Casualty::Casualty(const Casualty& c) {
	REQUIRE(properlyInitialized(), "Object 'Structures' was not properly initialized when calling copy constructor");

	hp = c.hp;
	state = c.state;
	home = c.home;
	_initCheck = this;

}

Casualty& Casualty::operator =(const Casualty& c){

	hp = c.hp;
	state = c.state;
	home = c.home;
	_initCheck = this;

	return *this;
}
