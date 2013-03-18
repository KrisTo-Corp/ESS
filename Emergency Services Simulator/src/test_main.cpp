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

bool FileCompare(const char *leftFileName, const char *rightFileName) {
	std::ifstream leftFile, rightFile;
	char leftRead, rightRead;
	bool result;

	// Open the two files.
	leftFile.open(leftFileName);
	if (!leftFile.is_open()) {
		return false;
	};
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	};

	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		result = (leftRead == rightRead);
	};
	if (result) {
		// last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	};

	leftFile.close();
	rightFile.close();
	return result;
}

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
protected:
	friend class CityObjects;

	CityObjects cObject;
};

class CityTest: public ::testing::Test {
protected:
	friend class City;

};

class MatrixTest: public ::testing::Test {
protected:
	friend class Matrix;

	Matrix matrix;
};

class SimulationTest: public ::testing::Test {
protected:
	friend class City;
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

// TEST THE DEFAULT MATRIX CONSTRUCTOR
TEST_F(MatrixTest, DefaultConstructor){
	EXPECT_TRUE(matrix.properlyInitialized());
	EXPECT_EQ(10, matrix.getRows());
	EXPECT_EQ(5, matrix.getColumns());
	EXPECT_EQ(50, matrix.getTotalLength());
}

// TEST THE SPECIFIED MATRIX CONSTRUCTOR
TEST_F(MatrixTest, Constructor){
	matrix = Matrix(25, 10);
	EXPECT_TRUE(matrix.properlyInitialized());
	EXPECT_EQ(25, matrix.getRows());
	EXPECT_EQ(10, matrix.getColumns());
	EXPECT_EQ(250, matrix.getTotalLength());
}

// TEST SINGLE ADD FUNCTION FROM MATRIX
TEST_F(MatrixTest, SingleAdd){
	matrix = Matrix(2, 2);
	House house;
	Fire_Department department;
	Street street;
	Crossroad crossroad;

	CityObjects* houseptr = &house;
	CityObjects* depptr = &department;
	CityObjects* streetptr = &street;
	CityObjects* crossroadptr = &crossroad;

	EXPECT_EQ(NULL, matrix.getObject(0, 0));
	EXPECT_EQ(NULL, matrix.getObject(0, 1));
	EXPECT_EQ(NULL, matrix.getObject(1, 0));
	EXPECT_EQ(NULL, matrix.getObject(1, 1));

	matrix.addObject(0, 0, depptr);
	matrix.addObject(0, 1, streetptr);
	matrix.addObject(1, 0, crossroadptr);
	matrix.addObject(1, 1, houseptr);

	EXPECT_EQ(depptr, matrix.getObject(0, 0));
	EXPECT_EQ(streetptr, matrix.getObject(0, 1));
	EXPECT_EQ(crossroadptr, matrix.getObject(1, 0));
	EXPECT_EQ(houseptr, matrix.getObject(1, 1));
}

// TEST THE ADDHOUSES FUNCTION
TEST_F(MatrixTest, AddHouses){
	matrix = Matrix(4, 4);
	House house1(0, 1, 20, "");
	House house2(0, 3, 20, "");
	House house3(2, 1, 20, "");
	House house4(2, 3, 20, "");
	std::list<House> houses;
	houses.push_back(house1);
	houses.push_back(house2);
	houses.push_back(house3);
	houses.push_back(house4);
	std::list<House>::iterator it = houses.begin();
	House* ptr1 = &(*it);
	it++;
	House* ptr2 = &(*it);
	it++;
	House* ptr3 = &(*it);
	it++;
	House* ptr4 = &(*it);

	matrix.addHouses(houses);

	EXPECT_EQ(ptr1, matrix.getObject(0, 0));
	EXPECT_EQ(ptr1, matrix.getObject(0, 1));
	EXPECT_EQ(ptr1, matrix.getObject(1, 0));
	EXPECT_EQ(ptr1, matrix.getObject(1, 1));
	EXPECT_EQ(ptr2, matrix.getObject(0, 3));
	EXPECT_EQ(ptr2, matrix.getObject(1, 3));
	EXPECT_EQ(ptr2, matrix.getObject(0, 2));
	EXPECT_EQ(ptr2, matrix.getObject(1, 2));
	EXPECT_EQ(ptr3, matrix.getObject(2, 1));
	EXPECT_EQ(ptr3, matrix.getObject(2, 0));
	EXPECT_EQ(ptr3, matrix.getObject(3, 1));
	EXPECT_EQ(ptr3, matrix.getObject(2, 0));
	EXPECT_EQ(ptr4, matrix.getObject(2, 3));
	EXPECT_EQ(ptr4, matrix.getObject(2, 2));
	EXPECT_EQ(ptr4, matrix.getObject(3, 3));
	EXPECT_EQ(ptr4, matrix.getObject(3, 2));
}

// TEST THE ADDDEPARTMENTS FUNCTION
TEST_F(MatrixTest, AddDepartments){
	matrix = Matrix(8, 8);
	Fire_Department dep1(0, 7, 0, 0, "");
	Fire_Department dep2(0, 3, 0, 0, "");
	Fire_Department dep3(4, 7, 0, 0, "");
	Fire_Department dep4(4, 3, 0, 0, "");
	std::list<Fire_Department> deps;
	deps.push_back(dep1);
	deps.push_back(dep2);
	deps.push_back(dep3);
	deps.push_back(dep4);
	std::list<Fire_Department>::iterator it = deps.begin();
	Fire_Department* ptr1 = &(*it);
	it++;
	Fire_Department* ptr2 = &(*it);
	it++;
	Fire_Department* ptr3 = &(*it);
	it++;
	Fire_Department* ptr4 = &(*it);

	matrix.addFiredeps(deps);

	EXPECT_EQ(ptr1, matrix.getObject(0, 7));
	EXPECT_EQ(ptr1, matrix.getObject(1, 7));
	EXPECT_EQ(ptr1, matrix.getObject(2, 7));
	EXPECT_EQ(ptr1, matrix.getObject(3, 7));
	EXPECT_EQ(ptr1, matrix.getObject(0, 6));
	EXPECT_EQ(ptr1, matrix.getObject(1, 6));
	EXPECT_EQ(ptr1, matrix.getObject(2, 6));
	EXPECT_EQ(ptr1, matrix.getObject(3, 6));
	EXPECT_EQ(ptr1, matrix.getObject(0, 5));
	EXPECT_EQ(ptr1, matrix.getObject(1, 5));
	EXPECT_EQ(ptr1, matrix.getObject(2, 5));
	EXPECT_EQ(ptr1, matrix.getObject(3, 5));
	EXPECT_EQ(ptr1, matrix.getObject(0, 4));
	EXPECT_EQ(ptr1, matrix.getObject(1, 4));
	EXPECT_EQ(ptr1, matrix.getObject(2, 4));
	EXPECT_EQ(ptr1, matrix.getObject(3, 4));

	EXPECT_EQ(ptr2, matrix.getObject(0, 3));
	EXPECT_EQ(ptr2, matrix.getObject(1, 3));
	EXPECT_EQ(ptr2, matrix.getObject(2, 3));
	EXPECT_EQ(ptr2, matrix.getObject(3, 3));
	EXPECT_EQ(ptr2, matrix.getObject(0, 2));
	EXPECT_EQ(ptr2, matrix.getObject(1, 2));
	EXPECT_EQ(ptr2, matrix.getObject(2, 2));
	EXPECT_EQ(ptr2, matrix.getObject(3, 2));
	EXPECT_EQ(ptr2, matrix.getObject(0, 1));
	EXPECT_EQ(ptr2, matrix.getObject(1, 1));
	EXPECT_EQ(ptr2, matrix.getObject(2, 1));
	EXPECT_EQ(ptr2, matrix.getObject(3, 1));
	EXPECT_EQ(ptr2, matrix.getObject(0, 0));
	EXPECT_EQ(ptr2, matrix.getObject(1, 0));
	EXPECT_EQ(ptr2, matrix.getObject(2, 0));
	EXPECT_EQ(ptr2, matrix.getObject(3, 0));

	EXPECT_EQ(ptr3, matrix.getObject(4, 7));
	EXPECT_EQ(ptr3, matrix.getObject(5, 7));
	EXPECT_EQ(ptr3, matrix.getObject(6, 7));
	EXPECT_EQ(ptr3, matrix.getObject(7, 7));
	EXPECT_EQ(ptr3, matrix.getObject(4, 6));
	EXPECT_EQ(ptr3, matrix.getObject(5, 6));
	EXPECT_EQ(ptr3, matrix.getObject(6, 6));
	EXPECT_EQ(ptr3, matrix.getObject(7, 6));
	EXPECT_EQ(ptr3, matrix.getObject(4, 5));
	EXPECT_EQ(ptr3, matrix.getObject(5, 5));
	EXPECT_EQ(ptr3, matrix.getObject(6, 5));
	EXPECT_EQ(ptr3, matrix.getObject(7, 5));
	EXPECT_EQ(ptr3, matrix.getObject(4, 4));
	EXPECT_EQ(ptr3, matrix.getObject(5, 4));
	EXPECT_EQ(ptr3, matrix.getObject(6, 4));
	EXPECT_EQ(ptr3, matrix.getObject(7, 4));

	EXPECT_EQ(ptr4, matrix.getObject(4, 3));
	EXPECT_EQ(ptr4, matrix.getObject(5, 3));
	EXPECT_EQ(ptr4, matrix.getObject(6, 3));
	EXPECT_EQ(ptr4, matrix.getObject(7, 3));
	EXPECT_EQ(ptr4, matrix.getObject(4, 2));
	EXPECT_EQ(ptr4, matrix.getObject(5, 2));
	EXPECT_EQ(ptr4, matrix.getObject(6, 2));
	EXPECT_EQ(ptr4, matrix.getObject(7, 2));
	EXPECT_EQ(ptr4, matrix.getObject(4, 1));
	EXPECT_EQ(ptr4, matrix.getObject(5, 1));
	EXPECT_EQ(ptr4, matrix.getObject(6, 1));
	EXPECT_EQ(ptr4, matrix.getObject(7, 1));
	EXPECT_EQ(ptr4, matrix.getObject(4, 0));
	EXPECT_EQ(ptr4, matrix.getObject(5, 0));
	EXPECT_EQ(ptr4, matrix.getObject(6, 0));
	EXPECT_EQ(ptr4, matrix.getObject(7, 0));
}

// TEST THE ADDSTREETS FUNCTION
TEST_F(MatrixTest, AddStreets){
	matrix = Matrix(3, 4);
	Street street1(0, 0, 2, 0, "");
	Street street2(0, 1, 2, 1, "");
	Street street3(0, 2, 2, 2, "");
	Street street4(3, 0, 3, 2, "");
	std::list<Street> streets;
	streets.push_back(street1);
	streets.push_back(street2);
	streets.push_back(street3);
	streets.push_back(street4);
	std::list<Street>::iterator it = streets.begin();
	Street* ptr1 = &(*it);
	it++;
	Street* ptr2 = &(*it);
	it++;
	Street* ptr3 = &(*it);
	it++;
	Street* ptr4 = &(*it);

	matrix.addStreets(streets);

	EXPECT_EQ(ptr1, matrix.getObject(0, 0));
	EXPECT_EQ(ptr1, matrix.getObject(1, 0));
	EXPECT_EQ(ptr1, matrix.getObject(2, 0));
	EXPECT_EQ(ptr2, matrix.getObject(0, 1));
	EXPECT_EQ(ptr2, matrix.getObject(1, 1));
	EXPECT_EQ(ptr2, matrix.getObject(2, 1));
	EXPECT_EQ(ptr3, matrix.getObject(0, 2));
	EXPECT_EQ(ptr3, matrix.getObject(1, 2));
	EXPECT_EQ(ptr3, matrix.getObject(2, 2));
	EXPECT_EQ(ptr4, matrix.getObject(3, 0));
	EXPECT_EQ(ptr4, matrix.getObject(3, 1));
	EXPECT_EQ(ptr4, matrix.getObject(3, 2));
}

// TEST THE ADDCROSSROADS FUNCTION
TEST_F(MatrixTest, AddCrossroads){
	matrix = Matrix(2, 2);
	Crossroad crossroad1(0, 0, "", "", "");
	Crossroad crossroad2(0, 1, "", "", "");
	Crossroad crossroad3(1, 0, "", "", "");
	Crossroad crossroad4(1, 1, "", "", "");;
	std::list<Crossroad> crossroads;
	crossroads.push_back(crossroad1);
	crossroads.push_back(crossroad2);
	crossroads.push_back(crossroad3);
	crossroads.push_back(crossroad4);
	std::list<Crossroad>::iterator it = crossroads.begin();
	Crossroad* ptr1 = &(*it);
	it++;
	Crossroad* ptr2 = &(*it);
	it++;
	Crossroad* ptr3 = &(*it);
	it++;
	Crossroad* ptr4 = &(*it);

	matrix.addCrossroads(crossroads);

	EXPECT_EQ(ptr1, matrix.getObject(0, 0));
	EXPECT_EQ(ptr2, matrix.getObject(0, 1));
	EXPECT_EQ(ptr3, matrix.getObject(1, 0));
	EXPECT_EQ(ptr4, matrix.getObject(1, 1));
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
}

// TEST THE CITYOBJECTS SETSTATE()
TEST_F(CityObjectsTest, setState) {
	cObject.setState(normal);
	EXPECT_EQ(normal, cObject.getState());
	cObject.setState(burning);
	EXPECT_EQ(burning, cObject.getState());
	cObject.setState(beingrescued);
	EXPECT_EQ(beingrescued, cObject.getState());
	cObject.setState(destroyed);
	EXPECT_EQ(destroyed, cObject.getState());
	cObject.setState(intouchable);
	EXPECT_EQ(intouchable, cObject.getState());
}

// TEST THE CITY CONSTRUCTOR
TEST_F(CityTest, Constructor){
	City city("XML Files/stad.xml", "Output files/unusedOutput.txt");
	EXPECT_TRUE(city.properlyInitialized());
	EXPECT_EQ(50, city.getAmountHouses());
	EXPECT_EQ(1, city.getAmountDepartments());
	EXPECT_EQ(8, city.getAmountStreets());
	EXPECT_EQ(16, city.getAmountCrossroads());
	EXPECT_EQ(2, city.getAmountTrucks());
}

// TEST A UPDATE FUNCTION
TEST_F(CityTest, Update){
	City c("XML Files/stad.xml", "Output files/updateTest.txt");
	c.update_test();
	c.close();

	EXPECT_TRUE(FileCompare("Output files/updateTest.txt", "Expected Output/expectedUpdateTest.txt"));
}

// TEST IS VALID COORDINATE
TEST_F(CityTest, ValidCoordinate){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");
	EXPECT_TRUE(c.validCoordCheck(15, 7));
	EXPECT_TRUE(c.validCoordCheck(21, 0));
	EXPECT_TRUE(c.validCoordCheck(21, 15));
	EXPECT_TRUE(c.validCoordCheck(0, 0));
	EXPECT_TRUE(c.validCoordCheck(0, 15));
	EXPECT_FALSE(c.validCoordCheck(-1, -9));
	EXPECT_FALSE(c.validCoordCheck(-1, 0));
	EXPECT_FALSE(c.validCoordCheck(0, -1));
	EXPECT_FALSE(c.validCoordCheck('a', 9));
	EXPECT_FALSE(c.validCoordCheck(15, 'b'));
}

// TEST THE SETFIRE FUNCTION
TEST_F(CityTest, SetFire){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");
	CityObjects* burning_object = c.setFire(9, 12);
	EXPECT_EQ(burning, burning_object->getState());
	CityObjects* object = c.getObject(9, 12);
	EXPECT_EQ(burning, object->getState());
}

// TEST THE GET ADJECANTSTREET FUNCTION
TEST_F(CityTest, AdjecantStreet){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");
	CityObjects* object = c.getObject(3, 13);
	EXPECT_EQ(Coordinate(4, 15), c.getAdjecantStreet(object, Coordinate(8, 10)));
	object = c.getObject(20, 3);
	EXPECT_EQ(Coordinate(19, 5), c.getAdjecantStreet(object, Coordinate(8, 10)));
	object = c.getObject(8, 12);
	EXPECT_EQ(Coordinate(9, 10), c.getAdjecantStreet(object, Coordinate(16, 10)));
}

// TEST THE CHECK ORIENTATION FUNCTION
TEST_F(CityTest, CheckOrientation){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 0)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 0)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 0)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 0)));

	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 5)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 5)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 5)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 5)));

	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 10)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 10)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 10)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 10)));

	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 15)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 15)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 15)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 15)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 2)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 2)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 2)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 2)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 0)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 0)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 0)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 0)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 5)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 5)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 5)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 5)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 10)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 10)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 10)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 10)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 15)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 15)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 15)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 15)));
	c.close();
}

// TEST THE CLOSEST CROSSROAD FUNCTION
TEST_F(CityTest, ClosestCrossroad){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");

	EXPECT_EQ(Coordinate(0, 10), c.closestCrossroad(Coordinate(3, 10)).getLocation());
	EXPECT_EQ(Coordinate(7, 5), c.closestCrossroad(Coordinate(11, 5)).getLocation());
	EXPECT_EQ(Coordinate(0, 0), c.closestCrossroad(Coordinate(0, 2)).getLocation());
	EXPECT_EQ(Coordinate(16, 15), c.closestCrossroad(Coordinate(12, 15)).getLocation());
	EXPECT_EQ(Coordinate(7, 10), c.closestCrossroad(Coordinate(7, 10)).getLocation());
	c.close();
}

// TEST THE CLOSEST CORRECT CROSSROAD
TEST_F(CityTest, ClosestCorrectCrossroad){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");
	CityObjects* ptr = c.getObject(7,12);
	Street* streetptr = dynamic_cast<Street*>(ptr);
	EXPECT_EQ(Coordinate(7, 15), c.closestCorrectCrossroad(Coordinate(12, 15), streetptr).getLocation());
	c.close();
}

// TEST CALCULATE DISTANCE
TEST_F(CityTest, CalculateDistance){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");
	EXPECT_EQ(23, c.calculateDistance(Coordinate(0, 5), Coordinate(21, 15)));
	EXPECT_EQ(15, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 15)));
	EXPECT_EQ(25, c.calculateDistance(Coordinate(0, 15), Coordinate(21, 0)));
	EXPECT_EQ(0, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 0)));
	c.close();
}
// TEST DRIVE TRUCK
TEST_F(CityTest, DriveTruck){
	City c("XML Files/stad.xml", "Output files/unusedOutput.txt");
	Firetruck* ptr = c.getTruck(0);
	ptr->setDestination(Coordinate(7, 13));
	EXPECT_EQ(Coordinate(8, 10), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 10), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 11), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 12), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 13), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 13), ptr->getCoord());
	c.close();
}

// TEST CITY PARSER WITH SYNTAX ERROR

TEST_F(SimulationTest, InputSyntaxError){
	City c("XML Files/syntaxError.xml", "Output files/syntaxErrorOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/syntaxErrorOutput.txt", "Expected Output/expectedSyntaxErrorOutput.txt"));
}

// TEST CITY PARSER WITH NON EXISTING OBJECT

TEST_F(SimulationTest, InputObjectNotFound){
	City c("XML Files/invalidObject.xml", "Output files/invalidObjectOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/invalidObjectOutput.txt", "Expected Output/expectedInvalidObjectOutput.txt"));
}

// TEST THE PARSER WITH NEGATIVE COORDINATES

TEST_F(SimulationTest, NegativeCoordinate){
	City c("XML Files/negativeCoordinate.xml", "Output files/negativeCoordinateOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/negativeCoordinateOutput.txt", "Expected Output/expectedNegativeCoordinateOutput.txt"));
}

// TEST THE PARSER WITH NO ROOT OBJECT
TEST_F(SimulationTest, NoRootObject){
	City c("XML Files/noRoot.xml", "Output files/noRootOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/noRootOutput.txt", "Expected Output/expectedNoRootOutput.txt"));
}

// TEST THE PARSER WITH INVALID CITY EMPTY SPOTS

TEST_F(SimulationTest, InvalidCityEmptySpots){
	City c("XML Files/emptySpots.xml", "Output files/emptySpotsOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/emptySpotsOutput.txt", "Expected Output/expectedEmptySpotsOutput.txt"));
}

// TEST THE PARSER WITH OVERLAP

TEST_F(SimulationTest, Overlap){
	City c("XML Files/overlap.xml", "Output files/overlapOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/overlapOutput.txt", "Expected Output/expectedOverlapOutput.txt"));
}

// TEST WITH UNLINKED TRUCKS
TEST_F(SimulationTest, UnlinkedTrucks){
	City c("XML Files/unlinkedTrucks.xml", "Output files/unlinkedTrucksOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/unlinkedTrucksOutput.txt", "Expected Output/expectedUnlinkedTrucksOutput.txt"));
}

// HOUSES NOT LINKED TO STREET
TEST_F(SimulationTest, UnlinkedHouses){
	City c("XML Files/unlinkedStreets.xml", "Output files/unlinkedHousesOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/unlinkedHousesOutput.txt", "Expected Output/expectedUnlinkedHousesOutput.txt"));
}

// TEST A NORMAL SIMULATION
TEST_F(SimulationTest, NormalSimulation){
	City c("XML Files/stad.xml", "Output files/normalOutput.txt");
	c.update_test();
	c.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput.txt", "Expected Output/expectedNormalOutput.txt"));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
