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

void City::parseCity(std::string filename) {
	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str())) {
		std::cerr << doc.ErrorDesc() << std::endl;
		exit(EXIT_FAILURE);
	}

	TiXmlElement* virtualCity = doc.FirstChildElement();

	if(virtualCity == NULL) {
		std::cerr << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		exit(EXIT_FAILURE);
	}

	/*
	 * NOT ERROR PROOF YET.
	 */

	/*
	 * Use DesignByContract.h here or when using the variables in the constructor?
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

					/*
					 * Check to see if the input is valid: not negative and of type int.
					 */
					if (x < 0 || y < 0) {
						std::cout << "A coordinate can not be negative! Coordinate read: (" << x << "," << y << ")" << std::endl;
						continue;
					}
					else if (isalpha(x) || isalpha(y) || typeid(x) != typeid(int) || typeid(y) != typeid(int)) {
						std::cout << "A coordinate must be of type int! Coordinate read: (" << x << "," << y << ")" << std::endl;
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
						std::cout << "A house can not have a negative amount of hitpoints! Hitpoints read: " << hp << std::endl;
						continue;
					}
					else if (isalpha(hp) || typeid(hp) != typeid(int)) {
						std::cout << "Hitpoints must be of type int! Hitpoints read: " << hp << std::endl;
						continue;
					}
				}
				else {
					std::cout << "Label " << fieldName << " is not a valid field. House" << std::endl;
					continue;
				}
			}
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
				}
				else if(fieldName == "Naar") {
					x_end = atoi(field->Attribute("x"));
					y_end = atoi(field->Attribute("y"));
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
					std::cout << "Label " << fieldName << " is not a valid field. Street" << std::endl;
					continue;
				}
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
					std::cout << "Label " << fieldName << " is not a valid field. Truck" << std::endl;
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
				}
				else if(fieldName == "Ingang") {
					x_entrance = atoi(field->Attribute("X"));
					y_entrance  = atoi(field->Attribute("Y"));
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
					std::cout << "Label " << fieldName << " is not a valid field. dep" << std::endl;
					continue;

				}
			}
			Fire_Department department(x_building, y_building, x_entrance, y_entrance, name);
			departments.push_back(department);
		}
		else {
			std::cout << object << " is not a valid object." << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}
