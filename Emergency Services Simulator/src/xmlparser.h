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
public:
	XmlParser(City*);

	void parseCity(std::string);

	bool validCoordCheck(int, int);

	int compareCoord(int, int);

	std::pair<int, int> getMaxValues();
};


#endif /* XMLPARSER_H_ */
