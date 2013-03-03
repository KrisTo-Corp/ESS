//=======================================================================================
// Name        : Matrix.h
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Matrix in C++, Ansi-style
//=======================================================================================

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <ostream>
#include <list>

#include "CityObjects.h"
#include "Structures.h"
#include "Roads.h"

class Matrix {
private:
	const int rows;
	const int columns;
	std::vector<std::vector<CityObjects*> > matrix;

public:
	Matrix();
	Matrix(const int r, const int c);
	virtual ~Matrix();

	void addHouses(std::list<House>& list);
	void addFiredeps(std::list<Fire_Department>& list);
	void addCrossroads(std::list<Crossroad>& list);
	std::list<Crossroad> addStreets(std::list<Street>& list);
	void addObject(int x, int y, CityObjects* object);

	friend std::ostream& operator <<(std::ostream& s, Matrix& m);

};

#endif /* MATRIX_H_ */
