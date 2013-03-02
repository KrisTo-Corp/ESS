/*
 * Coordinate.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <string>
#include <ostream>

class Coordinate {
private:
	int x;
	int y;
public:
	Coordinate();
	Coordinate(const int, const int);
	int getX()const;
	int getY()const;
	friend std::ostream& operator <<(std::ostream&, Coordinate&);
	virtual ~Coordinate();
};

#endif /* COORDINATE_H_ */
