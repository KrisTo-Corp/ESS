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
public:
	Casualty(Structures*);
	virtual ~Casualty();

	status getPState();
	int getHP();
	Structures* getHome();
	void decreaseHP();
	void setPassengerState(status );
};

#endif /* CASUALTY_H_ */
