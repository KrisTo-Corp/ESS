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

#include "Coordinate.h"
#include "CityObjects.h"

class Structures: public CityObjects {
protected:
	const std::string name;
	Coordinate location;
	const int width;
	const int length;

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

};



class House: public Structures {
private:
	int hitpoints;

public:
	House();
	House(const int x, const int y, int hp, const std::string n);
	virtual ~House();

	friend std::ostream& operator <<(std::ostream& s, House& house);
};


class Fire_Department: public Structures {
private:
	Coordinate entrance;

public:
	Fire_Department();
	Fire_Department(const int x, const int y, const int x_entrance, const int y_entrance, const std::string n);
	virtual ~Fire_Department();

	friend std::ostream& operator <<(std::ostream& s, Fire_Department& department);
};

#endif /* STRUCTURES_H_ */
