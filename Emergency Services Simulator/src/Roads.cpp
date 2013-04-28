//=======================================================================================
// Name        : Roads.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Roads in C++, Ansi-style
//=======================================================================================

#include <iostream>

#include "Roads.h"


//================
//	CLASS ROADS
//================


Roads::Roads(): CityObjects(none), name("") {
	ENSURE(init(), "Object 'Roads' was not properly initialized.");

}

Roads::Roads(const std::string n, Eobjects t): CityObjects(t), name(n) {
	ENSURE(init(), "Object 'Roads' was not properly initialized.");
}

Roads::~Roads()
{
}

std::string Roads::getName() {
	REQUIRE(init(), "Object 'Roads' was not properly initialized when calling getName()");

	return name;
}

Roads::Roads (const Roads& r) {
	name = r.name;
	this->type = r.type;
	this->state = r.state;

	_initCheck = this;
}

Roads& Roads::operator = (const Roads& r) {
	name = r.name;
	this->type = r.type;
	this->state = r.state;

	_initCheck = this;
	return *this;
}


//=================
//	CLASS STREET
//=================

Street::Street(): Roads("", street), start(0, 0), end(0, 0)
{
	ENSURE(init(), "Object 'Street' was not properly initialized.");
}

Street::Street(const int x_start, const int y_start, const int x_end, const int y_end, const std::string n): Roads(n, street), start(x_start, y_start), end(x_end, y_end)
{
	ENSURE(init(), "Object 'Street' was not properly initialized.");
}

Street::~Street()
{
}

Coordinate Street::getStart(){
	REQUIRE(init(), "Object 'Street' was not properly initialized when calling getStart()");

	return start;
}

Coordinate Street::getEnd(){
	REQUIRE(init(), "Object 'Street' was not properly initialized when calling getEnd()");

	return end;
}

std::ostream& operator <<(std::ostream& s, Street& street){
	s << "Road: Street \n";
	s << "Name: " << street.name << "\n";
	s << "Start: " << street.start << "\n";
	s << "End: " << street.end << "\n";

	return s;
}

Street::Street (const Street& s) {
	name = s.name;
	type = s.type;
	state = s.state;

	start = s.start;
	end = s.end;

	_initCheck = this;
}

Street& Street::operator = (const Street& s) {
	name = s.name;
	type = s.type;
	state = s.state;

	start = s.start;
	end = s.end;

	_initCheck = this;
	return *this;
}


//===================
//	CLASS CROSSROAD
//===================

Crossroad::Crossroad(): Roads("", crossroad), location(0, 0)
{
	s1 = "";
	s2 = "";

	ENSURE(init(), "Object 'Crossroad' was not properly initialized.");
}

Crossroad::Crossroad(const int x, const int y, const std::string n, const std::string street1, const std::string street2): Roads(n, crossroad), location(x, y)
{
	s1 = street1;
	s2 = street2;

	ENSURE(init(), "Object 'Crossroad' was not properly initialized.");
}

Crossroad::~Crossroad()
{
}

Coordinate Crossroad::getLocation(){
	REQUIRE(init(), "Object 'Crossroad' was not properly initialized when calling getLocation()");

	return location;
}

std::string Crossroad::getStreet1() {
	//REQUIRE(init(), "Object 'Crossroad' was not properly initialized when calling getStreet1()");

	return s1;
}

std::string Crossroad::getStreet2() {
	REQUIRE(init(), "Object 'Crossroad' was not properly initialized when calling getStreet2()");

	return s2;
}

std::ostream& operator <<(std::ostream& s, Crossroad& crossroad){
	s << "Road: Crossroad \n";
	s << "Name: " << crossroad.name << "\n";
	s << "Location: " << crossroad.location << "\n";

	return s;
}

Crossroad::Crossroad (const Crossroad& c) {
	name = c.name;
	type = c.type;
	state = c.state;

	location = c.location;
	s1 = c.s1;
	s2 = c.s2;

	_initCheck = this;
}

Crossroad& Crossroad::operator = (const Crossroad& c) {
	name = c.name;
	type = c.type;
	state = c.state;

	location = c.location;
	s1 = c.s1;
	s2 = c.s2;

	_initCheck = this;
	return *this;
}

// TEST THE DEFAULT ROAD CONSTRUCTOR
TEST_F(RoadsTest, RoadDefaultConstructor) {
	EXPECT_TRUE(road.init());
	EXPECT_EQ(road.getName(), "");
	EXPECT_EQ(none, road.getType());
	EXPECT_EQ(intouchable, road.getState());
}

// TEST THE SPECIFIED ROAD CONSTRUCTOR
TEST_F(RoadsTest, RoadConstructor) {
	road = Roads("test", none);
	EXPECT_TRUE(road.init());
	EXPECT_EQ(road.getName(), "test");
	EXPECT_EQ(none, road.getType());
	EXPECT_EQ(intouchable, road.getState());
}

// TEST THE DEFAULT STREET CONSTRUCTOR
TEST_F(RoadsTest, StreetDefaultConstructor) {
	EXPECT_TRUE(the_street.init());
	EXPECT_EQ(the_street.getName(), "");
	EXPECT_EQ(street, the_street.getType());
	EXPECT_EQ(intouchable, the_street.getState());
	EXPECT_EQ(Coordinate(0,0), the_street.getStart());
	EXPECT_EQ(Coordinate(0,0), the_street.getEnd());
}

// TEST THE SPECIFIED STREET CONSTRUCTOR
TEST_F(RoadsTest, StreetConstructor) {
	the_street = Street(10, 25, 10, 50, "teststreet");
	EXPECT_TRUE(the_street.init());
	EXPECT_EQ(the_street.getName(), "teststreet");
	EXPECT_EQ(street, the_street.getType());
	EXPECT_EQ(intouchable, the_street.getState());
	EXPECT_EQ(Coordinate(10,25), the_street.getStart());
	EXPECT_EQ(Coordinate(10,50), the_street.getEnd());
}

// TEST THE DEFAULT CROSSROAD CONTRUCTOR
TEST_F(RoadsTest, CrossroadDefaultConstructor) {
	EXPECT_TRUE(the_crossroad.init());
	EXPECT_EQ(the_crossroad.getName(), "");
	EXPECT_EQ(the_crossroad.getStreet1(), "");
	EXPECT_EQ(the_crossroad.getStreet2(), "");
	EXPECT_EQ(crossroad, the_crossroad.getType());
	EXPECT_EQ(intouchable, the_crossroad.getState());
	EXPECT_EQ(Coordinate(0,0), the_crossroad.getLocation());
}

// TEST THE SPECIFIED CROSSROAD CONTRUCTOR
TEST_F(RoadsTest, CrossroadConstructor) {
	the_crossroad = Crossroad(10, 4, "TestStreet", "Test", "Street");
	EXPECT_TRUE(the_crossroad.init());
	EXPECT_EQ(the_crossroad.getName(), "TestStreet");
	EXPECT_EQ(the_crossroad.getStreet1(), "Test");
	EXPECT_EQ(the_crossroad.getStreet2(), "Street");
	EXPECT_EQ(crossroad, the_crossroad.getType());
	EXPECT_EQ(intouchable, the_crossroad.getState());
	EXPECT_EQ(Coordinate(10, 4), the_crossroad.getLocation());
}

