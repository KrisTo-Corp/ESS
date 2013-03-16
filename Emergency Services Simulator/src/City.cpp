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
	std::cout << "entered setFire()" << std::endl;
	bool succes = false;
	CityObjects* ptr;

	while (!succes){

		int random_x = rand()% matrix.getRows();
		int random_y = rand()% matrix.getColumns();

		ptr = matrix.getObject(1, 14);

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
	Coordinate destination = getAdjecantStreet(houseptr, rescueTruck->getCoord());

	while(!finished){
		std::cout << "entered loop" << std::endl;
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

			driveTruck(destination, rescueTruck);
			// Scenario 2: truckStreet and destStreet are parallel.
					/*	else if (checkOrientation(truckLoc) == checkOrientation(destination)) {
							std::cout << "PARALLEL" << std::endl;
							// Move to the nearest crossroad.
							if ((matrix.getObject(truckLoc.getX(), truckLoc.getY()))->getType() == crossroad) {
								if (truckLoc.getY() != destination.getY()) {
									Coordinate correctY(truckLoc.getX(), destination.getY());
									driveTruck(correctY, truckLoc, rescueTruck, "parallel");
								}
								else {
									// Reduced to problem in case 1
									driveTruck(destination, truckLoc, rescueTruck);
								}
							}
							else {
								// Find the closest crossroad and move to it.
								Crossroad xroad = closestCrossroad(truckLoc);
								driveTruck(xroad.getLocation(), truckLoc, rescueTruck, "parallel");
							}
						}
		/*
			// Scenario 3: truckStreet and destStreet are not parallel.
			else {
				std::cout << "LOODRECHT" << std::endl;
				if (destination.getX() != truckLoc.getX()) {
					Coordinate correctX(destination.getX(), truckLoc.getY());
					driveTruck(correctX, truckLoc, rescueTruck);
				}
				else {
					driveTruck(destination, truckLoc, rescueTruck);
				}
			}*/
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

Coordinate City::getAdjecantStreet(CityObjects* building, Coordinate truckLoc) {

	House* houseptr = dynamic_cast<House*>(building);
	std::vector<Coordinate> coordinates;

	// Check adjecant points to upper left
	Coordinate location = houseptr->getLocation();
	if (location.getY() + 1 < matrix.getRows()){
		if(matrix.getObject(location.getX(), location.getY() +1)->getType() == street){
			coordinates.push_back(Coordinate(location.getX(), location.getY() +1));
		}
	}
	if (location.getX() - 1 >= 0){
		if(matrix.getObject(location.getX() -1, location.getY())->getType() == street){
			coordinates.push_back(Coordinate(location.getX()-1, location.getY()));
		}
	}

	// Check adjecant points to upper right
	location = Coordinate(location.getX()+1, location.getY());
	if (location.getY() + 1 < matrix.getRows()){
		if(matrix.getObject(location.getX(), location.getY() +1)->getType() == street){
			coordinates.push_back(Coordinate(location.getX(), location.getY() +1));
		}
	}
	if (location.getX() + 1 < matrix.getColumns()){
		if(matrix.getObject(location.getX() +1, location.getY())->getType() == street){
			coordinates.push_back(Coordinate(location.getX()+1, location.getY()));
		}
	}

	// Check adjecant points to down left
	location = Coordinate(location.getX(), location.getY()-1);
	if (location.getY() - 1 >= 0){
		if(matrix.getObject(location.getX(), location.getY() -1)->getType() == street){
			std::cout << "true that" << std::endl;
			coordinates.push_back(Coordinate(location.getX(), location.getY() -1));
		}
	}
	if (location.getX() + 1 < matrix.getColumns()){
		if(matrix.getObject(location.getX() +1, location.getY())->getType() == street){
			coordinates.push_back(Coordinate(location.getX()+1, location.getY()));
		}
	}

	// Check adjecant points to down right
	location = Coordinate(location.getX()-1, location.getY());
	if (location.getY() - 1 >= 0){
		if(matrix.getObject(location.getX(), location.getY() -1)->getType() == street){
			coordinates.push_back(Coordinate(location.getX(), location.getY() -1));
		}
	}
	if (location.getX() - 1 >= 0){
		if(matrix.getObject(location.getX() -1, location.getY())->getType() == street){
			coordinates.push_back(Coordinate(location.getX()-1, location.getY()));
		}
	}

	std::pair<double, Coordinate> closest(calculateDistance(*coordinates.begin(), truckLoc), *coordinates.begin());

	for(std::vector<Coordinate>::iterator it = coordinates.begin(); it != coordinates.end(); it++){
		if (calculateDistance(*it, truckLoc) < closest.first) {
			closest.first = calculateDistance(*it, truckLoc);
			closest.second = *it;
		}
	}

	return closest.second;
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
		if (checkSide->getType() == street || checkSide->getType() == crossroad) {
			right = true;
		}
	}

	// Check leftside (including boundscheck)
	if (coord.getX() - 1 >= 0) {
		checkSide = matrix.getObject(coord.getX() - 1, coord.getY());
		if (checkSide->getType() == street || checkSide->getType() == crossroad) {
			left = true;
		}
	}

	// Check upside (including boundscheck)
	if (coord.getY() + 1 <= matrix.getRows()) {
		checkSide = matrix.getObject(coord.getX(), coord.getY() + 1);
		if (checkSide->getType() == street || checkSide->getType() == crossroad) {
			up = true;
		}
	}

	// Check downside (including boundscheck)
	if (coord.getY() - 1 >= 0) {
		checkSide = matrix.getObject(coord.getX(), coord.getY() - 1);
		if (checkSide->getType() == street || checkSide->getType() == crossroad) {
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
	int distance = sqrt(pow(c2.getX() - c1.getX(), 2) + pow(c2.getY() - c1.getY(), 2));
	return distance;
}

void City::driveTruck(Coordinate destination,Firetruck* rescueTruck) {
	Coordinate cur = rescueTruck->getCoord();

	Street* destStreet = dynamic_cast<Street*>(matrix.getObject(destination.getX(), destination.getY()));
	// Scenario 1: rescueTruck is in the same street as destination.
	if (checkOrientation(rescueTruck->getCoord()) == "crossroad") {
		Crossroad* truckCross = dynamic_cast<Crossroad*>(matrix.getObject(rescueTruck->getCoord().getX(), rescueTruck->getCoord().getY()));
		if (truckCross->getStreet1() == destStreet->getName() || truckCross->getStreet2() == destStreet->getName()) {
			std::string orientation = checkOrientation(destination);
			if (orientation == "horizontal") {
				if (destination.getY() == cur.getY()) {
					std::cout << "SAME STREET" << std::endl;

					if (destination.getX() < cur.getX()) {
						rescueTruck->move("left");
					}
					else {
						rescueTruck->move("right");
					}
				}
			}
			if (orientation == "vertical") {
				if (destination.getY() < cur.getY()) {
					rescueTruck->move("down");
				}
				else {
					rescueTruck->move("up");
				}
			}
		}
		else {
			// on crossroad but wrong streets
			// go to other crossroad with streetname

			Crossroad xRoad = closestCorrectCrossroad(cur, destStreet);
			rescueTruck->setTempDestination(xRoad.getLocation());
			rescueTruck->setGoToTemp(true);

			if (xRoad.getLocation().getX() < cur.getX()) {
				rescueTruck->move("left");
			}
			else if (xRoad.getLocation().getX() > cur.getX()) {
				rescueTruck->move("right");
			}
			else if (xRoad.getLocation().getY() < cur.getY()) {
				rescueTruck->move("down");
			}
			else {
				rescueTruck->move("up");
			}
		}
	}
	else {
		Street* curStreet = dynamic_cast<Street*>(matrix.getObject(rescueTruck->getCoord().getX(), rescueTruck->getCoord().getY()));
		if (destStreet->getName() == curStreet->getName()) {
		std::string orientation = checkOrientation(destination);
			if (orientation == "horizontal") {
				if (destination.getY() == cur.getY()) {
					std::cout << "SAME STREET" << std::endl;

					if (destination.getX() < cur.getX()) {
						rescueTruck->move("left");
					}
					else {
						rescueTruck->move("right");
					}
				}
			}
			if (orientation == "vertical") {
				if (destination.getY() < cur.getY()) {
					rescueTruck->move("down");
				}
				else {
					rescueTruck->move("up");
				}
			}
		}
		else {
			std::string orientation = checkOrientation(rescueTruck->getCoord());
			if (!rescueTruck->getGoToTemp()) {
				//Go to the closest crossroad
				Crossroad xroad = closestCrossroad(rescueTruck->getCoord());
				if (orientation == "horizontal") {
					if (xroad.getLocation().getX() < cur.getX()) {
						rescueTruck->move("left");
					}
					else {
						rescueTruck->move("right");
					}
				}
				if (orientation == "vertical") {
					if (xroad.getLocation().getY() < cur.getY()) {
						rescueTruck->move("down");
					}
					else {
						rescueTruck->move("up");
					}
				}
			}
			else {
				if (orientation == "horizontal") {
					if (rescueTruck->getTempDest().getX() < cur.getX()) {
						rescueTruck->move("left");
					}
					else {
						rescueTruck->move("right");
					}
				}
				if (orientation == "vertical") {
					if (rescueTruck->getTempDest().getY() < cur.getY()) {
						rescueTruck->move("down");
					}
					else {
						rescueTruck->move("up");
					}
				}

				if (rescueTruck->getCoord().getX() == )
			}
		}
	}

}

Crossroad City::closestCorrectCrossroad(Coordinate cur, Street* destStreet) {
	std::vector<Crossroad> xRoads;

	Coordinate correctCrossroad;
	std::list<Crossroad>::iterator it_c;
	for (it_c = crossroads.begin(); it_c != crossroads.end(); it_c++) {
		if (it_c->getStreet1() == destStreet->getName() || it_c->getStreet2() == destStreet->getName()) {
			xRoads.push_back(*it_c);
		}
	}

	std::pair<Crossroad, int> closest (*(xRoads.begin()), calculateDistance(xRoads.begin()->getLocation(), cur));
	for (it_c = crossroads.begin(); it_c != crossroads.end(); it_c++) {
		int distance = calculateDistance(it_c->getLocation(), cur);
		if (distance < closest.second) {
			closest.first = *it_c;
			closest.second = distance;
		}
	}
	return closest.first;
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
