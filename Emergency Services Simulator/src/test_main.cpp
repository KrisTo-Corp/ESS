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
#include "Simulator.h"

// TODO: copy the newly formatted files as the correct test outcomes.

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

class CityObjectsTest: public ::testing::Test {
protected:
	friend class CityObjects;

	CityObjects cObject;
};

class CityTest: public ::testing::Test {
protected:
	friend class City;

};

class SimulationTest: public ::testing::Test {
protected:
	friend class City;
};



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
	cObject.setState(beingrescuedF);
	EXPECT_EQ(beingrescuedF, cObject.getState());
	cObject.setState(destroyed);
	EXPECT_EQ(destroyed, cObject.getState());
	cObject.setState(intouchable);
	EXPECT_EQ(intouchable, cObject.getState());
}

// TEST THE CITY CONSTRUCTOR
TEST_F(CityTest, Constructor){
	std::ofstream stream("Output files/unusedOutput.txt");
	City city("XML Files/stad.xml", stream);
	EXPECT_TRUE(city.properlyInitialized());
	EXPECT_EQ(50, city.getAmountHouses());
	EXPECT_EQ(1, city.getAmountDepartments());
	EXPECT_EQ(8, city.getAmountStreets());
	EXPECT_EQ(16, city.getAmountCrossroads());
	EXPECT_EQ(2, city.getAmountTrucks());
	stream.close();
}

// TEST A UPDATE FUNCTION
TEST_F(CityTest, Update){
	std::ofstream stream("Output files/updateTest.txt");
	City c("XML Files/stad.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();

	EXPECT_TRUE(FileCompare("Output files/updateTest.txt", "Expected Output/expectedUpdateTest.txt"));
}

// TEST IS VALID COORDINATE
/*
TEST_F(CityTest, ValidCoordinate){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
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
}*/

// TEST THE SETFIRE FUNCTION
TEST_F(CityTest, SetFire){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	CityObjects* burning_object = c.setFire(9, 12);
	EXPECT_EQ(burning, burning_object->getState());
	CityObjects* object = c.getObject(9, 12);
	EXPECT_EQ(burning, object->getState());
}

// TEST THE GET ADJECANTSTREET FUNCTION
TEST_F(CityTest, AdjecantStreet){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	CityObjects* object = c.getObject(3, 13);
	EXPECT_EQ(Coordinate(4, 15), c.getAdjecantStreet(object, Coordinate(8, 10)));
	object = c.getObject(20, 3);
	EXPECT_EQ(Coordinate(19, 5), c.getAdjecantStreet(object, Coordinate(8, 10)));
	object = c.getObject(8, 12);
	EXPECT_EQ(Coordinate(9, 10), c.getAdjecantStreet(object, Coordinate(16, 10)));
}

// TEST THE CHECK ORIENTATION FUNCTION
TEST_F(CityTest, CheckOrientation){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
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
	stream.close();
}

// TEST THE CLOSEST CROSSROAD FUNCTION
TEST_F(CityTest, ClosestCrossroad){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);

	EXPECT_EQ(Coordinate(0, 10), c.closestCrossroad(Coordinate(3, 10)).getLocation());
	EXPECT_EQ(Coordinate(7, 5), c.closestCrossroad(Coordinate(11, 5)).getLocation());
	EXPECT_EQ(Coordinate(0, 0), c.closestCrossroad(Coordinate(0, 2)).getLocation());
	EXPECT_EQ(Coordinate(16, 15), c.closestCrossroad(Coordinate(12, 15)).getLocation());
	EXPECT_EQ(Coordinate(7, 10), c.closestCrossroad(Coordinate(7, 10)).getLocation());
	stream.close();
}

// TEST THE CLOSEST CORRECT CROSSROAD
TEST_F(CityTest, ClosestCorrectCrossroad){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	CityObjects* ptr = c.getObject(7,12);
	Street* streetptr = dynamic_cast<Street*>(ptr);
	EXPECT_EQ(Coordinate(7, 15), c.closestCorrectCrossroad(Coordinate(12, 15), streetptr).getLocation());
	stream.close();
}

// TEST CALCULATE DISTANCE
TEST_F(CityTest, CalculateDistance){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	EXPECT_EQ(23, c.calculateDistance(Coordinate(0, 5), Coordinate(21, 15)));
	EXPECT_EQ(15, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 15)));
	EXPECT_EQ(25, c.calculateDistance(Coordinate(0, 15), Coordinate(21, 0)));
	EXPECT_EQ(0, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 0)));
	stream.close();
}
// TEST DRIVE TRUCK
TEST_F(CityTest, DriveTruck){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
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
	stream.close();
}

// TEST CITY PARSER WITH SYNTAX ERROR

TEST_F(SimulationTest, InputSyntaxError){
	std::ofstream stream("Output files/syntaxErrorOutput.txt");
	City c("XML Files/syntaxError.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/syntaxErrorOutput.txt", "Expected Output/expectedSyntaxErrorOutput.txt"));
}

// TEST CITY PARSER WITH NON EXISTING OBJECT

TEST_F(SimulationTest, InputObjectNotFound){
	std::ofstream stream("Output files/invalidObjectOutput.txt");
	City c("XML Files/invalidObject.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/invalidObjectOutput.txt", "Expected Output/expectedInvalidObjectOutput.txt"));
}

// TEST THE PARSER WITH NEGATIVE COORDINATES

TEST_F(SimulationTest, NegativeCoordinate){
	std::ofstream stream("Output files/noRootOutput.txt");
	City c("XML Files/negativeCoordinate.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/negativeCoordinateOutput.txt", "Expected Output/expectedNegativeCoordinateOutput.txt"));
}

// TEST THE PARSER WITH NO ROOT OBJECT
TEST_F(SimulationTest, NoRootObject){
	std::ofstream stream("Output files/noRootOutput.txt");
	City c("XML Files/noRoot.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/noRootOutput.txt", "Expected Output/expectedNoRootOutput.txt"));
}

// TEST THE PARSER WITH INVALID CITY EMPTY SPOTS

TEST_F(SimulationTest, InvalidCityEmptySpots){
	std::ofstream stream("Output files/emptySpotsOutput.txt");
	City c("XML Files/emptySpots.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/emptySpotsOutput.txt", "Expected Output/expectedEmptySpotsOutput.txt"));
}

// TEST THE PARSER WITH OVERLAP

TEST_F(SimulationTest, Overlap){
	std::ofstream stream("Output files/overlapOutput.txt");
	City c("XML Files/overlap.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/overlapOutput.txt", "Expected Output/expectedOverlapOutput.txt"));
}

// TEST WITH UNLINKED TRUCKS
TEST_F(SimulationTest, UnlinkedTrucks){
	std::ofstream stream("Output files/unlinkedTrucksOutput.txt");
	City c("XML Files/unlinkedTrucks.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/unlinkedTrucksOutput.txt", "Expected Output/expectedUnlinkedTrucksOutput.txt"));
}

// HOUSES NOT LINKED TO STREET
TEST_F(SimulationTest, UnlinkedHouses){
	std::ofstream stream("Output files/unlinkedHousesOutput.txt");
	City c("XML Files/unlinkedStreets.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/unlinkedHousesOutput.txt", "Expected Output/expectedUnlinkedHousesOutput.txt"));
}

// TEST A NORMAL SIMULATION
TEST_F(SimulationTest, NormalSimulation){
	std::ofstream stream("Output files/normalOutput.txt");
	City c("XML Files/stad.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput.txt", "Expected Output/expectedNormalOutput.txt"));
}

TEST_F(SimulationTest, NormalSimulation2){
	std::ofstream stream("Output files/normalOutput2.txt");
	City c("XML Files/stad.xml", stream);
	simulateCity_Test(c, Coordinate(3, 1), Coordinate(20, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput2.txt", "Expected Output/expectedNormalOutput2.txt"));
}

TEST_F(SimulationTest, NormalSimulation3){
	std::ofstream stream( "Output files/normalOutput3.txt");
	City c("XML Files/stad.xml", stream);
	simulateCity_Test(c, Coordinate(4, 11), Coordinate(12, 11), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput3.txt", "Expected Output/expectedNormalOutput3.txt"));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
