//=======================================================================================
// Name        : CityObjects.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : CityObjects in C++, Ansi-style
//=======================================================================================

#include "CityObjects.h"

CityObjects::CityObjects(): type(none)
{
}

CityObjects::CityObjects(Eobjects t): type(t)
{
}

CityObjects::~CityObjects()
{
}

Eobjects CityObjects::getType(){
	return type;
}

