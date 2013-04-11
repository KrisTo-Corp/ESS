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
	int rows;
	int columns;
	std::vector<std::vector<CityObjects*> > matrix;

	Matrix* _initCheck;

public:

	int getTotalLength();
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getTotalLength().");

	Matrix();
//	ENSURE(properlyInitialized(), "Object 'Matrix' was not properly initialized.");

	Matrix(int r, int c);
//	ENSURE(properlyInitialized(), "Object 'Matrix' was not properly initialized.");

	void addHouses(std::list<House>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addHouses().");

	void addFiredeps(std::list<Fire_Department>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addFiredeps().");

	void addCrossroads(std::list<Crossroad>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addCrossroads().");

	void addStores(std::list<Store>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addStores().");

	std::list<Crossroad> addStreets(std::list<Street>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addStreets().");

	void addObject(int x, int y, CityObjects*& object);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addObject().");
//	ENSURE(getObject(x, y) == object, "Added object " + object + " was not added correctly.");

	CityObjects* getObject(int x, int y);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getObject().");
//	REQUIRE(x >= 0 && x < getColumns() && y >= 0 && y < getRows(), "Parameters x and/or y are wrong!");

	friend std::ostream& operator <<(std::ostream& s, Matrix& m);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addHouses().");

	int getRows();
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getRows().");

	int getColumns();
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getColumns().");

	Matrix& operator =(const Matrix&);

	Matrix(const Matrix& c);

	bool properlyInitialized();

	bool properlyInitialized(int, int);

	virtual ~Matrix();
};

#endif /* MATRIX_H_ */
