/*
 * Matrix.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

#include <vector>

#include "Matrix.h"

Matrix::Matrix(): rows(15), columns(21) {
	for(int i = 0; i < columns; i++){
		std::vector<CityObjects*> colum;
		for (int j = 0; j < rows; j++){
			colum.push_back(NULL);
		}
		matrix.push_back(colum);
	}

	Street s(0, 0, 0, 0, "Leo Metsstraat");

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			matrix[i][j] = &s;
		}
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

std::ostream& operator <<(std::ostream& stream, Matrix& o){
	for (int i = 0; i < o.rows; i++){
		for (int j = 0; j < o.columns; j++){
			Street t = *(o.matrix[i][j]);
			stream << t << " ";
		}
		stream << "\n";
	}

	return stream;
}

Matrix::~Matrix()
{
}


