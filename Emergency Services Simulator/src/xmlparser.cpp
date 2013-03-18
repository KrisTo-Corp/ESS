#include <iostream>
#include <vector>
#include <cstdlib>
#include <assert.h>
#include <cctype>
#include <typeinfo>

#include "City.h"
#include "CityObjects.h"
#include "tinyxml.h"

#define TIXML_USE_STL

std::pair<int, int> City::parseCity(std::string filename) {
	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		output << doc.ErrorDesc() << std::endl;
		return std::pair<int, int>(-1, -1);
	}

	TiXmlElement* virtualCity = doc.FirstChildElement();

	if(virtualCity == NULL) {
		output << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		return std::pair<int, int>(-2, -2);
	}

	int maxX = 0;
	int maxY = 0;

	/*
	 * Primitive error checking in place!
	 */

	for(TiXmlElement* object = virtualCity->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
		std::string objectName = object->Value();
		if (objectName == "Huis") {
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
						output << "A house can not have a negative amount of hitpoints! Hitpoints read: " << hp << std::endl;
						continue;
					}
					else if (isalpha(hp) || typeid(hp) != typeid(int)) {
						output << "Hitpoints must be of type int! Hitpoints read: " << hp << std::endl;
						continue;
					}
				}
				else {
					output << "Label " << fieldName << " is not a valid field. House" << std::endl;
					continue;
				}
			}
			if (!validCoordCheck(x,y)) {
					continue;
			}
			// validcoordcheck here
			House house(x, y, hp, "house");
			houses.push_back(house);
		}
		else if (objectName == "Straat") {
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
					output << "Label " << fieldName << " is not a valid field. Street" << std::endl;
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
			streets.push_back(street);
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
					output << "Label " << fieldName << " is not a valid field. Truck" << std::endl;
					continue;
				}
			}
			Firetruck truck(0, 0, name, base);
			trucks.push_back(truck);
		}
		else if(objectName == "Brandweerkazerne") {
			int x_building, y_building, x_entrance, y_entrance;
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
					output << "Label " << fieldName << " is not a valid field. dep" << std::endl;
					continue;

				}
			}

			if (!validCoordCheck(x_building,y_building)) {
				continue;
			}

			if (!validCoordCheck(x_entrance,y_entrance)) {
				continue;
			}

			Fire_Department department(x_building, y_building, x_entrance, y_entrance, name);
			departments.push_back(department);
		}
		else {
			output << objectName << " is not a valid object." << std::endl;
			return std::pair<int, int>(-3, -3);
		}
	}
	std::pair<int, int> coords (maxX, maxY);
	return coords;
}

bool City::validCoordCheck(int x, int y) {
	/*
	 * Check to see if the input is valid: not negative and of type int.
	 */

	if (x < 0 || y < 0) {
		output << "A coordinate can not be negative! Coordinate read: (" << x << "," << y << ")" << std::endl;
		return false;
	}
	else if (isalpha(x) || isalpha(y) || typeid(x) != typeid(int) || typeid(y) != typeid(int)) {
		output << "A coordinate must be of type int! Coordinate read: (" << x << "," << y << ")" << std::endl;
		return false;
	}
	else {
		return true;
	}
}

int City::compareCoord(int curMax, int testVal) {
	if (testVal > curMax) {
		return testVal;
	}
	else {
		return curMax;
	}
}
