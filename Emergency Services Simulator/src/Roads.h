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
	Roads(const std::string, Eobjects);
	virtual ~Roads();

	std::string getName() const;
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
};



class Crossroad: public Roads {
private:
	Coordinate location;

public:
	Crossroad();
	Crossroad(const int x, const int y, const std::string n);
	virtual ~Crossroad();

	Coordinate getLocation();
	friend std::ostream& operator <<(std::ostream& s, Crossroad& crossroad);
};

#endif /* ROADS_H_ */
