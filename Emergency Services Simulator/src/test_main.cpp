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
	friend class Vehicles;
	friend class Firetruck;

	Vehicles vehicle;
	Firetruck firetruck;
};

class StructuresTest: public ::testing::Test {
protected:
	friend class Structures;
	friend class House;
	friend class Fire_Department;

	Structures structure;
	House test_house;
	Fire_Department test_department;
};

class RoadsTest: public ::testing::Test {
protected:
	friend class Roads;

	Roads road;
	Street the_street;
	Crossroad the_crossroad;

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

// TEST DEFAULT CONSTRUCTOR STRUCTURES
TEST_F(StructuresTest, DefaultConstructor){
	EXPECT_TRUE(structure.init());
	EXPECT_EQ("", structure.getName());
	EXPECT_EQ(Coordinate(0, 0), structure.getLocation());
	EXPECT_EQ(0, structure.getWidth());
	EXPECT_EQ(0, structure.getLength());
	EXPECT_EQ(none, structure.getType());
	EXPECT_EQ(intouchable, structure.getState());
}

// TEST SPECIFIED CONSTRUCTOR STRUCTURES
TEST_F(StructuresTest, Constructor){
	structure = Structures(12, 13, "structure", 9, 11, house);
	EXPECT_TRUE(structure.init());
	EXPECT_EQ("structure", structure.getName());
	EXPECT_EQ(Coordinate(12, 13), structure.getLocation());
	EXPECT_EQ(9, structure.getWidth());
	EXPECT_EQ(11, structure.getLength());
	EXPECT_EQ(house, structure.getType());
	EXPECT_EQ(normal, structure.getState());

}

// TEST DEFAULT CONSTRUCTOR HOUSE
TEST_F(StructuresTest, HouseDefaultConstructor){
	EXPECT_TRUE(test_house.init());
	EXPECT_EQ("", test_house.getName());
	EXPECT_EQ(Coordinate(0, 0), test_house.getLocation());
	EXPECT_EQ(2, test_house.getWidth());
	EXPECT_EQ(2, test_house.getLength());
	EXPECT_EQ(0, test_house.getHP());
	EXPECT_EQ(house, test_house.getType());
	EXPECT_EQ(normal, test_house.getState());
}

// TEST SPECIFIED CONSTRUCTOR HOUSE
TEST_F(StructuresTest, HouseConstructor){
	test_house = House(10, 11, 20, "house");
	EXPECT_TRUE(test_house.init());
	EXPECT_EQ("house", test_house.getName());
	EXPECT_EQ(Coordinate(10, 11), test_house.getLocation());
	EXPECT_EQ(2, test_house.getWidth());
	EXPECT_EQ(2, test_house.getLength());
	EXPECT_EQ(20, test_house.getHP());
	EXPECT_EQ(house, test_house.getType());
	EXPECT_EQ(normal, test_house.getState());
}

// TEST DECREASE HP FUNCTION
TEST_F(StructuresTest, DecreaseHP){
	test_house = House(0, 0, 10, "house");
	EXPECT_EQ(10, test_house.getHP());
	test_house.decreaseHP();
	EXPECT_EQ(9.75, test_house.getHP());
	test_house.decreaseHP();
	EXPECT_EQ(9.5, test_house.getHP());
	test_house.decreaseHP();
	EXPECT_EQ(9.25, test_house.getHP());
	test_house.decreaseHP();
	EXPECT_EQ(9, test_house.getHP());
}

// TEST DEFAULT CONSTRUCTOR FIRE_DEPARTMENT
TEST_F(StructuresTest, FireDepartmentDefaultConstructor){
	EXPECT_TRUE(test_department.init());
	EXPECT_EQ("", test_department.getName());
	EXPECT_EQ(Coordinate(0, 0), test_department.getLocation());
	EXPECT_EQ(Coordinate(0, 0), test_department.getEntrance());
	EXPECT_EQ(4, test_department.getWidth());
	EXPECT_EQ(4, test_department.getLength());
	EXPECT_EQ(0, test_department.getAmountTrucks());
	EXPECT_EQ(department, test_department.getType());
	EXPECT_EQ(intouchable, test_department.getState());
}

// TEST SPECIFIED CONSTRUCTOR FIRE_DEPARTMENT
TEST_F(StructuresTest, FireDepartmentConstructor){
	test_department = Fire_Department(1, 2, 3, 4, "department");
	EXPECT_TRUE(test_department.init());
	EXPECT_EQ("department", test_department.getName());
	EXPECT_EQ(Coordinate(1, 2), test_department.getLocation());
	EXPECT_EQ(Coordinate(3, 4), test_department.getEntrance());
	EXPECT_EQ(4, test_department.getWidth());
	EXPECT_EQ(4, test_department.getLength());
	EXPECT_EQ(0, test_department.getAmountTrucks());
	EXPECT_EQ(department, test_department.getType());
	EXPECT_EQ(intouchable, test_department.getState());
}

// TEST THE TRUCK FUNCTIONS FROM FIRE DEPARTMENT
TEST_F(StructuresTest, FireDepartmentTruckFunctions){
	Firetruck truck1;
	Firetruck truck2;
	Firetruck truck3;
	EXPECT_EQ(0, test_department.getAmountTrucks());
	test_department.addTruck(&truck1);
	EXPECT_EQ(1, test_department.getAmountTrucks());
	EXPECT_EQ(&truck1, test_department.useTruck());
	EXPECT_EQ(0, test_department.getAmountTrucks());
	test_department.addTruck(&truck3);
	test_department.addTruck(&truck2);
	EXPECT_EQ(2, test_department.getAmountTrucks());
	EXPECT_EQ(&truck3, test_department.useTruck());
	EXPECT_EQ(1, test_department.getAmountTrucks());
	EXPECT_EQ(&truck2, test_department.useTruck());
	EXPECT_EQ(0, test_department.getAmountTrucks());
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
