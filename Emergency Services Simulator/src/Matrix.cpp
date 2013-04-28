//=======================================================================================
// Name        : Matrix.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Matrix in C++, Ansi-style
//=======================================================================================

#include <vector>
#include <iostream>

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

	s << "\nMAP: \n";
	s << "====\n\n";
	for(int i = 0; i < m.rows; i++){
		s << m.rows-1-i << "\t[";
		for(int j = 0; j < m.columns; j++){
			if(m.matrix[i][j] == NULL){
				s << "?\t";
			}
			else if(m.matrix[i][j]->getType() == house){
				s << "H\t";
			}
			else if(m.matrix[i][j]->getType() == department){
				s << "D\t";
			}
			else if(m.matrix[i][j]->getType() == street){
				s << " \t";
			}
			else if(m.matrix[i][j]->getType() == crossroad){
				s << " \t";
			}
			else if(m.matrix[i][j]->getType() == store){
				s << "S\t";
			}
			else if(m.matrix[i][j]->getType() == policeStation){
				s << "P\t";
			}
			else if(m.matrix[i][j]->getType() == hospital){
				s << "+\t";
			}
			else{
				s << "?\t";
			}
		}
		s << "]\n";
	}
	s << "\n\t\t";
	for (int i = 0; i < m.columns; i++){
		s << i << "\t";
	}
	s << "\n\n\t\tH = HOUSE\t D = FIRE DEPARTMENT\t S = STREET\t C = CROSSROAD\t ? = UNKNOWN\n";

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

// TEST THE DEFAULT MATRIX CONSTRUCTOR
TEST_F(MatrixTest, DefaultConstructor){
	EXPECT_TRUE(matrix.properlyInitialized());
	EXPECT_EQ(10, matrix.getRows());
	EXPECT_EQ(5, matrix.getColumns());
	EXPECT_EQ(50, matrix.getTotalLength());
}

// TEST THE SPECIFIED MATRIX CONSTRUCTOR
TEST_F(MatrixTest, Constructor){
	matrix = Matrix(25, 10);
	EXPECT_TRUE(matrix.properlyInitialized());
	EXPECT_EQ(25, matrix.getRows());
	EXPECT_EQ(10, matrix.getColumns());
	EXPECT_EQ(250, matrix.getTotalLength());
}

// TEST SINGLE ADD FUNCTION FROM MATRIX
TEST_F(MatrixTest, SingleAdd){
	matrix = Matrix(2, 2);
	House house;
	Fire_Department department;
	Street street;
	Crossroad crossroad;

	CityObjects* houseptr = &house;
	CityObjects* depptr = &department;
	CityObjects* streetptr = &street;
	CityObjects* crossroadptr = &crossroad;

	EXPECT_EQ(NULL, matrix.getObject(0, 0));
	EXPECT_EQ(NULL, matrix.getObject(0, 1));
	EXPECT_EQ(NULL, matrix.getObject(1, 0));
	EXPECT_EQ(NULL, matrix.getObject(1, 1));

	matrix.addObject(0, 0, depptr);
	matrix.addObject(0, 1, streetptr);
	matrix.addObject(1, 0, crossroadptr);
	matrix.addObject(1, 1, houseptr);

	EXPECT_EQ(depptr, matrix.getObject(0, 0));
	EXPECT_EQ(streetptr, matrix.getObject(0, 1));
	EXPECT_EQ(crossroadptr, matrix.getObject(1, 0));
	EXPECT_EQ(houseptr, matrix.getObject(1, 1));
}

// TEST THE ADDHOUSES FUNCTION
TEST_F(MatrixTest, AddHouses){
	matrix = Matrix(4, 4);
	House house1(0, 1, 20, "");
	House house2(0, 3, 20, "");
	House house3(2, 1, 20, "");
	House house4(2, 3, 20, "");
	std::list<House> houses;
	houses.push_back(house1);
	houses.push_back(house2);
	houses.push_back(house3);
	houses.push_back(house4);
	std::list<House>::iterator it = houses.begin();
	House* ptr1 = &(*it);
	it++;
	House* ptr2 = &(*it);
	it++;
	House* ptr3 = &(*it);
	it++;
	House* ptr4 = &(*it);

	matrix.addHouses(houses);

	EXPECT_EQ(ptr1, matrix.getObject(0, 0));
	EXPECT_EQ(ptr1, matrix.getObject(0, 1));
	EXPECT_EQ(ptr1, matrix.getObject(1, 0));
	EXPECT_EQ(ptr1, matrix.getObject(1, 1));
	EXPECT_EQ(ptr2, matrix.getObject(0, 3));
	EXPECT_EQ(ptr2, matrix.getObject(1, 3));
	EXPECT_EQ(ptr2, matrix.getObject(0, 2));
	EXPECT_EQ(ptr2, matrix.getObject(1, 2));
	EXPECT_EQ(ptr3, matrix.getObject(2, 1));
	EXPECT_EQ(ptr3, matrix.getObject(2, 0));
	EXPECT_EQ(ptr3, matrix.getObject(3, 1));
	EXPECT_EQ(ptr3, matrix.getObject(2, 0));
	EXPECT_EQ(ptr4, matrix.getObject(2, 3));
	EXPECT_EQ(ptr4, matrix.getObject(2, 2));
	EXPECT_EQ(ptr4, matrix.getObject(3, 3));
	EXPECT_EQ(ptr4, matrix.getObject(3, 2));
}

// TEST THE ADDDEPARTMENTS FUNCTION
TEST_F(MatrixTest, AddDepartments){
	matrix = Matrix(8, 8);
	Fire_Department dep1(0, 7, 0, 0, "");
	Fire_Department dep2(0, 3, 0, 0, "");
	Fire_Department dep3(4, 7, 0, 0, "");
	Fire_Department dep4(4, 3, 0, 0, "");
	std::list<Fire_Department> deps;
	deps.push_back(dep1);
	deps.push_back(dep2);
	deps.push_back(dep3);
	deps.push_back(dep4);
	std::list<Fire_Department>::iterator it = deps.begin();
	Fire_Department* ptr1 = &(*it);
	it++;
	Fire_Department* ptr2 = &(*it);
	it++;
	Fire_Department* ptr3 = &(*it);
	it++;
	Fire_Department* ptr4 = &(*it);
	matrix.addFiredeps(deps);

	EXPECT_EQ(ptr1, matrix.getObject(0, 7));
	EXPECT_EQ(ptr1, matrix.getObject(1, 7));
	EXPECT_EQ(ptr1, matrix.getObject(2, 7));
	EXPECT_EQ(ptr1, matrix.getObject(3, 7));
	EXPECT_EQ(ptr1, matrix.getObject(0, 6));
	EXPECT_EQ(ptr1, matrix.getObject(1, 6));
	EXPECT_EQ(ptr1, matrix.getObject(2, 6));
	EXPECT_EQ(ptr1, matrix.getObject(3, 6));
	EXPECT_EQ(ptr1, matrix.getObject(0, 5));
	EXPECT_EQ(ptr1, matrix.getObject(1, 5));
	EXPECT_EQ(ptr1, matrix.getObject(2, 5));
	EXPECT_EQ(ptr1, matrix.getObject(3, 5));
	EXPECT_EQ(ptr1, matrix.getObject(0, 4));
	EXPECT_EQ(ptr1, matrix.getObject(1, 4));
	EXPECT_EQ(ptr1, matrix.getObject(2, 4));
	EXPECT_EQ(ptr1, matrix.getObject(3, 4));

	EXPECT_EQ(ptr2, matrix.getObject(0, 3));
	EXPECT_EQ(ptr2, matrix.getObject(1, 3));
	EXPECT_EQ(ptr2, matrix.getObject(2, 3));
	EXPECT_EQ(ptr2, matrix.getObject(3, 3));
	EXPECT_EQ(ptr2, matrix.getObject(0, 2));
	EXPECT_EQ(ptr2, matrix.getObject(1, 2));
	EXPECT_EQ(ptr2, matrix.getObject(2, 2));
	EXPECT_EQ(ptr2, matrix.getObject(3, 2));
	EXPECT_EQ(ptr2, matrix.getObject(0, 1));
	EXPECT_EQ(ptr2, matrix.getObject(1, 1));
	EXPECT_EQ(ptr2, matrix.getObject(2, 1));
	EXPECT_EQ(ptr2, matrix.getObject(3, 1));
	EXPECT_EQ(ptr2, matrix.getObject(0, 0));
	EXPECT_EQ(ptr2, matrix.getObject(1, 0));
	EXPECT_EQ(ptr2, matrix.getObject(2, 0));
	EXPECT_EQ(ptr2, matrix.getObject(3, 0));

	EXPECT_EQ(ptr3, matrix.getObject(4, 7));
	EXPECT_EQ(ptr3, matrix.getObject(5, 7));
	EXPECT_EQ(ptr3, matrix.getObject(6, 7));
	EXPECT_EQ(ptr3, matrix.getObject(7, 7));
	EXPECT_EQ(ptr3, matrix.getObject(4, 6));
	EXPECT_EQ(ptr3, matrix.getObject(5, 6));
	EXPECT_EQ(ptr3, matrix.getObject(6, 6));
	EXPECT_EQ(ptr3, matrix.getObject(7, 6));
	EXPECT_EQ(ptr3, matrix.getObject(4, 5));
	EXPECT_EQ(ptr3, matrix.getObject(5, 5));
	EXPECT_EQ(ptr3, matrix.getObject(6, 5));
	EXPECT_EQ(ptr3, matrix.getObject(7, 5));
	EXPECT_EQ(ptr3, matrix.getObject(4, 4));
	EXPECT_EQ(ptr3, matrix.getObject(5, 4));
	EXPECT_EQ(ptr3, matrix.getObject(6, 4));
	EXPECT_EQ(ptr3, matrix.getObject(7, 4));

	EXPECT_EQ(ptr4, matrix.getObject(4, 3));
	EXPECT_EQ(ptr4, matrix.getObject(5, 3));
	EXPECT_EQ(ptr4, matrix.getObject(6, 3));
	EXPECT_EQ(ptr4, matrix.getObject(7, 3));
	EXPECT_EQ(ptr4, matrix.getObject(4, 2));
	EXPECT_EQ(ptr4, matrix.getObject(5, 2));
	EXPECT_EQ(ptr4, matrix.getObject(6, 2));
	EXPECT_EQ(ptr4, matrix.getObject(7, 2));
	EXPECT_EQ(ptr4, matrix.getObject(4, 1));
	EXPECT_EQ(ptr4, matrix.getObject(5, 1));
	EXPECT_EQ(ptr4, matrix.getObject(6, 1));
	EXPECT_EQ(ptr4, matrix.getObject(7, 1));
	EXPECT_EQ(ptr4, matrix.getObject(4, 0));
	EXPECT_EQ(ptr4, matrix.getObject(5, 0));
	EXPECT_EQ(ptr4, matrix.getObject(6, 0));
	EXPECT_EQ(ptr4, matrix.getObject(7, 0));
}

// TEST THE ADDSTREETS FUNCTION
TEST_F(MatrixTest, AddStreets){
	matrix = Matrix(3, 4);
	Street street1(0, 0, 2, 0, "");
	Street street2(0, 1, 2, 1, "");
	Street street3(0, 2, 2, 2, "");
	Street street4(3, 0, 3, 2, "");
	std::list<Street> streets;
	streets.push_back(street1);
	streets.push_back(street2);
	streets.push_back(street3);
	streets.push_back(street4);
	std::list<Street>::iterator it = streets.begin();
	Street* ptr1 = &(*it);
	it++;
	Street* ptr2 = &(*it);
	it++;
	Street* ptr3 = &(*it);
	it++;
	Street* ptr4 = &(*it);

	matrix.addStreets(streets);

	EXPECT_EQ(ptr1, matrix.getObject(0, 0));
	EXPECT_EQ(ptr1, matrix.getObject(1, 0));
	EXPECT_EQ(ptr1, matrix.getObject(2, 0));
	EXPECT_EQ(ptr2, matrix.getObject(0, 1));
	EXPECT_EQ(ptr2, matrix.getObject(1, 1));
	EXPECT_EQ(ptr2, matrix.getObject(2, 1));
	EXPECT_EQ(ptr3, matrix.getObject(0, 2));
	EXPECT_EQ(ptr3, matrix.getObject(1, 2));
	EXPECT_EQ(ptr3, matrix.getObject(2, 2));
	EXPECT_EQ(ptr4, matrix.getObject(3, 0));
	EXPECT_EQ(ptr4, matrix.getObject(3, 1));
	EXPECT_EQ(ptr4, matrix.getObject(3, 2));
}

// TEST THE ADDCROSSROADS FUNCTION
TEST_F(MatrixTest, AddCrossroads){
	matrix = Matrix(2, 2);
	Crossroad crossroad1(0, 0, "", "", "");
	Crossroad crossroad2(0, 1, "", "", "");
	Crossroad crossroad3(1, 0, "", "", "");
	Crossroad crossroad4(1, 1, "", "", "");;
	std::list<Crossroad> crossroads;
	crossroads.push_back(crossroad1);
	crossroads.push_back(crossroad2);
	crossroads.push_back(crossroad3);
	crossroads.push_back(crossroad4);
	std::list<Crossroad>::iterator it = crossroads.begin();
	Crossroad* ptr1 = &(*it);
	it++;
	Crossroad* ptr2 = &(*it);
	it++;
	Crossroad* ptr3 = &(*it);
	it++;
	Crossroad* ptr4 = &(*it);

	matrix.addCrossroads(crossroads);

	EXPECT_EQ(ptr1, matrix.getObject(0, 0));
	EXPECT_EQ(ptr2, matrix.getObject(0, 1));
	EXPECT_EQ(ptr3, matrix.getObject(1, 0));
	EXPECT_EQ(ptr4, matrix.getObject(1, 1));
}
