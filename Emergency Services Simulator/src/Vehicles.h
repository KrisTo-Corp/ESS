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
	std::string name;
	Coordinate coord;

	Vehicles* _initCheck;

public:
	Vehicles();
//	ENSURE(properlyInitialized(), "Object 'Vehicles' was not properly initialized.");

	Vehicles(int x, int y, const std::string n);
//	ENSURE(properlyInitialized(), "Object 'Vehicles' was not properly initialized.");

	virtual ~Vehicles();

	std::string getName();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setCoord().");

	void setCoord(Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setCoord().");

	Coordinate getCoord();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getCoord().");

	Vehicles(const Vehicles& c);

	Vehicles& operator =(const Vehicles&);

	virtual bool properlyInitialized();
};

class Firetruck: public Vehicles {
private:
	Coordinate tempDestination;
	Coordinate destination;
	Structures* target;
	bool goToTemp;
	bool available;
	bool atHome;

	std::string basename;
	Fire_Department* base;


public:
	Firetruck();
//	ENSURE(properlyInitialized(), "Object 'Firetruck' was not properly initialized.");

	Firetruck(const int x, const int y, const std::string n, const std::string bn);
//	ENSURE(properlyInitialized(), "Object 'Firetruck' was not properly initialized.");

	virtual ~Firetruck();

	void linkBase(Fire_Department* dep_ptr);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling linkBase().");
//	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match Firetruck's base*.");

	std::string getBasename();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getBasename().");

	Fire_Department* getBaseptr();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	void move(std::string);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling move().");
//	ENSURE(direction == "up" || direction == "down" || direction == "left" || direction == "right", "An invalid direction was passed as an argument to move() in object 'Firetruck'");
//	ENSURE((oldLocation != coord), "Firetruck did not move properly.");

	void setTempDest(Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setTempDest().");
//	ENSURE(getTempDest() == c, "Setted tempDestination in Firetruck did not match Firetruck's tempDestination.");

	Coordinate getTempDest();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getTempDest().");

	Structures* getTarget();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getTarget().");

	void setTarget(Structures* t);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setTarget().");
//	ENSURE((getTarget() == t), "Setted target does not match Firetruck's target.");

	void setDestination(Coordinate dest);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setDestination().");
//	ENSURE((getDestination() == dest), "Setted destination does not match Firetruck's destination.");

	Coordinate getDestination();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getDestination().");

	void setGoToTemp(bool v);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setGoToTemp().");
//	ENSURE((getGoToTemp() == v), "Setted GoToTemp does not match Firetruck's GoToTemp.");

	bool getGoToTemp();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getGoToTemp().");

	bool getAvailable();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getAvailable().");

	void setAvailable(bool state);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setAvailable().");
//	ENSURE((getAvailable() == state), "Setted available does not match Firetruck's available.");

	bool getIsHome();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getIsHome().");

	void setIsHome(bool b);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling setIsHome().");
//	ENSURE((getIsHome() == b), "Setted atHome does not match Firetruck's atHome.");

	friend std::ostream& operator <<(std::ostream& s, Firetruck& truck);

	Firetruck(const Firetruck& c);

	Firetruck& operator = (const Firetruck&);
};

#endif /* VEHICLES_H_ */
