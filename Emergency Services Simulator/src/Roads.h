//=======================================================================================
// Name        : Roads.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Roads in C++, Ansi-style
//=======================================================================================

#ifndef ROADS_H_
#define ROADS_H_

#include <string>
#include <ostream>

#include "Coordinate.h"
#include "CityObjects.h"

class Roads: public CityObjects {
protected:
	std::string name;

public:
	Roads();
//	ENSURE(init(), "Object 'Roads' was not properly initialized.");

	Roads(const std::string, Eobjects);
//	ENSURE(init(), "Object 'Roads' was not properly initialized.");

	virtual ~Roads();

	std::string getName();
//	REQUIRE(init(), "Object 'Roads' was not properly initialized when calling getName()");

	Roads& operator = (const Roads&);
};



class Street: public Roads {
private:
	Coordinate start;
	Coordinate end;

public:
	Street();
	Street(const int x_start, const int y_start, const int x_end, const int y_end, const std::string n);
	virtual ~Street();

	Coordinate getStart();
	Coordinate getEnd();
	friend std::ostream& operator <<(std::ostream& s, Street& street);
	Street& operator = (const Street&);
};



class Crossroad: public Roads {
private:
	Coordinate location;
	std::string s1;
	std::string s2;

public:
	Crossroad();
	Crossroad(const int x, const int y, const std::string n, std::string, std::string);
	virtual ~Crossroad();

	Coordinate getLocation();
	std::string getStreet1();
	std::string getStreet2();
	friend std::ostream& operator <<(std::ostream& s, Crossroad& crossroad);
	Crossroad& operator = (const Crossroad&);
};

#endif /* ROADS_H_ */
