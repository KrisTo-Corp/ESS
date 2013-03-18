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
	bool properlyInitialized(int, int);

	int getTotalLength();

	Matrix();
//	ENSURE(properlyInitialized(), "Object 'Matrix' was not properly initialized.");

	Matrix(int r, int c);
//	ENSURE(properlyInitialized(), "Object 'Matrix' was not properly initialized.");

	virtual ~Matrix();

	void addHouses(std::list<House>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addHouses().");

	void addFiredeps(std::list<Fire_Department>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addFiredeps().");

	void addCrossroads(std::list<Crossroad>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addCrossroads().");

	std::list<Crossroad> addStreets(std::list<Street>& list);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addStreets().");

	void addObject(int x, int y, CityObjects*& object);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addObject().");
//	ENSURE(getObject(x, y) == object, "Added object " + object + " was not added correctly.");

	CityObjects* getObject(int, int);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling getObject().");


	friend std::ostream& operator <<(std::ostream& s, Matrix& m);
//	REQUIRE(properlyInitialized(), "Object 'Matrix' was not properly initialized when calling addHouses().");

	Matrix& operator =(const Matrix&);

	void resetInit();

	int getRows();

	int getColumns();

	bool properlyInitialized();
};

#endif /* MATRIX_H_ */
