//=======================================================================================
// Name        : Matrix.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Matrix in C++, Ansi-style
//=======================================================================================

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Matrix.h"

Matrix::Matrix(): rows(10), columns(5){
	for(int i = 0; i < rows; i++){
		std::vector<CityObjects*> colum;
		for (int j = 0; j < columns; j++){
			colum.push_back(NULL);
		}
		matrix.push_back(colum);
	}

	_initCheck = this;
	ENSURE(properlyInitialized(), "Object 'Matrix' was not properly initialized.");
}

Matrix::Matrix(int r, int c): rows(r), columns(c) {
	for(int i = 0; i < rows; i++){
		std::vector<CityObjects*> colum;
		for (int j = 0; j < columns; j++){
			colum.push_back(NULL);
		}
		matrix.push_back(colum);
	}
	_initCheck = this;
	ENSURE(properlyInitialized(), "Object 'Matrix' was not properly initialized.");
}

Matrix::~Matrix()
{
}

int Matrix::getTotalLength(){
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getTotalLength().");

	if (matrix.size() == 0){
		return 0;
	}
	else {
		return matrix.size()*matrix[0].size();
	}
}

void Matrix::addHouses(std::list<House>& list) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addHouses().");

	std::list<House>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getLocation().getX();
		int y_start = it->getLocation().getY();
		int x_end = x_start + (it->getWidth()-1);
		int y_end = y_start - (it->getLength()-1);

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j >= y_end; j--){
				CityObjects* pointer = &(*it);
				addObject(i, j, pointer);
			}
		}
	}
}

void Matrix::addFiredeps(std::list<Fire_Department>& list) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addFiredeps().");

	std::list<Fire_Department>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getLocation().getX();
		int y_start = it->getLocation().getY();
		int x_end = x_start + (it->getWidth()-1);
		int y_end = y_start - (it->getLength()-1);

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j >= y_end; j--){
				CityObjects* pointer = &(*it);
				addObject(i, j, pointer);
			}
		}
	}
}

void Matrix::addStores(std::list<Store>& list) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addStores().");

	std::list<Store>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getLocation().getX();
		int y_start = it->getLocation().getY();
		int x_end = x_start + (it->getWidth()-1);
		int y_end = y_start - (it->getLength()-1);

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j >= y_end; j--){
				CityObjects* pointer = &(*it);
				addObject(i, j, pointer);
			}
		}
	}
}

void Matrix::addHospitals(std::list<Hospital>& list) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addHospitals().");

	std::list<Hospital>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getLocation().getX();
		int y_start = it->getLocation().getY();
		int x_end = x_start + (it->getWidth()-1);
		int y_end = y_start - (it->getLength()-1);

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j >= y_end; j--){
				CityObjects* pointer = &(*it);
				addObject(i, j, pointer);
			}
		}
	}
}

void Matrix::addPolStations(std::list<PoliceStation>& list) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addPolStations().");

	std::list<PoliceStation>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getLocation().getX();
		int y_start = it->getLocation().getY();
		int x_end = x_start + (it->getWidth()-1);
		int y_end = y_start - (it->getLength()-1);

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j >= y_end; j--){
				CityObjects* pointer = &(*it);
				addObject(i, j, pointer);
			}
		}
	}
}

std::list<Crossroad> Matrix::addStreets(std::list<Street>& list) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addStreets().");

	std::list<Street>::iterator it;
	std::list<Crossroad> crossroads;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getStart().getX();
		int y_start = it->getStart().getY();
		int x_end = it->getEnd().getX();
		int y_end = it->getEnd().getY();

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j <= y_end; j++){
				if (matrix[rows-1-j][i] != NULL){
					std::string name = dynamic_cast<Street*>(matrix[rows-1-j][i])->getName();
					std::string name2 = name;
					name += "-" + it->getName();
					Crossroad c(i, j, name, name2, it->getName());
					crossroads.push_back(c);
				}
				CityObjects* pointer = &(*it);
				addObject(i, j, pointer);
			}
		}
	}
	return crossroads;
}

void Matrix::addCrossroads(std::list<Crossroad>& list) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addCrossroads().");

	std::list<Crossroad>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x = it->getLocation().getX();
		int y = it->getLocation().getY();

		CityObjects* pointer = &(*it);
		addObject(x, y, pointer);
	}
}

void Matrix::addObject(int x, int y, CityObjects*& object){
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addObject().");

	matrix[rows-1-y][x] = object;

	ENSURE(getObject(x, y) == object, "A problem occured when adding 'CityObjects' to the Matrix");
}

CityObjects* Matrix::getObject(int x, int y) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getObject().");
	REQUIRE(x >= 0 && x < getColumns() && y >= 0 && y < getRows(), "Parameters x and/or y are wrong!");

	return matrix[rows-1-y][x];
}

bool Matrix::properlyInitialized(int x, int y){
	return matrix[rows-1-y][x]->init();
}

std::ostream& operator <<(std::ostream& s, Matrix& m){
	REQUIRE(m.properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addHouses().");

	std::string output;
	output = "\nMAP: \n";
	output = output + "====\n\n";
	for(int i = 0; i < m.rows; i++){
		output = output + intToString(m.rows-1-i) + "\t[\t";
		for(int j = 0; j < m.columns; j++){
			if(m.matrix[i][j] == NULL){
				output = output + "?\t";
			}
			else if(m.matrix[i][j]->getType() == house){
				output = output + "H\t";
			}
			else if(m.matrix[i][j]->getType() == department){
				output = output + "D\t";
			}
			else if(m.matrix[i][j]->getType() == street){
				output = output + " \t";
			}
			else if(m.matrix[i][j]->getType() == crossroad){
				output = output + " \t";
			}
			else if(m.matrix[i][j]->getType() == store){
				output = output + "S\t";
			}
			else if(m.matrix[i][j]->getType() == policeStation){
				output = output + "P\t";
			}
			else if(m.matrix[i][j]->getType() == hospital){
				output = output + "+\t";
			}
			else{
				output = output + "?\t";
			}
		}
		output = output + "]\n";
	}
	output = output + "\n\t\t";
	for (int i = 0; i < m.columns; i++){
		if (i >= 9){
			output = output + intToString(i) + "\t";

		}
		else {
			output = output + intToString(i) + " \t";
		}
	}
	output = output + "\n\n\t\tH = HOUSE\t D = FIRE DEPARTMENT\t S = STORE\n";
	output = output + "\t\t+ = HOSPITAL\t P = POLICE DEPARTMENT\t ? = UNKNOWN\n";

	s << output << std::endl;

	return s;
}

void Matrix::printMatrix(OutputObject oo) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling printMatrix().");

	if (!oo.getHTML()) {
		std::string output;
		output = "\nMAP: \n";
		output = output + "====\n\n";
		for(int i = 0; i < rows; i++){
			output = output + intToString(rows-1-i) + "\t[\t";
			for(int j = 0; j < columns; j++){
				if(matrix[i][j] == NULL){
					output = output + "?\t";
				}
				else if(matrix[i][j]->getType() == house){
					output = output + "H\t";
				}
				else if(matrix[i][j]->getType() == department){
					output = output + "D\t";
				}
				else if(matrix[i][j]->getType() == street){
					output = output + " \t";
				}
				else if(matrix[i][j]->getType() == crossroad){
					output = output + " \t";
				}
				else if(matrix[i][j]->getType() == store){
					output = output + "S\t";
				}
				else if(matrix[i][j]->getType() == policeStation){
					output = output + "P\t";
				}
				else if(matrix[i][j]->getType() == hospital){
					output = output + "+\t";
				}
				else{
					output = output + "?\t";
				}
			}
			output = output + "]\n";
		}
		output = output + "\n\t\t";
		for (int i = 0; i < columns; i++){
			if (i >= 9){
				output = output + intToString(i) + "  ";

			}
			else {
				output = output + intToString(i) + " \t";
			}
		}
		output = output + "\n\n\t\tH = HOUSE\t D = FIRE DEPARTMENT\t S = STORE\n";
		output = output + "\t\t+ = HOSPITAL\t P = POLICE DEPARTMENT\t ? = UNKNOWN\n";

		oo.print(output);
	}
	else {
		std::ostream& s = oo.getOutput();
		s << "<table border = \"3\">";
		s << "</br>MAP: </br>";
		s << "====</br></br>";
		for(int i = 0; i < rows; i++){
			s << "<tr>";
			s << "<td style = \"background-color: #fde5c3\">" << rows-1-i << "</td>";//"&nbsp;&nbsp;&nbsp;&nbsp;[";
			for(int j = 0; j < columns; j++){
				if(matrix[i][j] == NULL){
					s << "<td>" << "?" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == house){
					s << "<td style = \"background-color: #6dc066\">" << "H" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == department){
					s << "<td style = \"background-color: #e00707\">" << "D" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == street){
					s << "<td style = \"background-color: #b2b2b2\">" << " " << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == crossroad){
					s << "<td style = \"background-color: #b2b2b2\">" << " " << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == store){
					s << "<td style = \"background-color: #ffc726\">" << "S" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == policeStation){
					s << "<td style = \"background-color: #33338b\">" << "P" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == hospital){
					s << "<td style = \"background-color: #ffffff\">" << "+" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else{
					s << "<td>" << "?" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
			}
			s << "</tr>";
			//s << "]</br>";
		}
		//s << "</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
		s << "<tr>";
		s << "<td style = \"background-color: #fde5c3\">" << " " << "</td>";
		for (int i = 0; i < columns; i++){
			s << "<td style = \"background-color: #fde5c3\">" << i << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
		}
		s << "</tr>";
		s << "</table>";
		s << "</br></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;H = HOUSE&nbsp;&nbsp;&nbsp;&nbsp; D = FIRE DEPARTMENT&nbsp;&nbsp;&nbsp;&nbsp; S = STORE</br>";
		s << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+ = HOSPITAL&nbsp;&nbsp;&nbsp;&nbsp; P = POLICE DEPARTMENT&nbsp;&nbsp;&nbsp;&nbsp; ? = UNKNOWN</br></br>";
	}
}

void Matrix::printVehicles(OutputObject oo) {
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling printMatrix().");

	if (!oo.getHTML()) {
		std::string output;
		output = "\nMAP: \n";
		output = output + "====\n\n";
		for(int i = 0; i < rows; i++){
			output = output + intToString(rows-1-i) + "\t[\t";
			for(int j = 0; j < columns; j++){
				if(matrix[i][j] == NULL){
					output = output + "?\t";
				}
				else if(matrix[i][j]->getType() == house){
					output = output + "H\t";
				}
				else if(matrix[i][j]->getType() == department){
					output = output + "D\t";
				}
				else if(matrix[i][j]->getType() == street){
					output = output + " \t";
				}
				else if(matrix[i][j]->getType() == crossroad){
					output = output + " \t";
				}
				else if(matrix[i][j]->getType() == store){
					output = output + "S\t";
				}
				else if(matrix[i][j]->getType() == policeStation){
					output = output + "P\t";
				}
				else if(matrix[i][j]->getType() == hospital){
					output = output + "+\t";
				}
				else{
					output = output + "?\t";
				}
			}
			output = output + "]\n";
		}
		output = output + "\n\t\t";
		for (int i = 0; i < columns; i++){
			if (i >= 9){
				output = output + intToString(i) + "  ";

			}
			else {
				output = output + intToString(i) + " \t";
			}
		}
		output = output + "\n\n\t\tH = HOUSE\t D = FIRE DEPARTMENT\t S = STORE\n";
		output = output + "\t\t+ = HOSPITAL\t P = POLICE DEPARTMENT\t ? = UNKNOWN\n";

		oo.print(output);
	}
	else {
		std::ostream& s = oo.getOutput();
		s << "<table border = \"3\">";
		s << "</br>MAP: </br>";
		s << "====</br></br>";
		for(int i = 0; i < rows; i++){
			s << "<tr>";
			s << "<td style = \"background-color: #fde5c3\">" << rows-1-i << "</td>";//"&nbsp;&nbsp;&nbsp;&nbsp;[";
			for(int j = 0; j < columns; j++){
				if(matrix[i][j] == NULL){
					s << "<td>" << "?" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == house){
					s << "<td style = \"background-color: #6dc066\">" << "H" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == department){
					s << "<td style = \"background-color: #e00707\">" << "D" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == street){
					s << "<td style = \"background-color: #b2b2b2\">" << " " << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == crossroad){
					s << "<td style = \"background-color: #b2b2b2\">" << " " << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == store){
					s << "<td style = \"background-color: #ffc726\">" << "S" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == policeStation){
					s << "<td style = \"background-color: #33338b\">" << "P" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else if(matrix[i][j]->getType() == hospital){
					s << "<td style = \"background-color: #ff009d\">" << "+" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				else{
					s << "<td>" << "?" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
				}
			}
			s << "</tr>";
			//s << "]</br>";
		}
		//s << "</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
		s << "<tr>";
		s << "<td style = \"background-color: #fde5c3\">" << " " << "</td>";
		for (int i = 0; i < columns; i++){
			s << "<td style = \"background-color: #fde5c3\">" << i << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
		}
		s << "</tr>";
		s << "</table>";
		s << "</br></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;H = HOUSE&nbsp;&nbsp;&nbsp;&nbsp; D = FIRE DEPARTMENT&nbsp;&nbsp;&nbsp;&nbsp; S = STORE</br>";
		s << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+ = HOSPITAL&nbsp;&nbsp;&nbsp;&nbsp; P = POLICE DEPARTMENT&nbsp;&nbsp;&nbsp;&nbsp; ? = UNKNOWN</br>";
	}
}


bool Matrix::properlyInitialized() {
	return _initCheck == this;
}

int Matrix::getRows(){
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getRows().");

	return rows;
}

int Matrix::getColumns(){
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getColumns().");

	return columns;
}

Matrix::Matrix(const Matrix& c){
	rows = c.rows;
	columns = c.columns;
	matrix = c.matrix;

	_initCheck = this;
}

Matrix& Matrix::operator = (const Matrix& c){
	rows = c.rows;
	columns = c.columns;
	matrix = c.matrix;

	_initCheck = this;

	return *this;
}

int Matrix::calculateBlocks() {
	int blockAmount = rows * columns;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(matrix[i][j]->getType() == house){
				blockAmount++;
			}
			else if(matrix[i][j]->getType() == department){
				blockAmount++;
			}
			else if(matrix[i][j]->getType() == store){
				blockAmount++;
			}
			else if(matrix[i][j]->getType() == policeStation){
				blockAmount++;
			}
			else if(matrix[i][j]->getType() == hospital){
				blockAmount++;
			}
		}
	}
	return blockAmount;
}

/*void Matrix::generateGFX() {
	std::cout << "YES!" << std::endl;
	std::ofstream gfx;
	gfx.open("GFX.ini");

	// General info
	gfx << "[General]" << std::endl;
	gfx << "size = 1024" << std::endl;
	gfx << "backgroundcolor = (0, 0, 0)" << std::endl;
	gfx << "type = \"LightedZBuffering\"" << std::endl;
	gfx << "nrLights = 1" << std::endl;
	gfx << "eye = (100, 25, 75)" << std::endl;
	int blockAmount = calculateBlocks();
	gfx << "nrFigures = " << blockAmount << std::endl << std::endl;

	gfx << "[Light0]" << std::endl;
	gfx << "infinity = FALSE" << std::endl;
	gfx << "location = (8, 9, 10)" << std::endl;
	gfx << "ambientLight = (1, 1, 1)" << std::endl;
	gfx << "diffuseLight = (1, 1, 1)" << std::endl << std::endl;
	gfx << "specularLight = (1, 1, 1)" << std::endl << std::endl;

	// draw floor
	std::stringstream ss;
	int counter = 0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			// Figure number
			ss << "[Figure" << counter << "]";
			std::string figureNr = ss.str();
			ss.str("");

			// Coordinates
			int x_coord = i * 2;
			int y_coord = j * 2;

			gfx << figureNr << std::endl;
			gfx << "type = \"Cube\"" << std::endl;
			gfx << "scale = 1" << std::endl;
			gfx << "rotateX = 0" << std::endl;
			gfx << "rotateY = 0" << std::endl;
			gfx << "rotateZ = 0" << std::endl;
			gfx << "center = (" << x_coord << "," << y_coord << ", -2)" << std::endl;
			gfx << "ambientReflection = (0.5, 0.5, 0.5)"  << std::endl << std::endl;
			gfx << "diffuseReflection = (0.5, 0.5, 0.5)"  << std::endl << std::endl;
			gfx << "specularLight = (1, 1, 1)" << std::endl << std::endl;
			gfx << "reflectionCoefficient = 20" << std::endl << std::endl;
			counter++;
		}
	}

	// draw buildings
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			bool valid = false;
			std::string ambientColor;
			std::string diffuseColor;
			if(matrix[i][j]->getType() == house){
				valid = true;
				ambientColor = "ambientReflection = (0, 1, 0)";
				diffuseColor = "diffuseColor = (0, 1, 0)";
			}
			else if(matrix[i][j]->getType() == department){
				valid = true;
				ambientColor = "ambientReflection = (1, 0, 0)";
				diffuseColor = "diffuseColor = (1, 0, 0)";

			}
			else if(matrix[i][j]->getType() == store){
				valid = true;
				ambientColor = "ambientReflection = (1, 1, 0)";
				diffuseColor = "diffuseColor = (1, 1, 0)";
			}
			else if(matrix[i][j]->getType() == policeStation){
				valid = true;
				ambientColor = "ambientReflection = (0, 0, 1)";
				diffuseColor = "diffuseColor = (0, 0, 1)";
			}
			else if(matrix[i][j]->getType() == hospital){
				valid = true;
				ambientColor = "ambientReflection = (1, 1, 1)";
				diffuseColor = "diffuseColor = (1, 1, 1)";
			}
			if (valid) {
				// Figure number
				ss << "[Figure" << counter << "]";
				std::string figureNr = ss.str();
				ss.str("");

				// Coordinates
				int x_coord = i * 2;
				int y_coord = j * 2;

				gfx << figureNr << std::endl;
				gfx << "type = \"Cube\"" << std::endl;
				gfx << "scale = 1" << std::endl;
				gfx << "rotateX = 0" << std::endl;
				gfx << "rotateY = 0" << std::endl;
				gfx << "rotateZ = 0" << std::endl;
				gfx << "center = (" << x_coord << "," << y_coord << ", 0)" << std::endl;
				gfx << ambientColor  << std::endl;
				gfx << diffuseColor  << std::endl << std::endl;
				gfx << "specularLight = (1, 1, 1)" << std::endl << std::endl;
				gfx << "reflectionCoefficient = 20" << std::endl << std::endl;
				counter++;
			}
		}
	}
	gfx.close();
}*/

void Matrix::generateGFX() {
	std::cout << "YES!" << std::endl;
	std::ofstream gfx;
	gfx.open("GFX.ini");

	// General info
	gfx << "[General]" << std::endl;
	gfx << "size = 1024" << std::endl;
	gfx << "backgroundcolor = (0, 0, 0)" << std::endl;
	gfx << "type = \"ZBuffering\"" << std::endl;
	gfx << "eye = (100, 25, 75)" << std::endl;
	int blockAmount = calculateBlocks();
	gfx << "nrFigures = " << blockAmount << std::endl << std::endl;

	// draw floor
	std::stringstream ss;
	int counter = 0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			// Figure number
			ss << "[Figure" << counter << "]";
			std::string figureNr = ss.str();
			ss.str("");

			// Coordinates
			int x_coord = i * 2;
			int y_coord = j * 2;

			gfx << figureNr << std::endl;
			gfx << "type = \"Cube\"" << std::endl;
			gfx << "scale = 1" << std::endl;
			gfx << "rotateX = 0" << std::endl;
			gfx << "rotateY = 0" << std::endl;
			gfx << "rotateZ = 0" << std::endl;
			gfx << "center = (" << x_coord << "," << y_coord << ", -2)" << std::endl;
			gfx << "color = (0.5, 0.5, 0.5)"  << std::endl << std::endl;
			counter++;
		}
	}

	// draw buildings
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			bool valid = false;
			std::string buildingColor;
			if(matrix[i][j]->getType() == house){
				valid = true;
				buildingColor = "color = (0, 1, 0)";
			}
			else if(matrix[i][j]->getType() == department){
				valid = true;
				buildingColor = "color = (1, 0, 0)";
			}
			else if(matrix[i][j]->getType() == store){
				valid = true;
				buildingColor = "color = (1, 1, 0)";
			}
			else if(matrix[i][j]->getType() == policeStation){
				valid = true;
				buildingColor = "color = (0, 0, 1)";
			}
			else if(matrix[i][j]->getType() == hospital){
				valid = true;
				buildingColor = "color = (1, 1, 1)";
			}
			if (valid) {
				// Figure number
				ss << "[Figure" << counter << "]";
				std::string figureNr = ss.str();
				ss.str("");

				// Coordinates
				int x_coord = i * 2;
				int y_coord = j * 2;

				gfx << figureNr << std::endl;
				gfx << "type = \"Cube\"" << std::endl;
				gfx << "scale = 1" << std::endl;
				gfx << "rotateX = 0" << std::endl;
				gfx << "rotateY = 0" << std::endl;
				gfx << "rotateZ = 0" << std::endl;
				gfx << "center = (" << x_coord << "," << y_coord << ", 0)" << std::endl;
				gfx << buildingColor  << std::endl << std::endl;
				counter++;
			}
		}
	}

	gfx.close();
}



void Matrix::printVehicles(OutputObject oo, std::vector<Vehicles*> vehicles) {
        REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling printMatrix().");

        std::vector<Vehicles*>::iterator itv;

        if (!oo.getHTML()) {
                std::string output;
                output = "\nMAP: \n";
                output = output + "====\n\n";
                for(int i = 0; i < rows; i++){
                        output = output + intToString(rows-1-i) + "\t[\t";
                        for(int j = 0; j < columns; j++){
                                if(matrix[i][j] == NULL){
                                        output = output + "?\t";
                                }
                                else if(matrix[i][j]->getType() == house){
                                        output = output + "H\t";
                                }
                                else if(matrix[i][j]->getType() == department){
                                        output = output + "D\t";
                                }
                                else if(matrix[i][j]->getType() == street || matrix[i][j]->getType() == crossroad){
                                        std::string sign = "";
                                        for (itv = vehicles.begin(); itv != vehicles.end(); itv++) {
                                                Coordinate location = (*itv)->getCoord();
                                                if ((location.getX() == j) && (location.getY() == rows-1-i) && (!(*itv)->getIsHome())) {
                                                        Coordinate location = (*itv)->getCoord();
                                                        sign += *((*itv)->getName().begin());
                                                }
                                        }
                                        if (sign != "") {
                                                output = output + sign + "\t";
                                        }
                                        else {
                                                output = output + " \t";
                                        }
                                }
                                else if(matrix[i][j]->getType() == store){
                                        output = output + "S\t";
                                }
                                else if(matrix[i][j]->getType() == policeStation){
                                        output = output + "P\t";
                                }
                                else if(matrix[i][j]->getType() == hospital){
                                        output = output + "+\t";
                                }
                                else{
                                        output = output + "?\t";
                                }
                        }
                        output = output + "]\n";
                }
                output = output + "\n\t\t";
                for (int i = 0; i < columns; i++){
                        if (i >= 9){
                                output = output + intToString(i) + "\t";
                        }
                        else {
                                output = output + intToString(i) + " \t";
                        }
                }
                output = output + "\n\n\t\tH = HOUSE\t D = FIRE DEPARTMENT\t S = STORE\n";
                output = output + "\t\t+ = HOSPITAL\t P = POLICE DEPARTMENT\t ? = UNKNOWN\n";

                oo.print(output);
        }
        else {
                std::ostream& s = oo.getOutput();
                s << "<table border = \"3\">";
                s << "</br>MAP: </br>";
                s << "====</br></br>";
                for(int i = 0; i < rows; i++){
                        s << "<tr>";
                        s << "<td style = \"background-color: #fde5c3\">" << rows-1-i << "</td>";//"&nbsp;&nbsp;&nbsp;&nbsp;[";
                        for(int j = 0; j < columns; j++){
                                if(matrix[i][j] == NULL){
                                        s << "<td>" << "?" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                                }
                                else if(matrix[i][j]->getType() == house){
                                        s << "<td style = \"background-color: #6dc066\">" << "H" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                                }
                                else if(matrix[i][j]->getType() == department){
                                        s << "<td style = \"background-color: #e00707\">" << "D" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                                }
                                else if(matrix[i][j]->getType() == street || matrix[i][j]->getType() == crossroad){
                                        std::string sign = "";
                                        for (itv = vehicles.begin(); itv != vehicles.end(); itv++) {
                                                Coordinate location = (*itv)->getCoord();
                                                if ((location.getX() == j) && (location.getY() == rows-1-i) && (!(*itv)->getIsHome())) {
                                                        Coordinate location = (*itv)->getCoord();
                                                        sign += *((*itv)->getName().begin());
                                                }
                                        }
                                        if (sign != "") {
                                                s << "<td style = \"background-color: #b2b2b2\">" << sign << "</td>";
                                        }
                                        else {
                                                s << "<td style = \"background-color: #b2b2b2\">" << " " << "</td>";
                                        }
                                }
                                else if(matrix[i][j]->getType() == store){
                                        s << "<td style = \"background-color: #ffc726\">" << "S" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                                }
                                else if(matrix[i][j]->getType() == policeStation){
                                        s << "<td style = \"background-color: #33338b\">" << "P" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                                }
                                else if(matrix[i][j]->getType() == hospital){
                                        s << "<td style = \"background-color: #ff009d\">" << "+" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                                }
                                else{
                                        s << "<td>" << "?" << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                                }
                        }
                        s << "</tr>";
                        //s << "]</br>";
                }
                //s << "</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
                s << "<tr>";
                s << "<td style = \"background-color: #fde5c3\">" << " " << "</td>";
                for (int i = 0; i < columns; i++){
                        s << "<td style = \"background-color: #fde5c3\">" << i << "</td>";//&nbsp;&nbsp;&nbsp;&nbsp;";
                }
                s << "</tr>";
                s << "</table>";
                s << "</br></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;H = HOUSE&nbsp;&nbsp;&nbsp;&nbsp; D = FIRE DEPARTMENT&nbsp;&nbsp;&nbsp;&nbsp; S = STORE</br>";
                s << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+ = HOSPITAL&nbsp;&nbsp;&nbsp;&nbsp; P = POLICE DEPARTMENT&nbsp;&nbsp;&nbsp;&nbsp; ? = UNKNOWN</br>";
        }
}


