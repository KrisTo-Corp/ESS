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

	double getSpreadcounter();

	void resetSpreadcounter();

	void increaseSpreadcounter();

	void increaseHp();

	int getWidth();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	int getLength();
//	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	Structures(const Structures& c);

	Structures& operator =(const Structures&);
};


class House: public Structures {

public:
	House();
//	ENSURE(init(), "Object 'House' was not properly initialized.");

	House(const int x, const int y, int hp, const std::string n);
//	ENSURE(init(), "Object 'House' was not properly initialized.");

	virtual ~House();

	friend std::ostream& operator <<(std::ostream& s, House& house);

	House(const House& c);

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


	friend std::ostream& operator <<(std::ostream& s, Fire_Department& department);

	Fire_Department operator =(const Fire_Department&);

	Fire_Department(const Fire_Department& c);

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

	bool getRobable();

	void decreaseRP();
//	REQUIRE(init(), "Object 'Store' was not properly initialized when calling decreaseRP()");

	Store(const Store& c);

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

	PoliceStation(const PoliceStation& c);

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


	Hospital(const Hospital& c);

	Hospital& operator =(const Hospital&);
};

#endif /* STRUCTURES_H_ */
