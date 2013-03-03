/*
 * CityObjects.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include "CityObjects.h"

CityObjects::CityObjects(): type(none)
{
}

CityObjects::CityObjects(Eobjects t): type(t)
{
}

Eobjects CityObjects::getType(){
	return type;
}

CityObjects::~CityObjects()
{
}


