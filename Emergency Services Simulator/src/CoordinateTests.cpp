/*
 * CoordinateTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "Coordinate.h"

class CoordinateTest: public ::testing::Test {
protected:
	friend class Coordinate;

	Coordinate coordinate;
};

// TEST THE DEFAULT COORDINATE CONSTRUCTOR.
TEST_F(CoordinateTest, DefaultConstructor){
	EXPECT_TRUE(coordinate.properlyInitialized());
	EXPECT_EQ(0, coordinate.getX());
	EXPECT_EQ(0, coordinate.getY());
}

// TEST THE SPECIFIED COORDINATE CONSTRUCTOR.
TEST_F(CoordinateTest, Constructor){
	coordinate = Coordinate(1, 1);
	EXPECT_TRUE(coordinate.properlyInitialized());
	EXPECT_EQ(1, coordinate.getX());
	EXPECT_EQ(1, coordinate.getY());
}

// TEST THE SET AND GET FUNCTIONS FROM COORDINATE
TEST_F(CoordinateTest, SetFunctions){
	coordinate.setX(999);
	EXPECT_EQ(999, coordinate.getX());
	coordinate.setY(-549);
	EXPECT_EQ(-549, coordinate.getY());
}
