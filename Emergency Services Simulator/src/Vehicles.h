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

class Fire_Department;

class Vehicles {
protected:
	const std::string name;
	Coordinate location;

	Vehicles* _initCheck;

public:
	Vehicles();
	//	ENSURE(init(), "Object 'Vehicles' was not properly initialized.");

	Vehicles(int x, int y, const std::string n);
	//	ENSURE(init(), "Object 'Vehicles' was not properly initialized.");

	virtual ~Vehicles();

	virtual bool init();

	void resetInit();
};

class Firetruck: public Vehicles {
private:
	Coordinate coord;
	const std::string basename;
	Fire_Department* base;

public:
	Firetruck();

	Firetruck(const int x, const int y, const std::string n, const std::string bn);

	virtual ~Firetruck();

	void linkBase(Fire_Department* dep_ptr);
	//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling linkBase().");

	std::string getBasename();
	//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBasename().");

	Fire_Department* getBaseptr();
	//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	void move(std::string);

	void setCoord(Coordinate);

	friend std::ostream& operator <<(std::ostream& s, Firetruck& truck);
};

#endif /* VEHICLES_H_ */
