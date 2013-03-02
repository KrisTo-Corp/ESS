/*
 * Matrix.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <vector>
#include <iostream>

#include "Matrix.h"

Matrix::Matrix(): rows(21), columns(15) {
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

		for (int i = x_start; i > x_end; i++){
			for (int j = y_start; j > y_end; j++){
				std::cout << "rows = " << rows << std::endl << "columns = " << columns << std::endl;
				std::cout << "row = " << (rows - 1) -j << std::endl << "colum =" << i << std::endl << std::endl;
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

		for (int i = x_start; i > x_end; i++){
			for (int j = y_start; j > y_end; j++){
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

		for (int i = x_start; i > x_end; i++){
			for (int j = y_start; j > y_end; j++){
				if (matrix[rows - j][i] != NULL){
					std::string name = dynamic_cast<Street*>(matrix[rows-j][i])->getName();
					name += "-" + it->getName();
					Crossroad c(i, j, name);
					crossroads.push_back(c);
				}
				std::cout << "x = " << i << std::endl;
				std::cout << "y = " << j << std::endl;
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
	matrix[(rows-1)-y][x] = object;
}




std::ostream& operator <<(std::ostream& stream, Matrix& o){
	for (int i = 0; i < o.rows; i++){
		for (int j = 0; j < o.columns; j++){
			if (o.matrix[i][j]->getType() == house){
				House* ptr = dynamic_cast<House*>(o.matrix[i][j]);
				stream << ptr->getName();
			}
			else if (o.matrix[i][j]->getType() == department){
				Fire_Department* ptr = dynamic_cast<Fire_Department*>(o.matrix[i][j]);
				stream << ptr->getName();
			}
			else if (o.matrix[i][j]->getType() == street){
				Street* ptr = dynamic_cast<Street*>(o.matrix[i][j]);
				stream << ptr->getName();
			}
			else if (o.matrix[i][j]->getType() == crossroad){
				Crossroad* ptr = dynamic_cast<Crossroad*>(o.matrix[i][j]);
				stream << ptr->getName();
			}
			stream << "\t";
		}
		stream << "\n";
	}

	return stream;
}

Matrix::~Matrix()
{
}


