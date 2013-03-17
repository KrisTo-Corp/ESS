//=======================================================================================
// Name        : test_main.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Main test file in C++, Ansi-style
//=======================================================================================

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

#include "City.h"
#include "CityObjects.h"
#include "Structures.h"
#include "Roads.h"
#include "Vehicles.h"
#include "Matrix.h"
#include <sys/stat.h>
#include <gtest/gtest.h>

class CoordinateTest: public ::testing::Test {
protected:
	friend class Coordinate;

	Coordinate coordinate;
};

class VehiclesTest: public ::testing::Test {
protected:
	friend class Firetruck;

	Vehicles vehicle;
	Firetruck firetruck;
};

class StructuresTest: public ::testing::Test {

};

class RoadsTest: public ::testing::Test {

};

class CityObjectsTest: public ::testing::Test {

};

class CityTest: public ::testing::Test {

};

class MatrixTest: public ::testing::Test {

};

class SimulationTest: public ::testing::Test {

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

// TEST THE DEFAULT VEHICLES CONSTRUCTOR
TEST_F(VehiclesTest, DefaultConstructor){
	EXPECT_TRUE(vehicle.properlyInitialized());
	EXPECT_EQ("", vehicle.getName());
	EXPECT_EQ(Coordinate(0, 0), vehicle.getCoord());
}

// TEST THE SPECIFIED VEHICLES CONSTRUCTOR
TEST_F(VehiclesTest, Constructor){
	vehicle = Vehicles(10, 9, "car");
	EXPECT_TRUE(vehicle.properlyInitialized());
	EXPECT_EQ("car", vehicle.getName());
	EXPECT_EQ(Coordinate(10, 9), vehicle.getCoord());
}

// TEST THE SET FUNCTION FROM VEHICLES
TEST_F(VehiclesTest, SetFunctions){
	Coordinate loc(5, 5);
	vehicle.setCoord(loc);
	EXPECT_EQ(loc, vehicle.getCoord());
}

// TEST THE FIRETRUCK DEFAULT CONSTRUCTOR
TEST_F(VehiclesTest, FiretruckDefaultConstructor){
	EXPECT_TRUE(firetruck.properlyInitialized());
	EXPECT_EQ("", firetruck.getName());
	EXPECT_EQ("", firetruck.getBasename());
	EXPECT_EQ(Coordinate(0, 0), firetruck.getCoord());
	EXPECT_EQ(Coordinate(0, 0), firetruck.getTempDest());
	EXPECT_EQ(Coordinate(0, 0), firetruck.getDestination());
	EXPECT_EQ(NULL, firetruck.getBaseptr());
	EXPECT_FALSE(firetruck.getGoToTemp());
	EXPECT_TRUE(firetruck.getAvailable());
	EXPECT_TRUE(firetruck.getIsHome());
	EXPECT_EQ(NULL, firetruck.getTarget());
}

// TEST THE FIRETRUCK SPECIFIED CONSTRUCTOR
TEST_F(VehiclesTest, FiretruckConstructor){
	firetruck = Firetruck(1, 1, "truck", "base");
	EXPECT_TRUE(firetruck.properlyInitialized());
	EXPECT_EQ("truck", firetruck.getName());
	EXPECT_EQ("base", firetruck.getBasename());
	EXPECT_EQ(Coordinate(1, 1), firetruck.getCoord());
	EXPECT_EQ(Coordinate(0, 0), firetruck.getTempDest());
	EXPECT_EQ(Coordinate(0, 0), firetruck.getDestination());
	EXPECT_EQ(NULL, firetruck.getBaseptr());
	EXPECT_FALSE(firetruck.getGoToTemp());
	EXPECT_TRUE(firetruck.getAvailable());
	EXPECT_TRUE(firetruck.getIsHome());
	EXPECT_EQ(NULL, firetruck.getTarget());
}

// TEST THE FIRETRUCK LINKBASE
TEST_F(VehiclesTest, FiretruckLinkBase){
	Fire_Department department;
	firetruck.linkBase(&department);
	EXPECT_EQ(&department, firetruck.getBaseptr());
}

// TEST THE MOVE FUNCTION FROM FIRETRUCK
TEST_F(VehiclesTest, FiretruckMove){
	EXPECT_EQ(Coordinate(0, 0), firetruck.getCoord());
	firetruck.move("up");
	EXPECT_EQ(Coordinate(0, 1), firetruck.getCoord());
	firetruck.move("down");
	EXPECT_EQ(Coordinate(0, 0), firetruck.getCoord());
	firetruck.move("right");
	EXPECT_EQ(Coordinate(1, 0), firetruck.getCoord());
	firetruck.move("left");
	EXPECT_EQ(Coordinate(0, 0), firetruck.getCoord());
}

// TEST ALL SET FUNCTIONS
TEST_F(VehiclesTest, FiretruckSetFunctions){
	Coordinate loc(15, 21);
	Coordinate tempdest(7, 9);
	Coordinate dest(1, 19);
	Structures structure;
	firetruck.setTempDest(tempdest);
	firetruck.setDestination(dest);
	firetruck.setTarget(&structure);
	firetruck.setGoToTemp(true);
	firetruck.setAvailable(true);
	firetruck.setIsHome(true);
	EXPECT_EQ(tempdest, firetruck.getTempDest());
	EXPECT_EQ(dest, firetruck.getDestination());
	EXPECT_EQ(&structure, firetruck.getTarget());
	EXPECT_TRUE(firetruck.getGoToTemp());
	EXPECT_TRUE(firetruck.getAvailable());
	EXPECT_TRUE(firetruck.getIsHome());
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*
 * TODO: -> Find min and max coordinates in order to make our matrix of variable size depending on the XML file.
 * 			We need to include a method that finds these coordinates and passes them to the matrix constructor...
 * 			Maybe we could make a new Matrix object in our City constructor (Since we have parsed the city by then) and copy construct our city's matrix with the new one we made? :D
 *
 * TODO: -> Output
 * 	        What we have so far is friggin' awesome. Great work with adding the coordinates!
 * 	        What we need more:
 *
 * 	        Burning houses:
 * 	        	-> House on location (x,y)
 * 	        Firetrucks on their way:
 * 	        	-> {FIRETRUCK NAME} on location (x,y) in Javastreet.
 * 	        Available firetrucks in firedepartment {FIREDEPNAME}:
 * 	        	-> {FIRETRUCK NAME}
 *
 * TODO: Contracts
 *
 * TODO: TESTS, TESTS, TESTS! We need to check whether or not our parser reacts in a proper way if we feed it wrong input.
 *
 *
 */
