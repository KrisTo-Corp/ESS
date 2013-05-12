/*
 * MatrixTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "Matrix.h"

class MatrixTest: public ::testing::Test {
protected:
	friend class Matrix;

	Matrix matrix;
};

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
