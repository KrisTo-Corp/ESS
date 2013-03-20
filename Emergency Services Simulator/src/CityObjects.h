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
enum Estate {normal, burning, beingrescued, destroyed, intouchable};

class CityObjects {
protected:
	Eobjects type;
	Estate state;

	CityObjects* _initCheck;

public:
	CityObjects();
//	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");

	CityObjects(Eobjects type);
//	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");

	Eobjects getType();
//	REQUIRE(this->init(), "Object 'CityObjects' was not properly initialized when calling getType()");

	Estate getState();
//	REQUIRE(init(), "Object 'CityObjects' was not properly initialized when calling getState()");

	void setState(Estate);
// 	REQUIRE(init(), "Object 'CityObjects' was not properly initialized when calling setState()");
// 	ENSURE((getState() == s), "Setted state does not match object's state.");

	virtual ~CityObjects();

	virtual bool init();

	CityObjects(const CityObjects& c);

	CityObjects& operator = (const CityObjects& c);

};

#endif /* CITYOBJECTS_H_ */
