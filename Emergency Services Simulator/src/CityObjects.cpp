//=======================================================================================
// Name        : CityObjects.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : CityObjects in C++, Ansi-style
//=======================================================================================

#include "CityObjects.h"

#include <iostream>

CityObjects::CityObjects(): type(none), state(intouchable)
{
	_initCheck = this;

	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");
}

CityObjects::CityObjects(Eobjects t): type(t)
{
	if (type == house){
		state = normal;
	}
	else if (type == store){
		state = normal;
	}
	else {
		state = intouchable;
	}

	_initCheck = this;

	ENSURE(init(), "Object 'CityObjects' was not properly initialized.");
}

CityObjects::~CityObjects()
{
}

Eobjects CityObjects::getType(){
	REQUIRE(init(), "Object 'CityObjects' was not properly initialized when calling getType()");

	return type;
}

Estate CityObjects::getState(){
	REQUIRE(init(), "Object 'CityObjects' was not properly initialized when calling getState()");

	return state;
}

void CityObjects::setState(Estate s){
	REQUIRE(init(), "Object 'CityObjects' was not properly initialized when calling setState()");

	state = s;

	ENSURE((getState() == s), "Setted state does not match object's state.");
}

bool CityObjects::init() {
	return _initCheck == this;
}

CityObjects::CityObjects(const CityObjects& c) {
	type = c.type;
	state = c.state;
	_initCheck = this;
}

CityObjects& CityObjects::operator = (const CityObjects& c) {
	type = c.type;
	state = c.state;

	_initCheck = this;
	return *this;
}



