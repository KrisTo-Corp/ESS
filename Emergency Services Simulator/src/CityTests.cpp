/*
 * CityTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "City.h"

class CityTest: public ::testing::Test {
protected:
	friend class City;

};

// ===========================
//		TESTS FOR CITY
// ===========================

// TEST THE CITY CONSTRUCTOR
TEST_F(CityTest, Constructor){
	std::ofstream stream("Output files/unusedOutput.txt");
	City city("XML-Files/stad.xml", stream, "empty", false, false);
	EXPECT_TRUE(city.properlyInitialized());
	EXPECT_EQ(50, city.getAmountHouses());
	EXPECT_EQ(1, city.getAmountDepartments());
	EXPECT_EQ(8, city.getAmountStreets());
	EXPECT_EQ(16, city.getAmountCrossroads());
	EXPECT_EQ(2, city.getAmountTrucks());
	stream.close();
}

// TEST THE SETFIRE FUNCTION
TEST_F(CityTest, SetFire){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML-Files/stad.xml", stream);
	CityObjects* burning_object = c.setFire(9, 12);
	EXPECT_EQ(burning, burning_object->getState());
	CityObjects* object = c.getObject(9, 12);
	EXPECT_EQ(burning, object->getState());
}

// TEST THE GET ADJECANTSTREET FUNCTION
TEST_F(CityTest, AdjecantStreet){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML-Files/stad.xml", stream);
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
	City c("XML-Files/stad.xml", stream);
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
	City c("XML-Files/stad.xml", stream);

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
	City c("XML-Files/stad.xml", stream);
	CityObjects* ptr = c.getObject(7,12);
	Street* streetptr = dynamic_cast<Street*>(ptr);
	EXPECT_EQ(Coordinate(7, 15), c.closestCorrectCrossroad(Coordinate(12, 15), streetptr).getLocation());
	stream.close();
}

// TEST CALCULATE DISTANCE
TEST_F(CityTest, CalculateDistance){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML-Files/stad.xml", stream);
	EXPECT_EQ(23, c.calculateDistance(Coordinate(0, 5), Coordinate(21, 15)));
	EXPECT_EQ(15, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 15)));
	EXPECT_EQ(25, c.calculateDistance(Coordinate(0, 15), Coordinate(21, 0)));
	EXPECT_EQ(0, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 0)));
	stream.close();
}
// TEST DRIVE TRUCK
TEST_F(CityTest, DriveTruck){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML-Files/stad.xml", stream);
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



