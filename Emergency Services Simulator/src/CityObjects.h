/*
 * CityObjects.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef CITYOBJECTS_H_
#define CITYOBJECTS_H_

#include <ostream>

enum Eobjects {none, house, department, street, crossroad};

class CityObjects {
private:
	Eobjects type;
public:
	CityObjects();
	CityObjects(Eobjects);
	Eobjects getType();

	virtual ~CityObjects();
};

#endif /* CITYOBJECTS_H_ */
