/*
 * Structures.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <string>

class Structures {
protected:
	const std::string name;
	Coordinate location;
public:
	Structures();
	virtual ~Structures();
};

#endif /* STRUCTURES_H_ */
