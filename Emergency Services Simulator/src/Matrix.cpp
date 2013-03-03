/*
 * Matrix.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <vector>
#include <iostream>

#include "Matrix.h"

Matrix::Matrix(): rows(22), columns(16) {
	for(int i = 0; i < columns; i++){
		std::vector<CityObjects*> colum;
		for (int j = 0; j < rows; j++){
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
				if (matrix[j][rows-1-i] != NULL){
					std::string name = dynamic_cast<Street*>(matrix[j][rows-1-i])->getName();
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
	matrix[y][rows-1-x] = object;
}

void Matrix::printObject(int x, int y){
	if(matrix[y][rows-1-x] == NULL){
		std::cout << "NULL\n";
	}
	else if(matrix[y][rows-1-x]->getType() == house){
		std::cout << "house\n";
	}
	else if(matrix[y][rows-1-x]->getType() == department){
		std::cout << "department\n";
	}
	else if(matrix[y][rows-1-x]->getType() == street){
		std::cout << "street\n";
	}
	else if(matrix[y][rows-1-x]->getType() == crossroad){
		std::cout << "crossroad\n";
	}
	else{
		std::cout << "unknown\n";
	}
}




std::ostream& operator <<(std::ostream& stream, Matrix& o){

	for(int i = 0; i < o.rows; i++){
		for(int j = 0; j < o.columns; j++){
			if(o.matrix[j][i] == NULL){
				stream << "NULL\n";
				continue;
			}
			else if(o.matrix[j][i]->getType() == house){
				stream << "house\n";
				continue;
			}
			else if(o.matrix[j][i]->getType() == department){
				stream << "department\n";
			}
			else if(o.matrix[j][i]->getType() == street){
				stream << "street\n";
			}
			else if(o.matrix[j][i]->getType() == crossroad){
				stream << "crossroad\n";
			}
			else{
				stream << "unknown\n";
				continue;
			}
		}
		stream << "\n";
	}
	return stream;
}

Matrix::~Matrix()
{
}


