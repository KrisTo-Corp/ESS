/*
 * Structures.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

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
	Structures(const int, const int, const std::string, const int, const int, Eobjects);
	std::string getName() const;
	Coordinate getLocation();
	const int getWidth()const;
	const int getLength()const;
	virtual ~Structures();
};

class House: public Structures {
private:
	int hitpoints;
public:
	House();
	House(const int, const int, int, const std::string);
	friend std::ostream& operator <<(std::ostream&, House&);
};

class Fire_Department: public Structures {
private:
	Coordinate entrance;
public:
	Fire_Department();
	Fire_Department(const int, const int, const int, const int, const std::string);
	friend std::ostream& operator <<(std::ostream&, Fire_Department&);
};

#endif /* STRUCTURES_H_ */
