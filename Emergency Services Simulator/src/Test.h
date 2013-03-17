/*
 * Test.h
 *
 *  Created on: Mar 17, 2013
 *      Author: kristof
 */

#ifndef TEST_H_
#define TEST_H_

#include <string>

class TestInput: public ::testing::Test {
private:
	City city;
public:
	TestInput(std::string filename, std::string outputfile);



};


#endif /* TEST_H_ */
