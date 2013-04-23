/*
 * Casualty.h
 *
 *  Created on: Apr 23, 2013
 *      Author: kristof
 */

#ifndef CASUALTY_H_
#define CASUALTY_H_

class Casualty {
private:
	//int id;
	int hp;
	bool inCare;
public:
	Casualty();
	virtual ~Casualty();

	int getHP();
	bool getInCare();
	void decreaseHP();
	int getID();
};

#endif /* CASUALTY_H_ */
