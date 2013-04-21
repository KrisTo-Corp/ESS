/*
 * helpers.cpp
 *
 *  Created on: Apr 21, 2013
 *      Author: kristof
 */

#include "helpers.h"


std::string doubleToString(double d) {
	std::stringstream ss;
	ss << d;
	std::string str = ss.str();
	return str;
}

std::string intToString(int i) {
	std::stringstream ss;
	ss << i;
	std::string str = ss.str();
	return str;
}


