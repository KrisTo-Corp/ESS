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
	//if ((type == house) || (type == store) || (type == hospital) || (type == department) || (type == policeStation)){
	//	state = normal;
	//}
	if ((type == house) || (type == store)){
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
// TEST THE CITYOBJECTS DEFAULT CONSTRUCTOR

TEST_F(CityObjectsTest,  CityObjectsDefaultConstructor) {
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(none, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());
}

// TEST THE CITYOBJECTS SPECIFIED CONSTRUCTOR
TEST_F(CityObjectsTest,  CityObjectsConstructor) {
	cObject = CityObjects(house);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(house, cObject.getType());
	EXPECT_EQ(normal, cObject.getState());

	cObject = CityObjects(department);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(department, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());

	cObject = CityObjects(street);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(street, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());

	cObject = CityObjects(crossroad);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(crossroad, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());

	cObject = CityObjects(store);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(store, cObject.getType());
	EXPECT_EQ(normal, cObject.getState());

	cObject = CityObjects(policeStation);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(policeStation, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());

	cObject = CityObjects(hospital);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(hospital, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());
}

// TEST THE CITYOBJECTS SETSTATE()
TEST_F(CityObjectsTest, setState) {
	cObject.setState(normal);
	EXPECT_EQ(normal, cObject.getState());
	cObject.setState(burning);
	EXPECT_EQ(burning, cObject.getState());
	cObject.setState(beingrescuedF);
	EXPECT_EQ(beingrescuedF, cObject.getState());
	cObject.setState(destroyed);
	EXPECT_EQ(destroyed, cObject.getState());
	cObject.setState(intouchable);
	EXPECT_EQ(intouchable, cObject.getState());
	cObject.setState(beingrobbed);
	EXPECT_EQ(beingrobbed, cObject.getState());
	cObject.setState(beingrescuedR);
	EXPECT_EQ(beingrescuedR, cObject.getState());
}


