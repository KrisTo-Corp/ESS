//=======================================================================================
// Name        : Vehicles.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Vehicles in C++, Ansi-style
//=======================================================================================

#ifndef VEHICLES_H_
#define VEHICLES_H_

#include <string>
#include <ostream>

#include "Coordinate.h"
#include "Structures.h"

class Vehicles {
protected:
	const std::string name;
	Coordinate location;

public:
	Vehicles();
	Vehicles(int x, int y, const std::string n);
	virtual ~Vehicles();
};



class Firetruck: public Vehicles {
private:
	const std::string basename;
	Fire_Department* base;

public:
	Firetruck();
	Firetruck(const int x, const int y, const std::string n, const std::string bn);
	virtual ~Firetruck();

	void linkBase(Fire_Department* dep_ptr);
	std::string getBasename()const;
	Fire_Department* getBaseptr();
	friend std::ostream& operator <<(std::ostream& s, Firetruck& truck);
};

#endif /* VEHICLES_H_ */
