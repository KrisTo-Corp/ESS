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
#include "Casualty.h"

class Casualty;
class Structures;
class Fire_Department;
class Hospital;
class PoliceStation;

class Vehicles {
protected:
	std::string name;
	Coordinate coord;

	Coordinate tempDestination;
	Coordinate destination;
	Structures* target;
	bool goToTemp;
	bool available;
	bool atHome;

	int driveTime;

	std::string basename;

	Vehicles* _initCheck;

public:
	Vehicles();
//	ENSURE(properlyInitialized(), "Object 'Vehicles' was not properly initialized.");

	Vehicles(int x, int y, const std::string n, std::string bn);
//	ENSURE(properlyInitialized(), "Object 'Vehicles' was not properly initialized.");

	virtual ~Vehicles();

	std::string getName();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setCoord().");

	void setCoord(Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setCoord().");

	Coordinate getCoord();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getCoord().");

	std::string getBasename();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getBasename().");

	void move(std::string);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling move().");
//	ENSURE(direction == "up" || direction == "down" || direction == "left" || direction == "right", "An invalid direction was passed as an argument to move() in object 'Firetruck'");
//	ENSURE((oldLocation != coord), "Vehicles did not move properly.");

	void setTempDest(Coordinate);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setTempDest().");
//	ENSURE(getTempDest() == c, "Setted tempDestination in Vehicles did not match Firetruck's tempDestination.");

		Coordinate getTempDest();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getTempDest().");

		Structures* getTarget();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getTarget().");

		void setTarget(Structures* t);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setTarget().");
//	ENSURE((getTarget() == t), "Setted target does not match Firetruck's target.");

		void setDestination(Coordinate dest);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setDestination().");
//	ENSURE((getDestination() == dest), "Setted destination does not match Firetruck's destination.");

		Coordinate getDestination();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getDestination().");

		void setGoToTemp(bool v);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setGoToTemp().");
//	ENSURE((getGoToTemp() == v), "Setted GoToTemp does not match Firetruck's GoToTemp.");

		bool getGoToTemp();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getGoToTemp().");

		bool getAvailable();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getAvailable().");

		void setAvailable(bool state);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setAvailable().");
//	ENSURE((getAvailable() == state), "Setted available does not match Firetruck's available.");

		bool getIsHome();
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getIsHome().");

		void setIsHome(bool b);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling setIsHome().");
//	ENSURE((getIsHome() == b), "Setted atHome does not match Firetruck's atHome.");

	Vehicles(const Vehicles& c);
//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling copy constructor.");

	void increaseDriveTime();
	//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling increaseDriveTime().");
	//	ENSURE(driveTime == oldDriveTime +1, "The driveTime was not incremented successfully.");

	int getDriveTime();
	//	REQUIRE(properlyInitialized(), "Object 'Vehicles' was not properly initialized when calling getDriveTime().");


	Vehicles& operator =(const Vehicles&);

	virtual bool properlyInitialized();

};

class Firetruck: public Vehicles {
private:
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

	Fire_Department* getBaseptr();
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling getBaseptr().");

	Firetruck(const Firetruck& c);
//	REQUIRE(properlyInitialized(), "Object 'Firetruck' was not properly initialized when calling copy constructor().");

	Firetruck& operator = (const Firetruck&);

	friend std::ostream& operator <<(std::ostream& s, Firetruck& truck);
};

class PoliceCar: public Vehicles {
private:
	PoliceStation* base;

public:
	PoliceCar();
//	ENSURE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized.");

	PoliceCar(const int x, const int y, const std::string n, const std::string bn);
//	ENSURE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized.");

	void linkBase(PoliceStation* dep_ptr);
//	REQUIRE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized when calling linkBase().");
//	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match PoliceCar's base*.");

	PoliceStation* getBaseptr();
//	REQUIRE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized when calling getBaseptr().");

	PoliceCar(const PoliceCar& c);
//	REQUIRE(properlyInitialized(), "Object 'PoliceCar' was not properly initialized when calling copy constructor.");

	PoliceCar& operator = (const PoliceCar&);

	friend std::ostream& operator <<(std::ostream& s, PoliceCar& pCar);
};

class Ambulance: public Vehicles {
private:
	Hospital* base;

	Casualty* passenger;

	bool containing_passenger;

public:
	Ambulance();
//	ENSURE(properlyInitialized(), "Object 'Ambulance' was not properly initialized.");

	Ambulance(const int x, const int y, const std::string n, const std::string bn);
//	ENSURE(properlyInitialized(), "Object 'Ambulance' was not properly initialized.");

	void linkBase(Hospital* dep_ptr);
//	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling linkBase().");
//	ENSURE((getBaseptr() == dep_ptr), "Setted base* does not match Ambulance base*.");

	Hospital* getBaseptr();
//	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling getBaseptr().");

	Ambulance(const Ambulance& c);
//	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling copy constructor.");

	void setPassenger(Casualty*);
//	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling setPassenger().");
//	ENSURE(passenger == c, "Method setPassenger() of Ambulance did not correctly set passenger.");

	Casualty* getPassenger();
//	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling getPassenger().");

	bool getContaining();
//	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling getContaining().");

	void setContaining(bool);
//	REQUIRE(properlyInitialized(), "Object 'Ambulance' was not properly initialized when calling setContaining().");
//	ENSURE(containing_passenger == b, "Method setContaining() of Ambulance did not correctly set bool containing_passenger.");

	Ambulance& operator = (const Ambulance&);

	friend std::ostream& operator <<(std::ostream& s, Ambulance& pCar);
};


#endif /* VEHICLES_H_ */
