//=======================================================================================
// Name        : CityObjects.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : CityObjects in C++, Ansi-style
//=======================================================================================

#ifndef CITYOBJECTS_H_
#define CITYOBJECTS_H_

#include <ostream>

#include "DesignByContract.h"

enum Eobjects {none, house, department, street, crossroad};

class CityObjects {
protected:
	Eobjects type;

	CityObjects* _initCheck;

public:
	CityObjects();
//	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");

	CityObjects(Eobjects type);
//	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");

	virtual ~CityObjects();

	Eobjects getType();
//	REQUIRE(this->init(), "Object 'CityObjects' was not properly initialized when calling getType()");


	virtual bool init();

};

#endif /* CITYOBJECTS_H_ */
