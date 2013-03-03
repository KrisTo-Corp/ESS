/*
 * CityObjects.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include "CityObjects.h"

CityObjects::CityObjects(): type(none) {

	_initCheck = this;

	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");
}

CityObjects::CityObjects(Eobjects t): type(t) {
	REQUIRE(typeid(t) == typeid(Eobjects), "Constructor requires an Eobjects type argument.");

	_initCheck = this;

	ENSURE(properlyInitialized(), "Constructor didn't end in properly initialized state.");
}

Eobjects CityObjects::getType(){
	//REQUIRE(this->properlyInitialized(), "Object was not properly initialized when calling getType().");

	ENSURE(typeid(type) == typeid(Eobjects), "getType() should return an Eobjects type.");

	return type;
}

bool CityObjects::properlyInitialized(){
	// PRIVATE METHOD DOES NOT HAVE POST OR PRE CONDITIONS.

	return _initCheck == this;
}


