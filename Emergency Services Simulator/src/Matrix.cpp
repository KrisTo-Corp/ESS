/*
 * Matrix.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <vector>
#include <iostream>

#include "Matrix.h"

Matrix::Matrix(): rows(2), columns(2) {
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

void Matrix::addObject(CityObjects* c, int x, int y){
	matrix[x][y] = c;
}

std::ostream& operator <<(std::ostream& stream, Matrix& o){
	for (int i = 0; i < o.rows; i++){
		for (int j = 0; j < o.columns; j++){
			if (o.matrix[i][j]->getType() == house){
				stream << *dynamic_cast<House*>(o.matrix[i][j]);
			}
			else if (o.matrix[i][j]->getType() == department){
				stream << *dynamic_cast<Fire_Department*>(o.matrix[i][j]);
			}
			else if (o.matrix[i][j]->getType() == street){
				stream << *dynamic_cast<Street*>(o.matrix[i][j]);
			}
			else if (o.matrix[i][j]->getType() == crossroad){
				stream << *dynamic_cast<Crossroad*>(o.matrix[i][j]);
			}
			stream << "\n";
		}
	}

	return stream;
}

Matrix::~Matrix()
{
}


