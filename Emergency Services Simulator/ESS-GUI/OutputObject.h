/*
 * OutputObject.h
 *
 *  Created on: Apr 21, 2013
 *      Author: kristof
 */

#ifndef OUTPUTOBJECT_H_
#define OUTPUTOBJECT_H_

#include <iostream>
#include <string>
#include "DesignByContract.h"

class OutputObject {
private:
	std::ostream& output;
	bool html;
	OutputObject* _initCheck;

public:
    OutputObject(std::ostream& stream, bool web, bool onlyMap = false);
//	ENSURE(properlyInitialized(), "OutputObject was not correctly constructed.");
	virtual ~OutputObject();

	std::ostream& getOutput();
//	REQUIRE(properlyInitialized(), "Object 'OutputObject' was not properly initialized when calling getOutput().");

	void print(std::string);
//	REQUIRE(properlyInitialized(), "Object 'OutputObject' was not properly initialized when calling print(std::string).");

	void closeHTML();
//	REQUIRE(properlyInitialized(), "Object 'OutputObject' was not properly initialized when calling closeHTML().");

	bool getHTML();
//	REQUIRE(properlyInitialized(), "Object 'OutputObject' was not properly initialized when calling getHTML().");

	bool properlyInitialized();
};

#endif /* OUTPUTOBJECT_H_ */
