/*
 * xmlparser.h
 *
 *  Created on: Mar 28, 2013
 *      Author: kristof
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <iostream>
#include <vector>
#include <cstdlib>
#include <assert.h>
#include <cctype>
#include <typeinfo>

#include "City.h"
#include "CityObjects.h"
#include "tinyxml.h"

class XmlParser {
private:
	std::pair<int, int> maxValues;
	City* city;

	XmlParser* _initCheck;
public:
	XmlParser(City*);
//	ENSURE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized.");

	void parseCity(std::string);
//	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properlyInitializedialized when calling parseCity(std::string) .");

	bool validCoordCheck(int, int);
//	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling validCoordCheck(int, int).");

	int compareCoord(int, int);
//	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling compareCoord(int, int).");

	std::pair<int, int> getMaxValues();
//	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling getMaxValues().");

	bool properlyInitialized();
};


#endif /* XMLPARSER_H_ */
