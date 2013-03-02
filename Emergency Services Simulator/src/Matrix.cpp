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

void addHouses(std::list<House>&) {

}


std::ostream& operator <<(std::ostream& stream, Matrix& o){
	for (int i = 0; i < o.rows; i++){
		for (int j = 0; j < o.columns; j++){
			if (o.matrix[i][j] == NULL){
				stream << " ";
			}
			else if (o.matrix[i][j]->getType() == house){
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
			else {
				stream << " ";
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


