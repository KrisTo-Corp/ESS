#include <iostream>
#include "tinyxml.h"
#include <vector>
#include <cstdlib>
#include <assert.h>
#include <cctype>

#define TIXML_USE_STL

int main() {
	TiXmlDocument doc;
	if(!doc.LoadFile("/home/kristof/git/ESS/Emergency Services Simulator/stad.xml")) {
		std::cerr << doc.ErrorDesc() << std::endl;
		return 0;
	}

	TiXmlElement* virtualCity = doc.FirstChildElement();

	if(virtualCity == NULL) {
		std::cerr << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		return 0;
	}

	/*
	 * NOT ERROR PROOF YET.
	 */

	/*
	 * Use DesignByContract.h here or when using the variables in the constructor?
	 */

	for(TiXmlElement* object = virtualCity->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
		std::string objectName = object->Value();
		if (objectName == "House") {
			for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
				std::string fieldName = field->Value();
				if(fieldName == "Locatie") {
					const int x = field->Attribute("X");
					const int y = field->Attribute("Y");

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
					std::string hp_string = text;
					int hp = atoi(hp_string.c_str());

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
					std::cout << "Label " << fieldName << " is not a valid field." << std::endl;
					continue;
				}
				/*
				 *  Check + construct house
				 */
			}
		}
		else if (objectName == "Straat") {
			for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
				std::string fieldName = field->Value();
				if(fieldName == "Van") {
					const int x_start = field->Attribute("x");
					const int y_start = field->Attribute("y");
				}
				if(fieldName == "Naar") {
					const int x_end = field->Attribute("x");
					const int y_end = field->Attribute("y");
				}
				else if(fieldName == "Naam") {
					TiXmlText* text = field->FirstChild()->ToText();
					if(text == NULL){
						continue;
					}
					else {
						std::string name = text;
					}
				}
				else {
					std::cout << "Label " << fieldName << " is not a valid field." << std::endl;
					continue;
				}
				/*
				 *  Check + construct street
				 */
			}
		}
		else if (objectName == "Brandweerwagen") {
			for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
				TiXmlText* text = field->FirstChild()->ToText();
				if(text == NULL){
					continue;
				}
				else if (text == "Naam") {
					std::string name = text;
				}
				else if (text == "Basis") {
					std::string base = text;
				}
				else {
					std::cout << "Label " << text << " is not a valid field." << std::endl;
					continue;
				}
				/*
				 * Check + construct Firetruck
				 */
			}
		}
		else if(objectName == "Brandweerkazerne") {
			for (TiXmlElement* field = object->FirstChildElement(); field != NULL; field = field->NextSiblingElement()) {
				std::string fieldName = field->Value();
				if(fieldName == "Locatie") {
					const int x_building = field->Attribute("X");
					const int y_building = field->Attribute("Y");
				}
				if(fieldName == "Ingang") {
					const int x_entrance_ = field->Attribute("X");
					const int y_entrance  = field->Attribute("Y");
				}
				else if(fieldName == "Naam") {
					TiXmlText* text = field->FirstChild()->ToText();
					if(text == NULL){
						continue;
					}
					else {
						std::string name = text;
					}
				}
				else {
					std::cout << "Label " << fieldName << " is not a valid field." << std::endl;
					continue;

				}
				/*
				 *  Check + construct Fire_department
				 */
			}
		}
		else {
			std::cout << object << " is not a valid object." << std::endl;
		}
	}

return 0;
}
