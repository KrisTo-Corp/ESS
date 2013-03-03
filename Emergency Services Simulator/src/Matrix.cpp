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

Matrix::Matrix(): rows(16), columns(22) {
	for(int i = 0; i < rows; i++){
		std::vector<CityObjects*> colum;
		for (int j = 0; j < columns; j++){
			colum.push_back(NULL);
		}
		matrix.push_back(colum);
	}
}

Matrix::Matrix(const int r, const int c): rows(r), columns(c) {
	for(int i = 0; i < columns; i++){
		std::vector<CityObjects*> colum;
		for (int j = 0; j < rows; j++){
			colum.push_back(NULL);
		}
		matrix.push_back(colum);
	}
}

Matrix::~Matrix()
{
}

void Matrix::addHouses(std::list<House>& list) {
	std::list<House>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getLocation().getX();
		int y_start = it->getLocation().getY();
		int x_end = x_start + (it->getWidth()-1);
		int y_end = y_start - (it->getLength()-1);

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j >= y_end; j--){
				addObject(i, j, &(*it));
			}
		}
	}
}

void Matrix::addFiredeps(std::list<Fire_Department>& list) {
	std::list<Fire_Department>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x_start = it->getLocation().getX();
		int y_start = it->getLocation().getY();
		int x_end = x_start + (it->getWidth()-1);
		int y_end = y_start - (it->getLength()-1);

		for (int i = x_start; i <= x_end; i++){
			for (int j = y_start; j >= y_end; j--){
				addObject(i, j, &(*it));
			}
		}
	}
}

std::list<Crossroad> Matrix::addStreets(std::list<Street>& list) {
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
					name += "-" + it->getName();
					Crossroad c(i, j, name);
					crossroads.push_back(c);
				}
				addObject(i, j, &(*it));
			}
		}
	}
	return crossroads;
}

void Matrix::addCrossroads(std::list<Crossroad>& list) {
	std::list<Crossroad>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		int x = it->getLocation().getX();
		int y = it->getLocation().getY();

		addObject(x, y, &(*it));
	}
}

void Matrix::addObject(int x, int y, CityObjects* object){
	matrix[rows-1-y][x] = object;
}

std::ostream& operator <<(std::ostream& s, Matrix& m){
	for(int i = 0; i < m.rows; i++){
		s << m.rows-1-i << "\t[\t";
		for(int j = 0; j < m.columns; j++){
			if(m.matrix[i][j] == NULL){
				s << "NULL\t";
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
				s << "unknown\t";
			}
		}
		s << "]\n";
	}
	s << "\n\t\t";
	for (int i = 0; i < m.columns; i++){
		s << i << "\t";
	}
	s << "\n";

	return s;
}
