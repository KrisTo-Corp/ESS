/*
 * StructuresTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "Structures.h"

class StructuresTest: public ::testing::Test {
protected:
	friend class Structures;
	friend class House;
	friend class Fire_Department;
	friend class Store;
	friend class PoliceStation;
	friend class Hospital;

	Structures structure;
	House test_house;
	Fire_Department test_department;
	Store store;
	PoliceStation policestation;
	Hospital hospital;
};

// TEST DEFAULT CONSTRUCTOR STRUCTURES
TEST_F(StructuresTest, DefaultConstructor){
	EXPECT_TRUE(structure.init());
	EXPECT_EQ("", structure.getName());
	EXPECT_EQ(Coordinate(0, 0), structure.getLocation());
	EXPECT_EQ(0, structure.getWidth());
	EXPECT_EQ(0, structure.getLength());
	EXPECT_EQ(none, structure.getType());
	EXPECT_EQ(intouchable, structure.getState());
	EXPECT_EQ(0, structure.getHP());
	EXPECT_EQ(0, structure.getMaxHp());
	EXPECT_EQ(0, structure.getSpreadcounter());
}

// TEST SPECIFIED CONSTRUCTOR STRUCTURES
TEST_F(StructuresTest, Constructor){
	structure = Structures(12, 13, "structure", 9, 11, house, 20);
	EXPECT_TRUE(structure.init());
	EXPECT_EQ("structure", structure.getName());
	EXPECT_EQ(Coordinate(12, 13), structure.getLocation());
	EXPECT_EQ(9, structure.getWidth());
	EXPECT_EQ(11, structure.getLength());
	EXPECT_EQ(house, structure.getType());
	EXPECT_EQ(normal, structure.getState());
	EXPECT_EQ(20, structure.getHP());
	EXPECT_EQ(20, structure.getMaxHp());
	EXPECT_EQ(0, structure.getSpreadcounter());
}

// TEST STRUCTURE SPREADCOUNTER FUNCTIONS
TEST_F(StructuresTest, SpreadcounterFunctions){
	EXPECT_EQ(0, structure.getSpreadcounter());
	structure.increaseSpreadcounter();
	EXPECT_EQ(1, structure.getSpreadcounter());
	structure.increaseSpreadcounter();
	EXPECT_EQ(2, structure.getSpreadcounter());
	structure.resetSpreadcounter();
	EXPECT_EQ(0, structure.getSpreadcounter());
}

// TEST DECREASE HP FUNCTION
TEST_F(StructuresTest, DecreaseHP){
	structure = Structures(12, 13, "structure", 2, 2, house, 10);
	EXPECT_EQ(10, structure.getHP());
	structure.decreaseHP();
	EXPECT_EQ(9.75, structure.getHP());
	structure.decreaseHP();
	EXPECT_EQ(9.5, structure.getHP());
	structure.decreaseHP();
	EXPECT_EQ(9.25, structure.getHP());
	structure.decreaseHP();
	EXPECT_EQ(9, structure.getHP());
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

// TEST THE DEFAULT CONSTRUCTOR FROM STORE
TEST_F(StructuresTest, StoreDefaultConstructor){
	EXPECT_TRUE(store.init());
	EXPECT_TRUE(store.getRobable());
	EXPECT_EQ(0, store.getRP());
}

// TEST THE SPECIFIED CONSTRUCTOR FROM STORE
TEST_F(StructuresTest, StoreConstructor){
	store = Store(1, 1, 10, 20, "store", 1, 1, true);
	EXPECT_TRUE(store.init());
	EXPECT_TRUE(store.getRobable());
	EXPECT_EQ(20, store.getRP());
}

// TEST THE DECREASE RP FUNCTIONS
TEST_F(StructuresTest, DecreaseRPFunctions){
	store = Store(1, 1, 10, 20, "store", 1, 1, true);
	EXPECT_EQ(20, store.getRP());
	store.decreaseRP();
	EXPECT_EQ(19, store.getRP());
	store.decreaseRP();
	EXPECT_EQ(18, store.getRP());
}

// TEST DEFAULT CONSTRUCTOR POLICESTATION
TEST_F(StructuresTest, PoliceStationDefaultConstructor){
	EXPECT_TRUE(policestation.init());
	EXPECT_EQ("", policestation.getName());
	EXPECT_EQ(Coordinate(0, 0), policestation.getLocation());
	EXPECT_EQ(Coordinate(0, 0), policestation.getEntrance());
	EXPECT_EQ(0, policestation.getWidth());
	EXPECT_EQ(0, policestation.getLength());
	EXPECT_EQ(0, policestation.getAmountCars());
	EXPECT_EQ(policeStation, policestation.getType());
	EXPECT_EQ(intouchable, policestation.getState());
}

// TEST SPECIFIED CONSTRUCTOR FIRE_DEPARTMENT
TEST_F(StructuresTest, PoliceStationConstructor){
	policestation = PoliceStation(10, 9, 8, 7, 20, "station", 4, 4);
	EXPECT_TRUE(policestation.init());
	EXPECT_EQ("station", policestation.getName());
	EXPECT_EQ(Coordinate(10, 9), policestation.getLocation());
	EXPECT_EQ(Coordinate(8, 7), policestation.getEntrance());
	EXPECT_EQ(4, policestation.getWidth());
	EXPECT_EQ(4, policestation.getLength());
	EXPECT_EQ(0, policestation.getAmountCars());
	EXPECT_EQ(policeStation, policestation.getType());
	EXPECT_EQ(intouchable, policestation.getState());
}

// TEST THE TRUCK FUNCTIONS FROM FIRE DEPARTMENT
TEST_F(StructuresTest, PoliceStationCarFunctions){
	PoliceCar car1;
	PoliceCar car2;
	PoliceCar car3;
	EXPECT_EQ(0, policestation.getAmountCars());
	policestation.addCar(&car1);
	EXPECT_EQ(1, policestation.getAmountCars());
	policestation.addCar(&car3);
	policestation.addCar(&car2);
	EXPECT_EQ(3, policestation.getAmountCars());
}

// TEST DEFAULT CONSTRUCTOR POLICESTATION
TEST_F(StructuresTest, HospitalDefaultConstructor){
	EXPECT_TRUE(hospital.init());
	EXPECT_EQ("", hospital.getName());
	EXPECT_EQ(Coordinate(0, 0), hospital.getLocation());
	EXPECT_EQ(Coordinate(0, 0), hospital.getEntrance());
	EXPECT_EQ(0, hospital.getWidth());
	EXPECT_EQ(0, hospital.getLength());
	EXPECT_EQ(0, hospital.getAmountAmbulances());
	EXPECT_EQ(intouchable, hospital.getState());
}

// TEST SPECIFIED CONSTRUCTOR FIRE_DEPARTMENT
TEST_F(StructuresTest, HospitalConstructor){
	hospital = Hospital(10, 9, 8, 7, 20, "hospital", 4, 4);
	EXPECT_TRUE(hospital.init());
	EXPECT_EQ("hospital", hospital.getName());
	EXPECT_EQ(Coordinate(10, 9), hospital.getLocation());
	EXPECT_EQ(Coordinate(8, 7), hospital.getEntrance());
	EXPECT_EQ(4, hospital.getWidth());
	EXPECT_EQ(4, hospital.getLength());
	EXPECT_EQ(0, hospital.getAmountAmbulances());
	EXPECT_EQ(intouchable, hospital.getState());
}

// TEST THE TRUCK FUNCTIONS FROM FIRE DEPARTMENT
TEST_F(StructuresTest, HospitalCarFunctions){
	Ambulance car1;
	Ambulance car2;
	Ambulance car3;
	EXPECT_EQ(0, hospital.getAmountAmbulances());
	hospital.addAmbulance(&car1);
	EXPECT_EQ(1, hospital.getAmountAmbulances());
	hospital.addAmbulance(&car3);
	hospital.addAmbulance(&car2);
	EXPECT_EQ(3, hospital.getAmountAmbulances());
}
