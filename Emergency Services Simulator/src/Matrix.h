/*
 * Matrix.h
 *
 *  Created on: Feb 28, 2013
 *      Author: tom
 */

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
	std::vector<std::vector<CityObjects*> > matrix;
	const int rows;
	const int columns;
public:
	Matrix();
	Matrix(const int, const int);
	void addHouses(std::list<House>&);
	void addFiredeps(std::list<Fire_Department>&);
	std::list<Crossroad> addStreets(std::list<Street>&);
	void addCrossroads(std::list<Crossroad>&);
	void addObject(int, int, CityObjects*);
	void printObject(int, int);


	friend std::ostream& operator <<(std::ostream&, Matrix&);
	virtual ~Matrix();
};

#endif /* MATRIX_H_ */
