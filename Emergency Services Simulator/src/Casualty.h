/*
 * Casualty.h
 *
 *  Created on: Apr 23, 2013
 *      Author: kristof
 */

#ifndef CASUALTY_H_
#define CASUALTY_H_

#include "Structures.h"

class Structures;

enum status {dead, inCare, beingrescued, hurt};

class Casualty {
private:
	status state;
	Structures* home;
	int hp;

	Casualty* _initCheck;
public:
	Casualty();

	Casualty(Structures*);
//	ENSURE(properlyInitialized(), "Object 'Casualty' was not properly initialized.");
	virtual ~Casualty();

	status getPState();
//	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling getPState().");

	int getHP();
//	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling getHP().");

	Structures* getHome();
//	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling getHome().");

	void decreaseHP();
//	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling decreaseHP().");
//	ENSURE(hp == oldHp-1, "Method decreaseHP() of object 'Casualty' did not properly decrease casualty's hp.");
//	OR
// 	ENSURE(state == dead, "Method decreaseHP() of object 'Casualty' did not properly change state to 'dead'.");

	void setPassengerState(status);
//	REQUIRE(properlyInitialized(), "Object 'Casualty' was not properly initialized when calling setPassengerState().");
//	ENSURE(state == status, "Method setPassengerState(status) of object 'Casualty' did not properly set casualty's state.");

	Casualty(const Casualty& c);
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling copy constructor");

	Casualty& operator =(const Casualty&);

	bool properlyInitialized();
};

class CasualtyTest: public ::testing::Test {
protected:
	friend class Casualty;

	Casualty casualty;
};

#endif /* CASUALTY_H_ */
