//=======================================================================================
// Name        : CityObjects.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : CityObjects in C++, Ansi-style
//=======================================================================================

#include "CityObjects.h"

#include <iostream>

CityObjects::CityObjects(): type(none)
{
	_initCheck = this;

	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");
}

CityObjects::CityObjects(Eobjects t): type(t)
{
	_initCheck = this;

	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");
}

CityObjects::~CityObjects()
{
}

Eobjects CityObjects::getType(){
	// TODO: Fix getType() contract
	//std::cerr << "Initcheck = " << init() << "\n";
	//REQUIRE(init(), "Object 'CityObjects' was not properly initialized when calling getType()");

	return type;
}

bool CityObjects::init() {
	return _initCheck == this;
}

