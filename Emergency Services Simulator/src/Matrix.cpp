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
		s << m.rows-1-i << "\t[\t";
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
				s << "S\t";
			}
			else if(m.matrix[i][j]->getType() == crossroad){
				s << "C\t";
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

bool Matrix::properlyInitialized() {
	return _initCheck == this;
}

void Matrix::resetInit() {
	_initCheck = this;
}

int Matrix::getRows(){
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getRows().");

	return rows;
}

int Matrix::getColumns(){
	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getColumns().");

	return columns;
}

Matrix& Matrix::operator = (const Matrix& c){
	rows = c.rows;
	columns = c.columns;
	matrix = c.matrix;

	_initCheck = this;

	return *this;
}
