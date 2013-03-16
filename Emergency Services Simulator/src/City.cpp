//=======================================================================================
// Name        : City.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : City in C++, Ansi-style
//=======================================================================================

#include "City.h"

#include <cstdlib>
#include <fstream>
#include <cmath>

City::City(const std::string filename){

	std::pair<int, int> maxCoords =	parseCity(filename);

	/*
	 * Program halts when adding objects to the matrix. Probably a segmentation fault.
	 */

	matrix = Matrix(maxCoords.second + 1, maxCoords.first +1);
	matrix.resetInit();

	for (std::list<Firetruck>::iterator it = trucks.begin(); it != trucks.end(); it++) {
		it->resetInit();
	}

	for (std::list<House>::iterator it = houses.begin(); it != houses.end(); it++) {
		it->resetInit();
	}

	for (std::list<Fire_Department>::iterator it = departments.begin(); it != departments.end(); it++) {
		it->resetInit();
	}

	for (std::list<Street>::iterator it = streets.begin(); it != streets.end(); it++) {
		it->resetInit();
	}

	link_trucks_to_bases();
	matrix.addHouses(houses);
	matrix.addFiredeps(departments);
	crossroads = matrix.addStreets(streets);
	matrix.addCrossroads(crossroads);

	for (std::list<Crossroad>::iterator it = crossroads.begin(); it != crossroads.end(); it++) {
		it->resetInit();
	}
	_initCheck = this;

	ENSURE(init(), "Object 'City' was not properly initialized.");
}

City::~City()
{
}

std::ostream& operator <<(std::ostream& s, City& city) {
	REQUIRE(city.init(), "Object 'City' was not properly initialized when calling overloaded operator '<<'");

	s << city.matrix << "\n";
	return s;
}

void City::link_trucks_to_bases() {
	std::list<Firetruck>::iterator it_t;
	std::list<Fire_Department>::iterator it_dep;
	for (it_t = trucks.begin(); it_t != trucks.end(); it_t++) {
		std::string basename = it_t->getBasename();
		for (it_dep = departments.begin(); it_dep != departments.end(); it_dep++) {
			std::string dep_name = it_dep->getName();
			if (basename == dep_name) {
				// Add truck to the fire department.
				it_dep->addTruck(&(*it_t));
				// Set values in Firetruck
				it_t->setCoord(it_dep->getEntrance());
				Fire_Department* dep_ptr = &(*it_dep);
				it_t->linkBase(dep_ptr);
			}
		}
		if (it_t->getBaseptr() == NULL){
			std::cerr << "Base doesn't exist -> Truck was not linked.\n";
		}
	}
}

bool City::init() {
	return _initCheck == this;
}

bool City::properlyInitialized(int x, int y){
	return matrix.properlyInitialized(x, y);
}

CityObjects* City::setFire(){

	bool succes = false;
	CityObjects* ptr;

	while (!succes){

		int random_x = rand()% matrix.getRows();
		int random_y = rand()% matrix.getColumns();

		ptr = matrix.getObject(random_y, random_x);

		if (ptr->getState() == normal){
			succes = true;
		}
	}

	ptr->setState(burning);

	return ptr;
}

void City::update(){
	bool finished = false;
	CityObjects* ptr;
	std::ofstream output;
	output.open("output.txt");

	ptr = setFire();
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	Coordinate cur = structptr->getLocation();
	std::string name = structptr->getName();
	output << name << " at location " << cur << " started burning." << std::endl;
	House* houseptr = dynamic_cast<House*>(structptr);
	double hp = houseptr->getHP();
	output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

	// Find an available firetruck.
	std::list<Fire_Department>::iterator it_d;
	Firetruck* rescueTruck;
	for (it_d = departments.begin(); it_d != departments.end(); it_d++) {
		rescueTruck = it_d->useTruck();
		if (rescueTruck->getBasename() != "") {
			break;
		}
	}
	// Find a road next to the burning location.
	Coordinate destination = getAdjecantStreet(cur);

	while(!finished){
		finished = true;

		for (int i = 0; i < matrix.getColumns(); i++){
			for (int j = 0; j < matrix.getRows(); j++){
				ptr = matrix.getObject(i, j);

				if (ptr->getState() == burning){
					finished = false;

					House* houseptr = dynamic_cast<House*>(ptr);

					houseptr->decreaseHP();
					double hp = houseptr->getHP();
					if (hp/floor(hp) == 1){
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						output << name << " at location " << cur << " is still burning." << std::endl;
						output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;
					}

					if (houseptr->getHP() <= 0){
						houseptr->setState(destroyed);
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						output << name << " at location " << cur << " is destroyed." << std::endl;
						output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;
					}
				}
			}
		}
		// rescueTruck to the rescue.
		Coordinate truckLoc = rescueTruck->getCoord();
		Roads* destStreet = dynamic_cast<Roads*>(matrix.getObject(destination.getX(), destination.getY()));
		Roads* truckStreet = dynamic_cast<Roads*>(matrix.getObject(truckLoc.getX(), truckLoc.getY()));

		if (truckLoc.getX() != destination.getX() || truckLoc.getY() != destination.getY()) {
			output << "Firetruck " << rescueTruck->getName() << " is on its way to " << name << " on location ";
			output << destination << ". The firetruck is at " << truckStreet->getName() << " on location " << truckLoc << std::endl << std::endl;

			// Scenario 1: rescueTruck is in the same street as destination.
			if (destStreet->getName() == truckStreet->getName()) {
				driveTruck(destination, truckLoc, rescueTruck);
			}
			// Scenario 2: truckStreet and destStreet are parallel.
			else if (checkOrientation(truckLoc) == checkOrientation(destination)) {
				// Move to the nearest crossroad.
				if ((matrix.getObject(truckLoc.getX(), truckLoc.getY()))->getType() == crossroad) {
					if (truckLoc.getY() != destination.getY()) {

					}
				}
				else {
					// Find the closest crossroad and move to it.
					Crossroad xroad = closestCrossroad(truckLoc);
					driveTruck(xroad.getLocation(), truckLoc, rescueTruck, "parallel");
				}
			}
		}
		else {
			output << "Firetruck " << rescueTruck->getName() << " has reached its destination " << name;
			output << " at location " << destination << " and has extinguished the fire." << std::endl;
			houseptr->setState(normal);
			finished = true;
		}
	}
	// Return the firetruck to its department

	output.close();
}

Coordinate City::getAdjecantStreet(Coordinate coord) {

	CityObjects* checkSide;

	// Check rightside (including boundscheck)
	if (coord.getX() + 1 <= matrix.getColumns()) {
		checkSide = matrix.getObject(coord.getX() + 1, coord.getY());
		if (checkSide->getType() == street) {
			return Coordinate(coord.getX() + 1, coord.getY());
		}
	}

	// Check leftside (including boundscheck)
	if (coord.getX() - 1 >= 0) {
		checkSide = matrix.getObject(coord.getX() - 1, coord.getY());
		if (checkSide->getType() == street) {
			return Coordinate(coord.getX() - 1, coord.getY());
		}
	}

	// Check upside (including boundscheck)
	if (coord.getY() + 1 <= matrix.getRows()) {
		checkSide = matrix.getObject(coord.getX(), coord.getY() + 1);
		if (checkSide->getType() == street) {
			return Coordinate(coord.getX(), coord.getY() + 1);
		}
	}

	// Check downside (including boundscheck)
	if (coord.getY() - 1 >= 0) {
		checkSide = matrix.getObject(coord.getX(), coord.getY() - 1);
		if (checkSide->getType() == street) {
			return Coordinate(coord.getX(), coord.getY() - 1);
		}
	}
}

std::string City::checkOrientation(Coordinate coord) {

	// CONTRACT -> coord must be of type street

	std::string result;

	// Check if the coordinate is a crossroad
	std::list<Crossroad>::iterator it;
	for (it = crossroads.begin(); it != crossroads.end(); it++) {
		Coordinate xroad = it->getLocation();
		if (xroad.getX() == coord.getX() && xroad.getY() == coord.getY()) {
			result = "crossroad";
			return result;
		}
	}

	CityObjects* checkSide;

	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;

	// Check rightside (including boundscheck)
		if (coord.getX() + 1 <= matrix.getColumns()) {
			checkSide = matrix.getObject(coord.getX() + 1, coord.getY());
			if (checkSide->getType() == street) {
				right = true;
			}
		}

		// Check leftside (including boundscheck)
		if (coord.getX() - 1 >= 0) {
			checkSide = matrix.getObject(coord.getX() - 1, coord.getY());
			if (checkSide->getType() == street) {
				left = true;
			}
		}

		// Check upside (including boundscheck)
		if (coord.getY() + 1 <= matrix.getRows()) {
			checkSide = matrix.getObject(coord.getX(), coord.getY() + 1);
			if (checkSide->getType() == street) {
				up = true;
			}
		}

		// Check downside (including boundscheck)
		if (coord.getY() - 1 >= 0) {
			checkSide = matrix.getObject(coord.getX(), coord.getY() - 1);
			if (checkSide->getType() == street) {
				down = true;
			}
		}

		if (left && right) {
			result = "horizontal";
			return result;
		}
		if (up && down) {
			result = "vertical";
			return result;
		}
}

Crossroad City::closestCrossroad(Coordinate coord) {
	std::list<Crossroad>::iterator it;

	std::pair<Crossroad, int> closest (*(crossroads.begin()), calculateDistance(crossroads.begin()->getLocation(), coord));

	for (it = crossroads.begin(); it != crossroads.end(); it++) {
		int distance = calculateDistance(it->getLocation(), coord);
		if (distance < closest.second) {
			closest.first = *it;
			closest.second = distance;
		}
	}
	return closest.first;
}

int City::calculateDistance(Coordinate c1, Coordinate c2) {
	int distance = sqrt((pow(c2.getX(), 2) - pow(c1.getX(), 2) + pow(c2.getY(), 2) - pow(c1.getY(), 2)));
	return distance;
}

void City::driveTruck(Coordinate destination, Coordinate truckLoc, Firetruck* rescueTruck, std::string dir) {
	std::string orientation = checkOrientation(destination);

	if (orientation == "horizontal") {
		if (destination.getX() < truckLoc.getX()) {
			rescueTruck->move("left");
		}
		else {
			rescueTruck->move("right");
		}
	}
	else if (orientation == "vertical") {
		if (destination.getY() < truckLoc.getY()) {
			rescueTruck->move("down");
		}
		else {
			rescueTruck->move("up");
		}
	}
	// crossroad
	else {
		if (dir == "parallel") {
			if (destination.getY() < truckLoc.getY()) {
					rescueTruck->move("down");
			}
			else {
				rescueTruck->move("up");
			}
		}
		else {
			if (destination.getX() < truckLoc.getX()) {
				rescueTruck->move("left");
			}
			else {
				rescueTruck->move("right");
			}
		}
	}
}

/*
 * TODO: Implement algorithm that makes the firetrucks drive to the fire.
 */
/*
 * Algorithm:
 * 	1. Check for an available firetruck and if there is one, get it's coordinates and streetname.
 *
 *	2. Get road next to burning location. (get streetname)
 *
 *
 * 	/*
 * 	 *
 * 	 *		2.1. Get all coordinates of roads/crossroad next to the building on fire.
 * 	 *		3.1. Determine what coordinate is the closest to the firetruck (min of all sqrt((pow(x2, 2) - pow(x1, 2)) + (pow(y2, 2) - pow(y1, 2))
 * 	 *			-> Then get the streetname.
 *
 * 	3.
 * 		SCENARIO 1:
 * 			Check if firetruck's street is the same as burning house.
 * 			1. Horizontal street:
 * 				-> Compare X values, if Xhouse < Xtruck then move left else move right.
 * 			2. Vertical street:
 * 				-> Compare Y values, if Yhouse < Ytruck then move down else move up.
 *
 * 		SCENARIO 2:
 * 			1. Check if firetruck's street is parallel with the destination street.
 * 			   (This will be done by doing a neighbour check and seeing if the street has cells
 * 				above and under OR left and right to the cell.)
 *
 * 			2. IF it was parallel:
 * 				-> Move to the nearest crossroad.
 * 					-> Compare Y values, if Yhouse < Ytruck then move down else move up.
 * 						UNTILL firetruck reaches destination street (which is a crossroad with same Y value)
 * 							-> Compare X values, if Xhouse < Xtruck then move left else move right.
 * 								UNTILL firetruck reaches destination.
 *
 * 			   ELSE:
 * 				-> 	Compare X values, if Xhouse < Xtruck then move left else move right.
 * 					UNTILL firetruck reaches destination street (which is a crossroad with same X value)
 * 						-> Compare Y values, if Yhouse < Ytruck then move down else move up.
 * 							UNTILL firetruck reaches destination.
 *
 *
 */
