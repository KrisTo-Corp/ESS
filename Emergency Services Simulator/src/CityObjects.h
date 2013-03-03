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

enum Eobjects {none, house, department, street, crossroad};

class CityObjects {
private:
	Eobjects type;

public:
	CityObjects();
	CityObjects(Eobjects type);
	virtual ~CityObjects();

	Eobjects getType();

};

#endif /* CITYOBJECTS_H_ */
