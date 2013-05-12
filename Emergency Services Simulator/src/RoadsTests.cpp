/*
 * RoadsTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "Roads.h"

class RoadsTest: public ::testing::Test {
protected:
	friend class Roads;

	Roads road;
	Street the_street;
	Crossroad the_crossroad;
};

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

