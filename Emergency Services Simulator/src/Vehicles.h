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

class Structures;
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

	const std::string getName()const;

	virtual bool init();
	void resetInit();
};

class Firetruck: public Vehicles {
private:
	Coordinate coord;
	Coordinate tempDestination;
	Coordinate destination;
	Structures* target;
	bool goToTemp;
	bool available;
	bool atHome;

	const std::string basename;
	Fire_Department* base;


public:
	Firetruck();

	Firetruck(const int x, const int y, const std::string n, const std::string bn);

	virtual ~Firetruck();

	void linkBase(Fire_Department* dep_ptr);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling linkBase().");
//	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match Firetruck's base*.");

	std::string getBasename();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBasename().");

	Fire_Department* getBaseptr();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	void move(std::string);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling move().");

	void setCoord(Coordinate);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setCoord().");

	Coordinate getCoord();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getCoord().");

	void setTempDest(Coordinate);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setTempDest().");

	Coordinate getTempDest();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getTempDest().");

	Structures* getTarget();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getTarget().");

	void setTarget(Structures* t);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setTarget().");
//	ENSURE((getTarget() == t), "Setted target does not match Firetruck's target.");

	void setDestination(Coordinate dest);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setDestination().");
//	ENSURE((getDestination() == dest), "Setted destination does not match Firetruck's destination.");

	Coordinate getDestination();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getDestination().");

	void setGoToTemp(bool v);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setGoToTemp().");
//	ENSURE((getGoToTemp() == v), "Setted GoToTemp does not match Firetruck's GoToTemp.");

	bool getGoToTemp();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getGoToTemp().");

	bool getAvailable();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getAvailable().");

	void setAvailable(bool state);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setAvailable().");
//	ENSURE((getAvailable() == state), "Setted available does not match Firetruck's available.");

	bool getIsHome();
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling getIsHome().");

	void setIsHome(bool b);
//	REQUIRE(init(), "Object 'Firetruck' was not properly initialized when calling setIsHome().");
//	ENSURE((getIsHome() == b), "Setted atHome does not match Firetruck's atHome.");


	friend std::ostream& operator <<(std::ostream& s, Firetruck& truck);
};

#endif /* VEHICLES_H_ */
