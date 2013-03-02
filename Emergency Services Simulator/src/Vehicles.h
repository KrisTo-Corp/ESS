/*
 * Vehicles.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef VEHICLES_H_
#define VEHICLES_H_

#include <string>
#include <ostream>

#include "Coordinate.h"

class Vehicles {
protected:
	const std::string name;
	Coordinate location;
public:
	Vehicles();
	Vehicles(const int, const int, const std::string);
	virtual ~Vehicles();
};

class Firetruck: public Vehicles {
private:
	const std::string basename;
public:
	Firetruck();
	Firetruck(int, int, const std::string, const std::string);
	friend std::ostream& operator <<(std::ostream&, Firetruck&);
};

#endif /* VEHICLES_H_ */
