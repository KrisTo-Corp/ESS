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

class SimulationTest: public ::testing::Test {
protected:
	friend class City;
};

//TEST CITY PARSER WITH SYNTAX ERROR

TEST_F(SimulationTest, InputSyntaxError){
	std::ofstream stream("Output files/syntaxErrorOutput.txt");
	City c("XML-Files/syntaxError.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/syntaxErrorOutput.txt", "Expected Output/expectedSyntaxErrorOutput.txt"));
}

// TEST CITY PARSER WITH NON EXISTING OBJECT

TEST_F(SimulationTest, InputObjectNotFound){
	std::ofstream stream("Output files/invalidObjectOutput.txt");
	City c("XML-Files/invalidObject.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/invalidObjectOutput.txt", "Expected Output/expectedInvalidObjectOutput.txt"));
}

// TEST THE PARSER WITH NEGATIVE COORDINATES

TEST_F(SimulationTest, NegativeCoordinate){
	std::ofstream stream("Output files/noRootOutput.txt");
	City c("XML-Files/negativeCoordinate.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/negativeCoordinateOutput.txt", "Expected Output/expectedNegativeCoordinateOutput.txt"));
}

// TEST THE PARSER WITH NO ROOT OBJECT
TEST_F(SimulationTest, NoRootObject){
	std::ofstream stream("Output files/noRootOutput.txt");
	City c("XML-Files/noRoot.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/noRootOutput.txt", "Expected Output/expectedNoRootOutput.txt"));
}

// TEST THE PARSER WITH INVALID CITY EMPTY SPOTS

TEST_F(SimulationTest, InvalidCityEmptySpots){
	std::ofstream stream("Output files/emptySpotsOutput.txt");
	City c("XML-Files/emptySpots.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/emptySpotsOutput.txt", "Expected Output/expectedEmptySpotsOutput.txt"));
}

// TEST THE PARSER WITH OVERLAP

TEST_F(SimulationTest, Overlap){
	std::ofstream stream("Output files/overlapOutput.txt");
	City c("XML-Files/overlap.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/overlapOutput.txt", "Expected Output/expectedOverlapOutput.txt"));
}

// TEST WITH UNLINKED TRUCKS
TEST_F(SimulationTest, UnlinkedTrucks){
	std::ofstream stream("Output files/unlinkedTrucksOutput.txt");
	City c("XML-Files/unlinkedTrucks.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/unlinkedTrucksOutput.txt", "Expected Output/expectedUnlinkedTrucksOutput.txt"));
}

// HOUSES NOT LINKED TO STREET
TEST_F(SimulationTest, UnlinkedHouses){
	std::ofstream stream("Output files/unlinkedHousesOutput.txt");
	City c("XML-Files/unlinkedStreets.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/unlinkedHousesOutput.txt", "Expected Output/expectedUnlinkedHousesOutput.txt"));
}

// TEST A NORMAL SIMULATION
TEST_F(SimulationTest, NormalSimulation){
	std::ofstream stream("Output files/normalOutput.txt");
	City c("XML-Files/stad.xml", stream);
	simulateCity_Test(c, Coordinate(4, 14), Coordinate(15, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput.txt", "Expected Output/expectedNormalOutput.txt"));
}

TEST_F(SimulationTest, NormalSimulation2){
	std::ofstream stream("Output files/normalOutput2.txt");
	City c("XML-Files/stad.xml", stream);
	simulateCity_Test(c, Coordinate(3, 1), Coordinate(20, 1), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput2.txt", "Expected Output/expectedNormalOutput2.txt"));
}

TEST_F(SimulationTest, NormalSimulation3){
	std::ofstream stream( "Output files/normalOutput3.txt");
	City c("XML-Files/stad.xml", stream);
	simulateCity_Test(c, Coordinate(4, 11), Coordinate(12, 11), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput3.txt", "Expected Output/expectedNormalOutput3.txt"));
}

TEST_F(SimulationTest, NormalSimulation4){
	std::ofstream stream( "Output files/normalOutput4.txt");
	City c("XML-Files/stad2.0.xml", stream, "XML-Files/voertuigen2.0.xml");
	simulateCity_Test(c, Coordinate(1, 1), Coordinate(20, 14), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput4.txt", "Expected Output/expectedNormalOutput4.txt"));
}

TEST_F(SimulationTest, NormalSimulation5){
	std::ofstream stream( "Output files/normalOutput5.txt");
	City c("XML-Files/stad2.0_bis.xml", stream, "XML-Files/voertuigen2.0_bis.xml");
	simulateCity_Test(c, Coordinate(1, 6), Coordinate(20, 14), 5);
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput5.txt", "Expected Output/expectedNormalOutput5.txt"));
}

TEST_F(SimulationTest, NormalSimulation6){
	std::ofstream stream( "Output files/normalOutput6.txt");
	City c("XML-Files/stad2.0_bis.xml", stream, "XML-Files/voertuigen2.0_bis.xml");
	simulateCity_Test(c, Coordinate(15, 6), Coordinate(6, 11), 5, Coordinate(13, 9));
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput6.txt", "Expected Output/expectedNormalOutput6.txt"));
}

TEST_F(SimulationTest, NormalSimulation7){
	std::ofstream stream( "Output files/normalOutput7.txt");
	City c("XML-Files/stad2.0_bis.xml", stream, "XML-Files/voertuigen2.0_bis.xml");
	simulateCity_Test(c, Coordinate(20, 1), Coordinate(3, 14), 5, Coordinate(13, 9), Coordinate(11, 11));
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput7.txt", "Expected Output/expectedNormalOutput7.txt"));
}

TEST_F(SimulationTest, NormalSimulation8){
	std::ofstream stream( "Output files/normalOutput8.txt");
	City c("XML-Files/stad2.0_bis.xml", stream, "XML-Files/voertuigen2.0_bis.xml");
	simulateCity_Test(c, Coordinate(12, 14), Coordinate(6, 11), 5, Coordinate(12, 9));
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput8.txt", "Expected Output/expectedNormalOutput8.txt"));
}

TEST_F(SimulationTest, NormalSimulation9){
	std::ofstream stream( "Output files/normalOutput9.txt");
	City c("XML-Files/stad2.0_bis.xml", stream, "XML-Files/voertuigen2.0_bis.xml");
	simulateCity_Test(c, Coordinate(18, 11), Coordinate(6, 7), 5, Coordinate(8, 11));
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput9.txt", "Expected Output/expectedNormalOutput9.txt"));
}

TEST_F(SimulationTest, NormalSimulation10){
	std::ofstream stream( "Output files/normalOutput10.txt");
	City c("XML-Files/stad2.0_bis.xml", stream, "XML-Files/voertuigen2.0_bis.xml");
	simulateCity_Test(c, Coordinate(9, 13), Coordinate(10, 13), 5, Coordinate(10, 11));
	stream.close();
	EXPECT_TRUE(FileCompare("Output files/normalOutput10.txt", "Expected Output/expectedNormalOutput10.txt"));
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
