#include <iostream>
#include "tinyxml.h"
#include <vector>
#include <cstdlib>
#include <assert.h>


#define TIXML_USE_STL

TiXmlDocument doc;
if(!doc.LoadFile("FILENAME"))
{
	cerr << doc.ErrorDesc() << endl;
	return 0;
}

TiXmlElement* virtualCity = doc.FirstChildElement();

if(virtualCity == NULL)
{
	cerr << "Failed to load file: No root element." << endl;
	doc.Clear();
	return 0;
}

/*
 * NOT ERROR PROOF YET.
 */

/*
 * Checks when defined or at the end ?
 */

for(TiXmlElement* object = virtualCity->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
	string objectName = object->Value();
	if (objectName == "House") {
		for (TiXmlElement* field = object->FirstChildElement(; field != NULL; field = field->NextSiblingElement())) {
			std::string fieldName = field->Value();
			if(fieldName == "Locatie") {
				const int x = field->Attribute("X");
				const int y = field->Attribute("Y");
			}
			else if(fieldName == "Brandbaarheid") {
				TiXmlText* text = field->FirstChild()->ToText();
				if(text == NULL){
					continue;
				}
				int hp = atoi(text.c_str());
			}
			else {
				std::cout << "Label " << fieldName << " is not a valid field." << std:endl;
				continue;
			}
			/*
			 *  Check + construct house
			 */
		}
	}
	else if (objectName == "Straat") {
		for (TiXmlElement* field = object->FirstChildElement(; field != NULL; field = field->NextSiblingElement())) {
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
				std::cout << "Label " << fieldName << " is not a valid field." << std:endl;
				continue;
			}
			/*
			 *  Check + construct street
			 */
		}
	}
	else if (objectName == "Brandweerwagen") {
		for (TiXmlElement* field = object->FirstChildElement(; field != NULL; field = field->NextSiblingElement())) {
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
				std::cout << "Label " << fieldName << " is not a valid field." << std:endl;
				continue;
			}
			/*
			 * Check + construct Firetruck
			 */
		}
	}
	else if(objectName == "Brandweerkazerne") {
		for (TiXmlElement* field = object->FirstChildElement(; field != NULL; field = field->NextSiblingElement())) {
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
				std::cout << "Label " << fieldName << " is not a valid field." << std:endl;
				continue;

			}
			/*
			 *  Check + construct Fire_department
			 */
		}
	}
	else {
		std::cout << object << " is not a valid object." << std:endl;
	}
}

