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

	std::string getName();
//	REQUIRE(init(), "Object 'Roads' was not properly initialized when calling getName()");

	Roads (const Roads& r);

	Roads& operator = (const Roads&);

	virtual ~Roads();
};



class Street: public Roads {
private:
	Coordinate start;
	Coordinate end;

public:
	Street();
//	ENSURE(init(), "Object 'Street' was not properly initialized.");

	Street(const int x_start, const int y_start, const int x_end, const int y_end, const std::string n);
//	ENSURE(init(), "Object 'Street' was not properly initialized.");

	Coordinate getStart();
//	REQUIRE(init(), "Object 'Street' was not properly initialized when calling getStart()");

	Coordinate getEnd();
//	REQUIRE(init(), "Object 'Street' was not properly initialized when calling getEnd()");

	friend std::ostream& operator <<(std::ostream& s, Street& street);

	Street (const Street& s);

	Street& operator = (const Street&);

	virtual ~Street();
};



class Crossroad: public Roads {
private:
	Coordinate location;
	std::string s1;
	std::string s2;

public:
	Crossroad();
//	ENSURE(init(), "Object 'Crossroad' was not properly initialized.");

	Crossroad(const int x, const int y, const std::string n, std::string, std::string);
//	ENSURE(init(), "Object 'Crossroad' was not properly initialized.");

	Coordinate getLocation();
//	REQUIRE(init(), "Object 'Crossroad' was not properly initialized when calling getLocation()");

	std::string getStreet1();
//	REQUIRE(init(), "Object 'Crossroad' was not properly initialized when calling getStreet1()");

	std::string getStreet2();
//	REQUIRE(init(), "Object 'Crossroad' was not properly initialized when calling getStreet1()");

	friend std::ostream& operator <<(std::ostream& s, Crossroad& crossroad);

	Crossroad (const Crossroad& c);

	Crossroad& operator = (const Crossroad&);

	virtual ~Crossroad();
};

#endif /* ROADS_H_ */
