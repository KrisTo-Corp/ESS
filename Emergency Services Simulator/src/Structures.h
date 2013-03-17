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

class Structures: public CityObjects {
protected:
	std::string name;
	Coordinate location;
	int width;
	int length;

public:
	Structures();
	//	ENSURE(init(), "Object 'Structures' was not properly initialized.");

	Structures(const int x, const int y, const std::string n, const int w, const int l, Eobjects t);
	//	ENSURE(init(), "Object 'Structures' was not properly initialized.");

	virtual ~Structures();

	std::string getName();
	Coordinate getLocation();
	int getWidth();
	int getLength();

	Structures& operator =(const Structures&);

};

class House: public Structures {
private:
	double hitpoints;

public:
	House();
	House(const int x, const int y, int hp, const std::string n);
	virtual ~House();
	void decreaseHP();
	double getHP();
	friend std::ostream& operator <<(std::ostream& s, House& house);
	House& operator =(const House&);
};


class Fire_Department: public Structures {
private:
	Coordinate entrance;
	std::vector<Firetruck*> trucks;

public:
	Fire_Department();
	Fire_Department(const int x, const int y, const int x_entrance, const int y_entrance, const std::string n);
	virtual ~Fire_Department();

	Coordinate& getEntrance();
	int getAmountTrucks();
	void addTruck(Firetruck*);
	Firetruck* useTruck();

	friend std::ostream& operator <<(std::ostream& s, Fire_Department& department);
	Fire_Department operator =(const Fire_Department&);
};

#endif /* STRUCTURES_H_ */
