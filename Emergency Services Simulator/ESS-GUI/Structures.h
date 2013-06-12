//=======================================================================================
// Name        : Structures.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Structures in C++, Ansi-style
//=======================================================================================

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <string>
#include <ostream>
#include <vector>

#include "Vehicles.h"
#include "Coordinate.h"
#include "CityObjects.h"

class Firetruck;
class PoliceCar;
class Ambulance;

class Structures: public CityObjects {
protected:
	double maxhp;
	double hp;
	double spreadcounter;
	std::string name;
	Coordinate location;
	int width;
	int length;

public:
	Structures();
//	ENSURE(init(), "Object 'Structures' was not properly initialized.");

	Structures(const int x, const int y, const std::string n, const int w, const int l, Eobjects t, int hitpoints = 0);
//	ENSURE(init(), "Object 'Structures' was not properly initialized.");

	virtual ~Structures();

	std::string getName();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	Coordinate getLocation();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	void decreaseHP();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling decreaseHP()");
//	ENSURE(hitpoints == oldHP - (1.0/(width*length)), "HP of structure was not decreased successfully.");

	double getHP();
//	REQUIRE(init(), "Object 'House' was not properly initialized when calling getHP()");

	double getMaxHp();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getMaxHp()");

	double getSpreadcounter();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getSpreadcounter()");

	void resetSpreadcounter();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling resetSpreadcounter()");
//	ENSURE(spreadcounter == 0, "Method resetSpreadcounter() of object 'Structures' did not correctly reset the spreadcounter.");

	void increaseSpreadcounter();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling increaseSpreadcounter()");
//	ENSURE(spreadcounter == oldSpreadCounter + 1, "Method increaseSpreadcounter() of object 'Structures' did not correctly increase the spreadcounter.");

	void increaseHp();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling increaseHP()");
//	ENSURE(hp = hp + ((((1.0)/width*length))/2), "Method increaseHP() of Structures did not correctly increase the object's hp");

	int getWidth();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	int getLength();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	Structures(const Structures& c);
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling copy constructor");

	Structures& operator =(const Structures&);
};


class House: public Structures {

public:
	House();
//	ENSURE(init(), "Object 'House' was not properly initialized.");

	House(const int x, const int y, int hp, const std::string n);
//	ENSURE(init(), "Object 'House' was not properly initialized.");

	virtual ~House();

	House(const House& c);
//	REQUIRE(init(), "Object 'House' was not properly initialized when calling copy constructor");

	friend std::ostream& operator <<(std::ostream& s, House& house);

	House& operator =(const House&);
};


class Fire_Department: public Structures {
private:
	Coordinate entrance;
	std::vector<Firetruck*> trucks;

public:
	Fire_Department();
//	ENSURE(init(), "Object 'Fire_Department' was not properly initialized.");

	Fire_Department(const int x, const int y, const int x_entrance, const int y_entrance, const std::string n, int hp = 0);
//	ENSURE(init(), "Object 'Fire_Department' was not properly initialized.");

	virtual ~Fire_Department();

	Coordinate& getEntrance();
//	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized.");

	int getAmountTrucks();
//	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling getAmountTrucks()");

	void addTruck(Firetruck*);
//	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling addTruck()");
//	ENSURE((trucks[trucks.size()-1] == t), "Firetruck was not succesfully added to trucks Vector");

	Firetruck* useTruck();
//	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling useTruck()");
//	ENSURE((size - 1 == trucks.size()), "Firetruck was not succesfully added to trucks Vector");

	Fire_Department(const Fire_Department& c);
//	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling copy constructor");

	friend std::ostream& operator <<(std::ostream& s, Fire_Department& department);

	Fire_Department operator =(const Fire_Department&);
};

class Store : public Structures {
private:
	double rp;
	bool robable;
public:
	Store();
//	ENSURE(init(), "Object 'Store' was not properly initialized.");

	Store(const int x, const int y, int hitpoints, int robberyPoints, const std::string n, const int width, const int length, bool rob);
//	ENSURE(init(), "Object 'Store' was not properly initialized.");

	double getRP();
//	REQUIRE(init(), "Object 'Store' was not properly initialized when calling getRP()");

	bool getRobable();
//	REQUIRE(init(), "Object 'Store' was not properly initialized when calling getRobable()");

	void decreaseRP();
//	REQUIRE(init(), "Object 'Store' was not properly initialized when calling decreaseRP()");
//	ENSURE(rp == oldRP - (1.0/(width*length)), "HP of house was not decreased successfully.");

	Store(const Store& c);
//	REQUIRE(init(), "Object 'Store' was not properly initialized when calling copy constructor");

	Store& operator =(const Store&);
};

class PoliceStation : public Structures {
private:
	Coordinate entrance;
	std::vector<PoliceCar*> cars;

public:
	PoliceStation();
//	ENSURE(init(), "Object 'policeStation' was not properly initialized.");

	PoliceStation(const int x, const int y, const int x_entrance, const int y_entrance, int hitpoints, const std::string n, const int width, const int length);
//	ENSURE(init(), "Object 'policeStation' was not properly initialized.");

	Coordinate& getEntrance();
//	REQUIRE(init(), "Object 'Hospital' was not properly initialized.");

	void addCar(PoliceCar*);
//	REQUIRE(init(), "Object 'PoliceStation' was not properly initialized when calling addTruck()");
//	ENSURE((trucks[trucks.size()-1] == t), "PoliceStation was not succesfully added to trucks Vector");

	int getAmountCars();
//	REQUIRE(init(), "Object 'PoliceStation' was not properly initialized when calling getAmountCars()");

	PoliceStation(const PoliceStation& c);
//	REQUIRE(init(), "Object 'PoliceStation' was not properly initialized when calling copy constructor");

	PoliceStation& operator =(const PoliceStation&);
};

class Hospital : public Structures {
private:
	Coordinate entrance;
	std::vector<Ambulance*> ambulances;

public:
	Hospital();
//	ENSURE(init(), "Object 'Hospital' was not properly initialized.");

	Hospital(const int x, const int y, const int x_entrance, const int y_entrance, int hitpoints, const std::string n, const int width, const int length);
//	ENSURE(init(), "Object 'Hospital' was not properly initialized.");

	Coordinate& getEntrance();
//	REQUIRE(init(), "Object 'Hospital' was not properly initialized.");

	void addAmbulance(Ambulance*);
//	REQUIRE(init(), "Object 'Hospital' was not properly initialized when calling addTruck()");
//	ENSURE((trucks[trucks.size()-1] == t), "Hospital was not succesfully added to trucks Vector");

	int getAmountAmbulances();
//	REQUIRE(init(), "Object 'Hospital' was not properly initialized when calling getAmountAmbulances()");

	Hospital(const Hospital& c);
//	REQUIRE(init(), "Object 'Hospital' was not properly initialized when calling copy constructor.");

	Hospital& operator =(const Hospital&);
};



#endif /* STRUCTURES_H_ */
