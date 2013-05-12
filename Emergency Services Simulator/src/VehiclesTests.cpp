/*
 * VehiclesTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "Vehicles.h"

class VehiclesTest: public ::testing::Test {
protected:
	friend class Vehicles;
	friend class Firetruck;
	friend class PoliceCar;
	friend class Ambulance;

	Vehicles vehicle;
	Firetruck firetruck;
	PoliceCar policecar;
	Ambulance ambulance;
};


// TEST THE DEFAULT VEHICLES CONSTRUCTOR
TEST_F(VehiclesTest, DefaultConstructor){
	EXPECT_TRUE(vehicle.properlyInitialized());
	EXPECT_EQ("", vehicle.getName());
	EXPECT_EQ(Coordinate(0, 0), vehicle.getCoord());
}

// TEST THE SPECIFIED VEHICLES CONSTRUCTOR
TEST_F(VehiclesTest, Constructor){
	vehicle = Vehicles(10, 9, "car", "base");
	EXPECT_TRUE(vehicle.properlyInitialized());
	EXPECT_EQ("car", vehicle.getName());
	EXPECT_EQ(Coordinate(10, 9), vehicle.getCoord());
}

// TEST THE SET FUNCTION FROM VEHICLES
TEST_F(VehiclesTest, SetFunctions){
	Coordinate loc(5, 5);
	Coordinate tempdest(7, 9);
	Coordinate dest(1, 19);
	Structures structure;
	vehicle.setCoord(loc);
	vehicle.setTempDest(tempdest);
	vehicle.setDestination(dest);
	vehicle.setTarget(&structure);
	vehicle.setGoToTemp(true);
	vehicle.setAvailable(true);
	vehicle.setIsHome(true);
	EXPECT_EQ(loc, vehicle.getCoord());
	EXPECT_EQ(tempdest, vehicle.getTempDest());
	EXPECT_EQ(dest, vehicle.getDestination());
	EXPECT_EQ(&structure, vehicle.getTarget());
	EXPECT_TRUE(vehicle.getGoToTemp());
	EXPECT_TRUE(vehicle.getAvailable());
	EXPECT_TRUE(vehicle.getIsHome());
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

// TEST THE MOVE FUNCTION FROM VEHICLES
TEST_F(VehiclesTest, VehicleMove){
	EXPECT_EQ(Coordinate(0, 0), vehicle.getCoord());
	vehicle.move("up");
	EXPECT_EQ(Coordinate(0, 1), vehicle.getCoord());
	vehicle.move("down");
	EXPECT_EQ(Coordinate(0, 0), vehicle.getCoord());
	vehicle.move("right");
	EXPECT_EQ(Coordinate(1, 0), vehicle.getCoord());
	vehicle.move("left");
	EXPECT_EQ(Coordinate(0, 0), vehicle.getCoord());
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

// TEST THE POLICECAR DEFAULT CONSTRUCTOR
TEST_F(VehiclesTest, PoliceCarDefaultConstructor){
	EXPECT_TRUE(policecar.properlyInitialized());
	EXPECT_EQ("", policecar.getName());
	EXPECT_EQ("", policecar.getBasename());
	EXPECT_EQ(Coordinate(0, 0), policecar.getCoord());
	EXPECT_EQ(Coordinate(0, 0), policecar.getTempDest());
	EXPECT_EQ(Coordinate(0, 0), policecar.getDestination());
	EXPECT_EQ(NULL, policecar.getBaseptr());
	EXPECT_FALSE(policecar.getGoToTemp());
	EXPECT_TRUE(policecar.getAvailable());
	EXPECT_TRUE(policecar.getIsHome());
	EXPECT_EQ(NULL, policecar.getTarget());
}

// TEST THE POLICECAR SPECIFIED CONSTRUCTOR
TEST_F(VehiclesTest, PoliceCarConstructor){
	policecar = PoliceCar(1, 1, "car", "base");
	EXPECT_TRUE(policecar.properlyInitialized());
	EXPECT_EQ("car", policecar.getName());
	EXPECT_EQ("base", policecar.getBasename());
	EXPECT_EQ(Coordinate(1, 1), policecar.getCoord());
	EXPECT_EQ(Coordinate(0, 0), policecar.getTempDest());
	EXPECT_EQ(Coordinate(0, 0), policecar.getDestination());
	EXPECT_EQ(NULL, policecar.getBaseptr());
	EXPECT_FALSE(policecar.getGoToTemp());
	EXPECT_TRUE(policecar.getAvailable());
	EXPECT_TRUE(policecar.getIsHome());
	EXPECT_EQ(NULL, policecar.getTarget());
}

// TEST THE POLICECAR LINKBASE
TEST_F(VehiclesTest, PoliceCarLinkBase){
	PoliceStation station;
	policecar.linkBase(&station);
	EXPECT_EQ(&station, policecar.getBaseptr());
}

// TEST THE AMBULANCE DEFAULT CONSTRUCTOR
TEST_F(VehiclesTest, AmbulanceDefaultConstructor){
	EXPECT_TRUE(ambulance.properlyInitialized());
	EXPECT_EQ("", ambulance.getName());
	EXPECT_EQ("", ambulance.getBasename());
	EXPECT_EQ(Coordinate(0, 0), ambulance.getCoord());
	EXPECT_EQ(Coordinate(0, 0), ambulance.getTempDest());
	EXPECT_EQ(Coordinate(0, 0), ambulance.getDestination());
	EXPECT_EQ(NULL, ambulance.getBaseptr());
	EXPECT_FALSE(ambulance.getGoToTemp());
	EXPECT_TRUE(ambulance.getAvailable());
	EXPECT_TRUE(ambulance.getIsHome());
	EXPECT_EQ(NULL, ambulance.getTarget());
}

// TEST THE ambulance SPECIFIED CONSTRUCTOR
TEST_F(VehiclesTest, AmbulanceConstructor){
	ambulance = Ambulance(1, 1, "car", "base");
	EXPECT_TRUE(ambulance.properlyInitialized());
	EXPECT_EQ("car", ambulance.getName());
	EXPECT_EQ("base", ambulance.getBasename());
	EXPECT_EQ(Coordinate(1, 1), ambulance.getCoord());
	EXPECT_EQ(Coordinate(0, 0), ambulance.getTempDest());
	EXPECT_EQ(Coordinate(0, 0), ambulance.getDestination());
	EXPECT_EQ(NULL, ambulance.getBaseptr());
	EXPECT_FALSE(ambulance.getGoToTemp());
	EXPECT_TRUE(ambulance.getAvailable());
	EXPECT_TRUE(ambulance.getIsHome());
	EXPECT_EQ(NULL, ambulance.getTarget());
}

// TEST THE AMBULANCE LINKBASE
TEST_F(VehiclesTest, AmbulanceLinkBase){
	Hospital hospital;
	ambulance.linkBase(&hospital);
	EXPECT_EQ(&hospital, ambulance.getBaseptr());
}

// TEST THE AMBULANCE SET FUNCTIONS
TEST_F(VehiclesTest, AmbulanceSetFunctions){
	Structures structure;
	Casualty cas(&structure);
	ambulance.setPassenger(&cas);
	ambulance.setContaining(true);
	EXPECT_TRUE(ambulance.getContaining());
	EXPECT_EQ(&cas, ambulance.getPassenger());
}


