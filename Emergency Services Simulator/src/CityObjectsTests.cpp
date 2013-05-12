/*
 * CityObjectsTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "CityObjects.h"

class CityObjectsTest: public ::testing::Test {
protected:
	friend class CityObjects;

	CityObjects cObject;
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

	cObject = CityObjects(crossroad);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(crossroad, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());

	cObject = CityObjects(store);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(store, cObject.getType());
	EXPECT_EQ(normal, cObject.getState());

	cObject = CityObjects(policeStation);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(policeStation, cObject.getType());
	EXPECT_EQ(intouchable, cObject.getState());

	cObject = CityObjects(hospital);
	EXPECT_TRUE(cObject.init());
	EXPECT_EQ(hospital, cObject.getType());
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
	cObject.setState(beingrobbed);
	EXPECT_EQ(beingrobbed, cObject.getState());
	cObject.setState(beingrescuedR);
	EXPECT_EQ(beingrescuedR, cObject.getState());
}
