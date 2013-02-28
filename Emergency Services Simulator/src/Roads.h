/*
 * Roads.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef ROADS_H_
#define ROADS_H_

#include <string>
#include <ostream>

#include "Coordinate.h"

class Roads {
protected:
	const std::string name;
public:
	Roads();
	Roads(const std::string);
	virtual ~Roads();
};

class Street: public Roads {
private:
	Coordinate start;
	Coordinate end;
public:
	Street();
	Street(int, int, int, int, const std::string);
	friend std::ostream& operator <<(std::ostream&, Street&);
};

class Crossroad: public Roads {
private:
	Coordinate location;
public:
	Crossroad();
	Crossroad(int, int, const std::string);
	friend std::ostream& operator <<(std::ostream&, Crossroad&);
};

#endif /* ROADS_H_ */
