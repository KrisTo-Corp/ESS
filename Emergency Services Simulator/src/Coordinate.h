/*
 * Coordinate.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <string>

class Coordinate {
private:
	int x;
	int y;
public:
	Coordinate();
	Coordinate(int, int);
	virtual ~Coordinate();
	std::string print();
};

#endif /* COORDINATE_H_ */
