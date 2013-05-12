/*
 * CasualtyTests.cpp
 *
 *  Created on: May 12, 2013
 *      Author: kristof
 */

#include "Casualty.h"

class CasualtyTest: public ::testing::Test {
protected:
	friend class Casualty;

	Casualty casualty;
};

// =============================
//	    TESTS FOR CASUALTY
// =============================

TEST_F(CasualtyTest, CasualtyDefaultConstructor){
	EXPECT_TRUE(casualty.properlyInitialized());
	EXPECT_EQ(10, casualty.getHP());
	EXPECT_EQ(hurt, casualty.getPState());
	EXPECT_EQ(NULL, casualty.getHome());
}

TEST_F(CasualtyTest, CasualtyConstructor){
	Structures structure;
	casualty = Casualty(&structure);
	EXPECT_TRUE(casualty.properlyInitialized());
	EXPECT_EQ(10, casualty.getHP());
	EXPECT_EQ(hurt, casualty.getPState());
	EXPECT_EQ(&structure, casualty.getHome());
}

TEST_F(CasualtyTest, CasualtySetStateFunction){
	EXPECT_EQ(hurt, casualty.getPState());
	casualty.setPassengerState(beingrescued);
	EXPECT_EQ(beingrescued, casualty.getPState());
	casualty.setPassengerState(inCare);
	EXPECT_EQ(inCare, casualty.getPState());
	casualty.setPassengerState(dead);
	EXPECT_EQ(dead, casualty.getPState());
}

TEST_F(CasualtyTest, CasualtyDecreaseHP){
	EXPECT_EQ(10, casualty.getHP());
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	EXPECT_EQ(7, casualty.getHP());
	casualty.setPassengerState(beingrescued);
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	EXPECT_EQ(4, casualty.getHP());
	casualty.setPassengerState(inCare);
	casualty.decreaseHP();
	EXPECT_EQ(4, casualty.getHP());
	casualty.setPassengerState(beingrescued);
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	casualty.decreaseHP();
	EXPECT_EQ(0, casualty.getHP());
	EXPECT_EQ(dead, casualty.getHP());
}

