//=======================================================================================
// Name        : xmlparser.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : City in C++, Ansi-style
//=======================================================================================

#include "xmlparser.h"

#define TIXML_USE_STL

XmlParser::XmlParser(City* inputCity) {
	city = inputCity;
	maxValues = std::pair<int, int>(0, 0);

	_initCheck = this;

	ENSURE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized.");

}

void XmlParser::parseCity(std::string filename) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properlyInitializedialized when calling parseCity(std::string) .");

	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::string error = doc.ErrorDesc();
		city->o.print(error + "\n");
		maxValues = std::pair<int, int>(-1, -1);
		return;
	}

	TiXmlElement* virtualCity = doc.FirstChildElement();

	if(virtualCity == NULL) {
		city->o.print("Failed to load file: No root element.\n");
		doc.Clear();
		maxValues =  std::pair<int, int>(-2, -2);
		return;
	}

	int maxX = 0;
	int maxY = 0;

	for(TiXmlElement* object = virtualCity->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
		std::string objectName = object->Value();
		if (objectName == "Huis") {
			bool valid = parseHouse(object, maxX, maxY);
			if (!valid) {
				continue;
			}
		}
		else if (objectName == "Straat") {
			bool valid = parseStreet(object, maxX, maxY);
			if (!valid) {
				continue;
			}
		}
		else if (objectName == "Brandweerwagen") {
			parseFiretruck(object);
		}
		else if (objectName == "Ziekenwagen") {
			parseAmbulance(object);
		}
		else if(objectName == "Brandweerkazerne") {
			bool valid = parseFiredep(object, maxX, maxY);
			if (!valid) {
				continue;
			}
		}
		else if (objectName == "Winkel") {
			bool valid = parseStore(object, maxX, maxY);
			if (!valid) {
				continue;
			}
		}
		else if (objectName == "Ziekenhuis") {
			bool valid = parseHospital(object, maxX, maxY);
			if (!valid) {
				continue;
			}
		}
		else if (objectName == "PolitieBureau") {
			bool valid = parsePolicedep(object, maxX, maxY);
			if (!valid) {
				continue;
			}
		}
		else if (objectName == "Politiewagen") {
			bool valid = parsePolicecar(object);
			if (!valid) {
				continue;
			}
		}
		else {
			city->o.print(objectName + " is not a valid object.\n");
			maxValues = std::pair<int, int>(-3, -3);
			return;
		}
	}
	maxValues = std::pair<int, int>(maxX, maxY);
}

bool XmlParser::parseHouse(TiXmlElement* object, int& maxX, int& maxY) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseHouse(TiXmlElement* object, int& maxX, int& maxY).");
	int x, y, hp;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		if(fieldName == "Locatie") {
			bool valid = parseLocation(field, maxX, maxY, x, y);
			if (!valid) {
				continue;
			}
		}
		else if(fieldName == "Brandbaarheid") {
			bool valid = parseBrandbaarheid(field, hp);
			if (!valid) {
				continue;
			}
		}
		else {
			city->o.print("Label " + fieldName + " is not a valid field. House\n");
			continue;
		}
	}
	if (!validCoordCheck(x,y)) {
			return false;
	}
	House house(x, y, hp, "House");
	city->getHouseList()->push_back(house);

	return true;
}

bool XmlParser::parseStreet(TiXmlElement* object, int& maxX, int& maxY) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseStreet(TiXmlElement* object, int& maxX, int& maxY).");

	int x_start, y_start, x_end, y_end;
	std::string name;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		if(fieldName == "Van") {
			x_start = atoi(field->Attribute("x"));
			y_start = atoi(field->Attribute("y"));

			if (!validCoordCheck(x_start,y_start)) {
				continue;
			}

			maxX = compareCoord(maxX, x_start);
			maxY = compareCoord(maxY, y_start);
		}
		else if(fieldName == "Naar") {
			x_end = atoi(field->Attribute("x"));
			y_end = atoi(field->Attribute("y"));

			if (!validCoordCheck(x_end,y_end)) {
				continue;
			}

			maxX = compareCoord(maxX, x_end);
			maxY = compareCoord(maxY, y_end);
		}
		else if(fieldName == "Naam") {
			TiXmlText* text = field->FirstChild()->ToText();
			if(text == NULL){
				continue;
			}
			else {
				name = text->Value();
			}
		}
		else {
			city->o.print("Label " + fieldName + " is not a valid field. Street\n");
			continue;
		}
	}

	if (!validCoordCheck(x_start,y_start)) {
		return false;
	}

	if (!validCoordCheck(x_end,y_end)) {
		return false;
	}

	Street street(x_start, y_start, x_end, y_end, name);
	city->getStreetsList()->push_back(street);

	return true;
}

void XmlParser::parseFiretruck(TiXmlElement* object) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseFiretruck(TiXmlElement* object).");
	std::string name, base;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		TiXmlText* text = field->FirstChild()->ToText();
		if(text == NULL){
			continue;
		}
		else if (fieldName == "Naam") {
			name = text->Value();
		}
		else if (fieldName == "Basis") {
			base = text->Value();
		}
		else {
			city->o.print("Label " + fieldName + " is not a valid field. Truck\n");
			continue;
		}
	}
	Firetruck truck(0, 0, name, base);
	city->getTruckList()->push_back(truck);
}

void XmlParser::parseAmbulance(TiXmlElement* object) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseAmbulance(TiXmlElement* object).");

	std::string name, base;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		TiXmlText* text = field->FirstChild()->ToText();
		if(text == NULL){
			continue;
		}
		else if (fieldName == "Naam") {
			name = text->Value();
		}
		else if (fieldName == "Basis") {
			base = text->Value();
		}
		else {
			city->o.print("Label " + fieldName + " is not a valid field. Truck\n");
			continue;
		}
	}
	Ambulance amb(0, 0, name, base);
	city->getAmbulancesList()->push_back(amb);
}

bool XmlParser::parseFiredep(TiXmlElement* object, int& maxX, int& maxY) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseFiredep(TiXmlElement* object, int& maxX, int& maxY).");
	int x_building, y_building, x_entrance, y_entrance;
	int hp = 0;
	std::string name;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		if(fieldName == "Locatie") {
			bool valid = parseLocation(field, maxX, maxY, x_building, y_building);
			if (!valid) {
				continue;
			}
		}
		else if(fieldName == "Ingang") {
			x_entrance = atoi(field->Attribute("X"));
			y_entrance  = atoi(field->Attribute("Y"));

			if (!validCoordCheck(x_entrance,y_entrance)) {
				continue;
			}

			maxX = compareCoord(maxX, x_entrance);
			maxY = compareCoord(maxY, y_entrance);
		}
		else if(fieldName == "Brandbaarheid") {
			bool valid = parseBrandbaarheid(field, hp);
			if (!valid) {
				continue;
			}
		}
		else if(fieldName == "Naam") {
			TiXmlText* text = field->FirstChild()->ToText();
			if(text == NULL){
				continue;
			}
			else {
				name = text->Value();
			}
		}
		else {
			city->o.print("Label " + fieldName + " is not a valid field. dep\n");
			continue;

		}
	}

	if (!validCoordCheck(x_building,y_building)) {
		return false;
	}

	if (!validCoordCheck(x_entrance,y_entrance)) {
		return false;
	}

	Fire_Department department(x_building, y_building, x_entrance, y_entrance, name, hp);
	city->getDepList()->push_back(department);

	return true;
}

bool XmlParser::parseStore(TiXmlElement* object, int& maxX, int& maxY) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseStore(TiXmlElement* object, int& maxX, int& maxY).");
	int x_building, y_building, width, length, hp, rp;
	std::string name;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		if(fieldName == "Locatie") {
			bool valid = parseLocation(field, maxX, maxY, x_building, y_building);
			if (!valid) {
				continue;
			}
		}
		else if (fieldName == "Grootte") {
			width = atoi(field->Attribute("Breedte"));
			length = atoi(field->Attribute("Hoogte"));

			/*
			 * Check to see if the input is valid: not negative and of type int.
			 */
			if (width < 0 || length < 0) {
				city->o.print("A Store can't have negative dimensions! Dimensions read: " + intToString(width) + " " + intToString(length) + "\n");
				continue;
			}
			else if (isalpha(width) || typeid(width) != typeid(int) || isalpha(length) || typeid(length) != typeid(int)) {
				city->o.print("Dimensions must be of type int! Dimensions read: " + intToString(width) + " " + intToString(length) + "\n");
				continue;
			}
		}
		else if(fieldName == "Brandbaarheid") {
			bool valid = parseBrandbaarheid(field, hp);
			if (!valid) {
				continue;
			}
		}
		else if(fieldName == "Overvalbaarheid") {
			TiXmlText* text = field->FirstChild()->ToText();
			if(text == NULL){
				continue;
			}
			std::string rp_string = text->Value();
			rp = atoi(rp_string.c_str());

			/*
			 * Check to see if the input is valid: not negative and of type int.
			 */
			if (rp < 0) {
				city->o.print("A house can not have a negative amount of robbery points! Robbery points read: " + intToString(rp) + "\n");
				continue;
			}
			else if (isalpha(rp) || typeid(rp) != typeid(int)) {
				city->o.print("Robbery points must be of type int! Robbery points read: " + intToString(rp) + "\n");
				continue;
			}
		}
		else {
			city->o.print("Label " + fieldName + " is not a valid field. " + "\n");
			continue;

		}
	}
	Store newStore;
	if (rp != 0) {
		newStore = Store(x_building, y_building, hp, rp, "Store", width, length, true);
	}
	else {
		newStore = Store(x_building, y_building, hp, rp, "Store", width, length, false);
	}
	city->getStoresList()->push_back(newStore);

	return true;
}

bool XmlParser::parseHospital(TiXmlElement* object, int& maxX, int& maxY) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseHospital(TiXmlElement* object, int& maxX, int& maxY).");
	int x_building, y_building, x_entrance, y_entrance, width, length, hp;
	std::string name;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		if(fieldName == "Naam") {
			TiXmlText* text = field->FirstChild()->ToText();
			if(text == NULL){
				continue;
			}
			else {
				name = text->Value();
			}
		}
		else if(fieldName == "Locatie") {
			bool valid = parseLocation(field, maxX, maxY, x_building, y_building);
			if (!valid) {
				continue;
			}
		}
		else if (fieldName == "Grootte") {
			width = atoi(field->Attribute("Breedte"));
			length = atoi(field->Attribute("Hoogte"));

			/*
			 * Check to see if the input is valid: not negative and of type int.
			 */
			if (width < 0 || length < 0) {
				city->o.print("A Store can't have negative dimensions! Dimensions read: " + intToString(width) + " " + intToString(length) + "\n");
				continue;
			}
			else if (isalpha(width) || typeid(width) != typeid(int) || isalpha(length) || typeid(length) != typeid(int)) {
				city->o.print("Dimensions must be of type int! Dimensions read: " + intToString(width) + " " + intToString(length) + "\n");
				continue;
			}
		}
		else if(fieldName == "Ingang") {
			x_entrance = atoi(field->Attribute("X"));
			y_entrance  = atoi(field->Attribute("Y"));

			if (!validCoordCheck(x_entrance,y_entrance)) {
				continue;
			}

			maxX = compareCoord(maxX, x_entrance);
			maxY = compareCoord(maxY, y_entrance);
		}
		else if(fieldName == "Brandbaarheid") {
			bool valid = parseBrandbaarheid(field, hp);
			if (!valid) {
				continue;
			}
		}
	}
	Hospital newHospital(x_building, y_building, x_entrance, y_entrance, hp, name, width, length);
	city->getHospitalsList()->push_back(newHospital);

	return true;
}

bool XmlParser::parsePolicedep(TiXmlElement* object, int& maxX, int& maxY) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parsePolicedep(TiXmlElement* object, int& maxX, int& maxY).");
	int x_building, y_building, x_entrance, y_entrance, width, length, hp;
	std::string name;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		if(fieldName == "Naam") {
			TiXmlText* text = field->FirstChild()->ToText();
			if(text == NULL){
				continue;
			}
			else {
				name = text->Value();
			}
		}
		else if(fieldName == "Locatie") {
			bool valid = parseLocation(field, maxX, maxY, x_building, y_building);
			if (!valid) {
				continue;
			}
		}
		else if (fieldName == "Grootte") {
			width = atoi(field->Attribute("Breedte"));
			length = atoi(field->Attribute("Hoogte"));

			/*
			 * Check to see if the input is valid: not negative and of type int.
			 */
			if (width < 0 || length < 0) {
				city->o.print("A Store can't have negative dimensions! Dimensions read: " + intToString(width) + " " + intToString(length) + "\n");
				continue;
			}
			else if (isalpha(width) || typeid(width) != typeid(int) || isalpha(length) || typeid(length) != typeid(int)) {
				city->o.print("Dimensions must be of type int! Dimensions read: " + intToString(width) + " " + intToString(length) + "\n");
				continue;
			}
		}
		else if(fieldName == "Ingang") {
			x_entrance = atoi(field->Attribute("X"));
			y_entrance  = atoi(field->Attribute("Y"));

			if (!validCoordCheck(x_entrance,y_entrance)) {
				continue;
			}

			maxX = compareCoord(maxX, x_entrance);
			maxY = compareCoord(maxY, y_entrance);
		}
		else if(fieldName == "Brandbaarheid") {
			bool valid = parseBrandbaarheid(field, hp);
			if (!valid) {
				continue;
			}
		}
	}
	PoliceStation newPolStation(x_building, y_building, x_entrance, y_entrance, hp, name, width, length);
	city->getPoliStatsList()->push_back(newPolStation);

	return true;
}

bool XmlParser::parsePolicecar(TiXmlElement* object) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parsePolicecar(TiXmlElement* object).");
	std::string name, base;
	for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
		std::string fieldName = field->Value();
		TiXmlText* text = field->FirstChild()->ToText();
		if(text == NULL){
			continue;
		}
		else if (fieldName == "Naam") {
			name = text->Value();
		}
		else if (fieldName == "Basis") {
			base = text->Value();
		}
		else {
			city->o.print("Label " + fieldName + " is not a valid field. Truck\n");
			continue;
		}
	}
	PoliceCar policeCar(0, 0, name, base);
	city->getPoliceCarsList()->push_back(policeCar);

	return true;
}

bool XmlParser::parseLocation(TiXmlElement* field, int& maxX, int& maxY, int& x, int& y) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseLocation(TiXmlElement* field, int& maxX, int& maxY, int& x, int& y).");

	x = atoi(field->Attribute("X"));
	y = atoi(field->Attribute("Y"));

	if (!validCoordCheck(x,y)) {
		return false;
	}

	maxX = compareCoord(maxX, x);
	maxY = compareCoord(maxY, y);

	return true;
}

bool XmlParser::parseBrandbaarheid(TiXmlElement* field, int& hp) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initialized when calling parseBrandbaarheid(TiXmlElement* field, int& hp).");

	TiXmlText* text = field->FirstChild()->ToText();
	if(text == NULL){
		return false;
	}
	std::string hp_string = text->Value();
	hp = atoi(hp_string.c_str());

	/*
	 * Check to see if the input is valid: not negative and of type int.
	 */
	if (hp < 0) {
		city->o.print("A house can not have a negative amount of hitpoints! Hitpoints read: " + doubleToString(hp) + "\n");
		return false;
	}
	else if (isalpha(hp) || typeid(hp) != typeid(int)) {
		city->o.print("Hitpoints must be of type int! Hitpoints read: " + doubleToString(hp) + "\n");
		return false;
	}

	return true;
}

bool XmlParser::validCoordCheck(int x, int y) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling validCoordCheck(int, int).");

	/*
	 * Check to see if the input is valid: not negative and of type int.
	 */

	if (x < 0 || y < 0) {
		city->o.print("A coordinate can not be negative! Coordinate read: (" + intToString(x) + "," + intToString(y) + ")\n");
		return false;
	}
	else if (isalpha(x) || isalpha(y) || typeid(x) != typeid(int) || typeid(y) != typeid(int)) {
		city->o.print("A coordinate must be of type int! Coordinate read: (" + intToString(x) + "," + intToString(y) + ")\n");
		return false;
	}
	else {
		return true;
	}
}

int XmlParser::compareCoord(int curMax, int testVal) {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling compareCoord(int, int).");

	if (testVal > curMax) {
		return testVal;
	}
	else {
		return curMax;
	}
}

std::pair<int, int> XmlParser::getMaxValues() {
	REQUIRE(properlyInitialized(), "Object 'XmlParser' was not properly properly Initializedialized when calling getMaxValues().");

	return maxValues;
}

bool XmlParser::properlyInitialized() {
	return _initCheck == this;
}
