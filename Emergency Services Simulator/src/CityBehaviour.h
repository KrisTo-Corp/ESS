/*
 * CityBehaviour.h
 *
 *  Created on: Apr 11, 2013
 *      Author: kristof
 */

#ifndef CITYBEHAVIOUR_H_
#define CITYBEHAVIOUR_H_

class CityBehaviour {
private:
	City* city;
public:
	CityBehaviour(City*);
	virtual ~CityBehaviour();

	CityObjects* setFire();
	CityObjects* setFire(int, int);
	void driveTruck(Firetruck* rescueTruck);
};

#endif /* CITYBEHAVIOUR_H_ */
