/*
 * CityObjects.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#ifndef CITYOBJECTS_H_
#define CITYOBJECTS_H_

#include <ostream>
#include <typeinfo>

#include "DesignByContract.h"

enum Eobjects {none, house, department, street, crossroad};

class CityObjects {
private:
	Eobjects type;

	CityObjects* _initCheck;

public:
	CityObjects();
//	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");

	CityObjects(Eobjects t);
//	REQUIRE(typeid(t) == typeid(Eobjects), "Constructor requires an Eobjects type argument.")
//	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");

	Eobjects getType();
//	REQUIRE(this->properlyInitialized(), "Object was not properly initialized when calling getType().");
//	ENSURE(typeid(type) == typeid(Eobjects), "getType() should return an Eobjects type.");

private:
	bool properlyInitialized();
};

#endif /* CITYOBJECTS_H_ */
