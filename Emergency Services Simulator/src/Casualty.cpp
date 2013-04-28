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



// =============================
//	    TESTS FOR CASUALTY
// =============================

TEST_F(CasualtyTest, CasualtyDefaultConstructor){
	EXPECT_TRUE(casualty.properlyInitialized());
	EXPECT_EQ(10, casualty.getHP());
	EXPECT_EQ(hurt, casualty.getPState());
	EXPECT_EQ(NULL, casualty.getHome());
}

TEST_F(CasualtyTest, CasualtyConstructor){
	Structures structure;
	casualty = Casualty(&structure);
	EXPECT_TRUE(casualty.properlyInitialized());
	EXPECT_EQ(10, casualty.getHP());
	EXPECT_EQ(hurt, casualty.getPState());
	EXPECT_EQ(&structure, casualty.getHome());
}

TEST_F(CasualtyTest, CasualtySetStateFunction){
	EXPECT_EQ(hurt, casualty.getPState());
	casualty.setPassengerState(beingrescued);
	EXPECT_EQ(beingrescued, casualty.getPState());
	casualty.setPassengerState(inCare);
	EXPECT_EQ(inCare, casualty.getPState());
	casualty.setPassengerState(dead);
	EXPECT_EQ(dead, casualty.getPState());
}

TEST_F(CasualtyTest, CasualtyDecreaseHP){
	EXPECT_EQ(10, casualty.getHP());
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	EXPECT_EQ(7, casualty.getHP());
	casualty.setPassengerState(beingrescued);
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	EXPECT_EQ(4, casualty.getHP());
	casualty.setPassengerState(inCare);
	casualty.decreaseHP();
	EXPECT_EQ(4, casualty.getHP());
	casualty.setPassengerState(beingrescued);
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	EXPECT_EQ(0, casualty.getHP());
	EXPECT_EQ(dead, casualty.getHP());
}
