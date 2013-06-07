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

	std::pair<int, int> getMaxValues();
//	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling getMaxValues().");

	bool properlyInitialized();

private:
	bool validCoordCheck(int, int);
//	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling validCoordCheck(int, int).");

	int compareCoord(int, int);
//	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling compareCoord(int, int).");

	bool parseHouse(TiXmlElement* object, int& maxX, int& maxY);

	bool parseStreet(TiXmlElement* object, int& maxX, int& maxY);

	void parseFiretruck(TiXmlElement* object);

	void parseAmbulance(TiXmlElement* object);

	bool parseFiredep(TiXmlElement* object, int& maxX, int& maxY);

	bool parseStore(TiXmlElement* object, int& maxX, int& maxY);

	bool parseHospital(TiXmlElement* object, int& maxX, int& maxY);

	bool parsePolicedep(TiXmlElement* object, int& maxX, int& maxY);

	bool parsePolicecar(TiXmlElement* object);

	bool parseLocation(TiXmlElement* field, int& maxX, int& maxY, int& x, int& y);

	bool parseBrandbaarheid(TiXmlElement* field, int& hp);
};


#endif /* XMLPARSER_H_ */
