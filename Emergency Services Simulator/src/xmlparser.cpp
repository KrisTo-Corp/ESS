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
}

void XmlParser::parseCity(std::string filename) {
	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		city->output << doc.ErrorDesc() << std::endl;
		maxValues = std::pair<int, int>(-1, -1);
		return;
	}

	TiXmlElement* virtualCity = doc.FirstChildElement();

	if(virtualCity == NULL) {
		city->output << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		maxValues =  std::pair<int, int>(-2, -2);
		return;
	}

	int maxX = 0;
	int maxY = 0;

	for(TiXmlElement* object = virtualCity->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
		std::string objectName = object->Value();
		if (objectName == "Huis") {
			std::cout << "house 1" << std::endl;

			int x, y, hp;

			for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
				std::string fieldName = field->Value();
				if(fieldName == "Locatie") {
					x = atoi(field->Attribute("X"));
					y = atoi(field->Attribute("Y"));

					if (!validCoordCheck(x,y)) {
						continue;
					}

					maxX = compareCoord(maxX, x);
					maxY = compareCoord(maxY, y);
				}
				else if(fieldName == "Brandbaarheid") {
					TiXmlText* text = field->FirstChild()->ToText();
					if(text == NULL){
						continue;
					}
					std::string hp_string = text->Value();
					hp = atoi(hp_string.c_str());

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (hp < 0) {
						city->output << "A house can not have a negative amount of hitpoints! Hitpoints read: " << hp << std::endl;
						continue;
					}
					else if (isalpha(hp) || typeid(hp) != typeid(int)) {
						city->output << "Hitpoints must be of type int! Hitpoints read: " << hp << std::endl;
						continue;
					}
				}
				else {
					city->output << "Label " << fieldName << " is not a valid field. House" << std::endl;
					continue;
				}
			}
			if (!validCoordCheck(x,y)) {
					continue;
			}
			// validcoordcheck here
			House house(x, y, hp, "house");
			city->getHouseList()->push_back(house);
			std::cout << "house 1" << std::endl;
		}
		else if (objectName == "Straat") {
			std::cout << "street 1" << std::endl;
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
					city->output << "Label " << fieldName << " is not a valid field. Street" << std::endl;
					continue;
				}
			}

			if (!validCoordCheck(x_start,y_start)) {
				continue;
			}

			if (!validCoordCheck(x_end,y_end)) {
				continue;
			}

			Street street(x_start, y_start, x_end, y_end, name);
			city->getStreetsList()->push_back(street);
			std::cout << "street 1" << std::endl;
		}
		else if (objectName == "Brandweerwagen") {
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
					city->output << "Label " << fieldName << " is not a valid field. Truck" << std::endl;
					continue;
				}
			}
			Firetruck truck(0, 0, name, base);
			city->getTruckList()->push_back(truck);
		}
		else if(objectName == "Brandweerkazerne") {
			std::cout << "dep 1" << std::endl;
			int x_building, y_building, x_entrance, y_entrance;
			int hp = 0;
			std::string name;
			for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
				std::string fieldName = field->Value();
				if(fieldName == "Locatie") {
					x_building = atoi(field->Attribute("X"));
					y_building = atoi(field->Attribute("Y"));

					if (!validCoordCheck(x_building,y_building)) {
						continue;
					}

					maxX = compareCoord(maxX, x_building);
					maxY = compareCoord(maxY, y_building);
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
					TiXmlText* text = field->FirstChild()->ToText();
					if(text == NULL){
						continue;
					}
					std::string hp_string = text->Value();
					hp = atoi(hp_string.c_str());

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (hp < 0) {
						city->output << "A house can not have a negative amount of hitpoints! Hitpoints read: " << hp << std::endl;
						continue;
					}
					else if (isalpha(hp) || typeid(hp) != typeid(int)) {
						city->output << "Hitpoints must be of type int! Hitpoints read: " << hp << std::endl;
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
					city->output << "Label " << fieldName << " is not a valid field. dep" << std::endl;
					continue;

				}
			}

			if (!validCoordCheck(x_building,y_building)) {
				continue;
			}

			if (!validCoordCheck(x_entrance,y_entrance)) {
				continue;
			}

			Fire_Department department(x_building, y_building, x_entrance, y_entrance, name, hp);
			city->getDepList()->push_back(department);
			std::cout << "dep 1" << std::endl;
		}
		else if (objectName == "Winkel") {
			std::cout << "store 1" << std::endl;

			int x_building, y_building, width, length, hp, rp;
			std::string name;
			for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
				std::string fieldName = field->Value();
				if(fieldName == "Locatie") {
					x_building = atoi(field->Attribute("X"));
					y_building = atoi(field->Attribute("Y"));

					if (!validCoordCheck(x_building,y_building)) {
						continue;
					}

					maxX = compareCoord(maxX, x_building);
					maxY = compareCoord(maxY, y_building);
				}
				else if (fieldName == "Grootte") {
					width = atoi(field->Attribute("Breedte"));
					length = atoi(field->Attribute("Hoogte"));

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (width < 0 || length < 0) {
						city->output << "A Store can't have negative dimensions! Dimensions read: " << width << " " << length << std::endl;
						continue;
					}
					else if (isalpha(width) || typeid(width) != typeid(int) || isalpha(length) || typeid(length) != typeid(int)) {
						city->output << "Dimensions must be of type int! Dimensions read: " << width << " " << length << std::endl;
						continue;
					}
				}
				else if(fieldName == "Brandbaarheid") {
					TiXmlText* text = field->FirstChild()->ToText();
					if(text == NULL){
						continue;
					}
					std::string hp_string = text->Value();
					hp = atoi(hp_string.c_str());

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (hp < 0) {
						city->output << "A house can not have a negative amount of hitpoints! Hitpoints read: " << hp << std::endl;
						continue;
					}
					else if (isalpha(hp) || typeid(hp) != typeid(int)) {
						city->output << "Hitpoints must be of type int! Hitpoints read: " << hp << std::endl;
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
						city->output << "A house can not have a negative amount of robbery points! Robbery points read: " << rp << std::endl;
						continue;
					}
					else if (isalpha(rp) || typeid(rp) != typeid(int)) {
						city->output << "Robbery points must be of type int! Robbery points read: " << hp << std::endl;
						continue;
					}
				}
				else {
					city->output << "Label " << fieldName << " is not a valid field. dep" << std::endl;
					continue;

				}
			}
			std::cout << "CONSTRUCTING" << std::endl;
			Store newStore(x_building, y_building, hp, rp, "Store", width, length);
			std::cout << "next is wrong!" << std::endl;
			city->getStoresList()->push_back(newStore);
			std::cout << "store 1" << std::endl;
		}
		else if (objectName == "Ziekenhuis") {
			std::cout << "hospital 1" << std::endl;
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
					x_building = atoi(field->Attribute("X"));
					y_building = atoi(field->Attribute("Y"));

					if (!validCoordCheck(x_building,y_building)) {
						continue;
					}

					maxX = compareCoord(maxX, x_building);
					maxY = compareCoord(maxY, y_building);
				}
				else if (fieldName == "Grootte") {
					width = atoi(field->Attribute("Breedtje"));
					length = atoi(field->Attribute("Hoogte"));

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (width < 0 || length < 0) {
						city->output << "A Store can't have negative dimensions! Dimensions read: " << width << " " << length << std::endl;
						continue;
					}
					else if (isalpha(width) || typeid(width) != typeid(int) || isalpha(length) || typeid(length) != typeid(int)) {
						city->output << "Dimensions must be of type int! Dimensions read: " << width << " " << length << std::endl;
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
					TiXmlText* text = field->FirstChild()->ToText();
					if(text == NULL){
						continue;
					}
					std::string hp_string = text->Value();
					hp = atoi(hp_string.c_str());

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (hp < 0) {
						city->output << "A hospital can not have a negative amount of hitpoints! Hitpoints read: " << hp << std::endl;
						continue;
					}
					else if (isalpha(hp) || typeid(hp) != typeid(int)) {
						city->output << "Hitpoints must be of type int! Hitpoints read: " << hp << std::endl;
						continue;
					}
				}
			}
			Hospital newHospital(x_building, y_building, x_entrance, y_entrance, hp, name, width, length);
			city->getHospitalsList()->push_back(newHospital);
			std::cout << "hospital 1" << std::endl;
		}
		else if (objectName == "PolitieBureau") {
			std::cout << "pol 1" << std::endl;
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
					x_building = atoi(field->Attribute("X"));
					y_building = atoi(field->Attribute("Y"));

					if (!validCoordCheck(x_building,y_building)) {
						continue;
					}

					maxX = compareCoord(maxX, x_building);
					maxY = compareCoord(maxY, y_building);
				}
				else if (fieldName == "Grootte") {
					width = atoi(field->Attribute("Breedtje"));
					length = atoi(field->Attribute("Hoogte"));

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (width < 0 || length < 0) {
						city->output << "A Store can't have negative dimensions! Dimensions read: " << width << " " << length << std::endl;
						continue;
					}
					else if (isalpha(width) || typeid(width) != typeid(int) || isalpha(length) || typeid(length) != typeid(int)) {
						city->output << "Dimensions must be of type int! Dimensions read: " << width << " " << length << std::endl;
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
					TiXmlText* text = field->FirstChild()->ToText();
					if(text == NULL){
						continue;
					}
					std::string hp_string = text->Value();
					hp = atoi(hp_string.c_str());

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (hp < 0) {
						city->output << "A house can not have a negative amount of hitpoints! Hitpoints read: " << hp << std::endl;
						continue;
					}
					else if (isalpha(hp) || typeid(hp) != typeid(int)) {
						city->output << "Hitpoints must be of type int! Hitpoints read: " << hp << std::endl;
						continue;
					}
				}
			}
			PoliceStation newPolStation(x_building, y_building, x_entrance, y_entrance, hp, name, width, length);
			city->getPoliStatsList()->push_back(newPolStation);
			std::cout << "pol 1" << std::endl;
		}
		else if (objectName == "Politiewagen") {
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
					city->output << "Label " << fieldName << " is not a valid field. Truck" << std::endl;
					continue;
				}
			}
			//PoliceCar policeCar(0, 0, name, base);
			//city->getPoliceCarsList()->push_back(truck);
		}
		else if (objectName == "Politiewagen") {
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
					city->output << "Label " << fieldName << " is not a valid field. Truck" << std::endl;
					continue;
				}
			}
			//Ambulance policeCar(0, 0, name, base);
			//city->getAmbulancesList()->push_back(truck);
		}
		else {
			city->output << objectName << " is not a valid object." << std::endl;
			maxValues = std::pair<int, int>(-3, -3);
			return;
		}
	}
	maxValues = std::pair<int, int>(maxX, maxY);
}


bool XmlParser::validCoordCheck(int x, int y) {
	/*
	 * Check to see if the input is valid: not negative and of type int.
	 */

	if (x < 0 || y < 0) {
		city->output << "A coordinate can not be negative! Coordinate read: (" << x << "," << y << ")" << std::endl;
		return false;
	}
	else if (isalpha(x) || isalpha(y) || typeid(x) != typeid(int) || typeid(y) != typeid(int)) {
		city->output << "A coordinate must be of type int! Coordinate read: (" << x << "," << y << ")" << std::endl;
		return false;
	}
	else {
		return true;
	}
}

int XmlParser::compareCoord(int curMax, int testVal) {
	if (testVal > curMax) {
		return testVal;
	}
	else {
		return curMax;
	}
}

std::pair<int, int> XmlParser::getMaxValues() {
	return maxValues;
}
