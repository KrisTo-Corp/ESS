//=======================================================================================
// Name        : City.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : City in C++, Ansi-style
//=======================================================================================

#include "City.h"
#include "xmlparser.h"

#include <cstdlib>
#include <cmath>

City::City() : output(std::cout){
	validCity = false;
	_initCheck = this;
}

City::City(const std::string filename, std::ostream& stream) : output(stream) {

	validCity = true;
	_initCheck = this;

	output << "\t\t\t\t\t\t\t\tEMERGENCY SERVICES SIMULATION \n";
	output << "\t\t\t\t\t\t\t\t============================= \n\n";

	XmlParser parser(this);
	parser.parseCity(filename);
	std::pair<int, int> maxCoords =	parser.getMaxValues();

	if(maxCoords.first == -1 && maxCoords.second == -1){
		output << "ERROR: .XML CONTAINED SYNTAX ERRORS !\n\n";
		validCity = false;
		return;
	}

	else if(maxCoords.first == -2 && maxCoords.second == -2){
		output << "ERROR: THERE WAS NO ROOT FOUND IN THE XMLFILE !\n\n";
		validCity = false;
		return;
	}

	else if(maxCoords.first == -3 && maxCoords.second == -3){
		output << "ERROR: THERE WAS FOUND AN OBJECT THAT'S NOT SUPPORTED !\n\n";
		validCity = false;
		return;
	}

	matrix = Matrix(maxCoords.second + 1, maxCoords.first +1);

	link_trucks_to_bases();
	matrix.addHouses(houses);
	matrix.addFiredeps(departments);
	crossroads = matrix.addStreets(streets);
	matrix.addCrossroads(crossroads);

	output << matrix << "\n";

	output << "\nINTEGRITYCHECK: \n";
	output << "===============\n";
	if (!(integrityCheck())){
		validCity = false;
		return;
	}
	else {
		output << "\tPASSED\n\n";
	}

	ENSURE(properlyInitialized(), "Object 'City' was not properly initialized.");
}

 City::City(const std::string filename, std::ofstream stream) : output(stream) {

	validCity = true;
	_initCheck = this;

	//output = stream;

	output << "\t\t\t\t\t\t\t\tEMERGENCY SERVICES SIMULATION \n";
	output << "\t\t\t\t\t\t\t\t============================= \n\n";

	XmlParser parser(this);
	parser.parseCity(filename);
	std::pair<int, int> maxCoords =	parser.getMaxValues();

	if(maxCoords.first == -1 && maxCoords.second == -1){
		output << "ERROR: .XML CONTAINED SYNTAX ERRORS !\n\n";
		validCity = false;
		return;
	}

	else if(maxCoords.first == -2 && maxCoords.second == -2){
		output << "ERROR: THERE WAS NO ROOT FOUND IN THE XMLFILE !\n\n";
		validCity = false;
		return;
	}

	else if(maxCoords.first == -3 && maxCoords.second == -3){
		output << "ERROR: THERE WAS FOUND AN OBJECT THAT'S NOT SUPPORTED !\n\n";
		validCity = false;
		return;
	}

	matrix = Matrix(maxCoords.second + 1, maxCoords.first +1);

	link_trucks_to_bases();
	matrix.addHouses(houses);
	matrix.addFiredeps(departments);
	crossroads = matrix.addStreets(streets);
	matrix.addCrossroads(crossroads);

	output << matrix << "\n";

	output << "\nINTEGRITYCHECK: \n";
	output << "===============\n";
	if (!(integrityCheck())){
		validCity = false;
		return;
	}
	else {
		output << "\tPASSED\n\n";
	}

	ENSURE(properlyInitialized(), "Object 'City' was not properly initialized.");
}

City::~City()
{
}

std::ostream& operator <<(std::ostream& s, City& city) {
	REQUIRE(city.properlyInitialized(), "Object 'City' was not properly initialized when calling overloaded operator '<<'");

	s << city.matrix << "\n";
	return s;
}

int City::getAmountHouses(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountHouses()");

	return houses.size();
}
int City::getAmountDepartments(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountDepartments()");

	return departments.size();
}
int City::getAmountStreets(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountStreets()");

	return streets.size();
}
int City::getAmountCrossroads(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountCrossroads()");

	return crossroads.size();
}
int City::getAmountTrucks(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountTrucks()");

	return trucks.size();
}

CityObjects* City::getObject(int x, int y){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getObject()");

	return matrix.getObject(x, y);
}

Firetruck* City::getTruck(int loop){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getTruck()");

	std::list<Firetruck>::iterator it = trucks.begin();
	for (int i = 0; i < loop; i++){
		it++;
	}
	return &(*it);
}

City& City::operator =(const City& c){
	houses = c.houses;
	departments = c.departments;
	streets = c.streets;
	crossroads = c.crossroads;
	trucks = c.trucks;
	matrix = c.matrix;

	_initCheck = this;

	return *this;
}

void City::link_trucks_to_bases() {
	std::list<Firetruck>::iterator it_t;
	std::list<Fire_Department>::iterator it_dep;
	for (it_t = trucks.begin(); it_t != trucks.end(); it_t++) {
		Firetruck* truckptr = &(*it_t);
		std::string basename = truckptr->getBasename();
		for (it_dep = departments.begin(); it_dep != departments.end(); it_dep++) {
			Fire_Department* depptr = &(*it_dep);
			std::string dep_name = depptr->getName();
			if (basename == dep_name) {
				// Add truck to the fire department.
				depptr->addTruck(truckptr);
				// Set values in Firetruck
				truckptr->setCoord(depptr->getEntrance());
				truckptr->linkBase(depptr);
				truckptr->setDestination(depptr->getEntrance());
			}
		}
		if (truckptr->getBaseptr() == NULL){
			continue;
		}
	}
}

bool City::properlyInitialized() {
	return _initCheck == this;
}

bool City::properlyInitialized(int x, int y){
	return matrix.properlyInitialized(x, y);
}

CityObjects* City::setFire(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling setFire()");

	bool succes = false;
	CityObjects* ptr;

	while (!succes){

		int random_y = rand()% matrix.getRows();
		int random_x = rand()% matrix.getColumns();

		ptr = matrix.getObject(random_x, random_y);

		if (ptr->getState() == normal){
			succes = true;
		}
	}

	ptr->setState(burning);

	ENSURE(ptr->getState() == burning, "setFire() did not correctly set fire to a house.");

	return ptr;
}

CityObjects* City::setFire(int x, int y){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling setFire()");

	bool succes = false;
	CityObjects* ptr;

	ptr = matrix.getObject(x, y);

	if (ptr->getState() == normal){
		succes = true;
	}

	ptr->setState(burning);

	ENSURE(ptr->getState() == burning, "setFire() did not correctly set fire to the given house.");

	return ptr;
}

Coordinate City::getAdjecantStreet(CityObjects* building, Coordinate truckLoc) {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAdjecantStreet()");

	Structures* ptr = dynamic_cast<Structures*>(building);
	std::vector<Coordinate> coordinates;
	Coordinate location;

	for (int x = 0; x < ptr->getWidth(); x++){
		for (int y = 0; y < ptr->getLength(); y++){

			location = ptr->getLocation();
			location.setX(location.getX()+x);
			location.setY(location.getY()-y);

			if (location.getY() < matrix.getRows()-1) {
				if (matrix.getObject(location.getX(), location.getY()+1) == NULL) {
					continue;
				}
				else if(matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
					coordinates.push_back(Coordinate(location.getX(), location.getY()+1));
				}
			}

			if (location.getY() > 0){
				if (matrix.getObject(location.getX(), location.getY()-1) == NULL) {
					continue;
				}
				else if(matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
					coordinates.push_back(Coordinate(location.getX(), location.getY()-1));
				}
			}

			if (location.getX() < matrix.getColumns()-1){
				if (matrix.getObject(location.getX()+1, location.getY()) == NULL) {
					continue;
				}
				else if (matrix.getObject(location.getX()+1, location.getY())->getType() == street){
					coordinates.push_back(Coordinate(location.getX()+1, location.getY()));
				}
			}
			if (location.getX() > 0){
				if (matrix.getObject(location.getX()-1, location.getY()) == NULL) {
					continue;
				}
				else if(matrix.getObject(location.getX()-1, location.getY())->getType() == street){
					coordinates.push_back(Coordinate(location.getX()-1, location.getY()));
				}
			}
		}
	}

	if (coordinates.size() == 0){
		return Coordinate(-1, -1);
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
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling checkOrientation()");
	REQUIRE((matrix.getObject(coord.getX(), coord.getY()))->getType() == street || (matrix.getObject(coord.getX(), coord.getY()))->getType() == crossroad, "I can not determine the orientation of anything non-street.");

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
	if (coord.getX() + 1 < matrix.getColumns()) {
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
	if (coord.getY() + 1 < matrix.getRows()) {
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
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling closestCrossroad()");

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
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling calculateDistance()");

	int distance = sqrt(pow(c2.getX() - c1.getX(), 2) + pow(c2.getY() - c1.getY(), 2));
	return distance;
}

void City::driveTruck(Firetruck* rescueTruck) {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling driveTruck()");

	Coordinate cur = rescueTruck->getCoord();
	Coordinate destination = rescueTruck->getDestination();

	if (cur == destination) {
		return;
	}

	Street* destStreet = dynamic_cast<Street*>(matrix.getObject(destination.getX(), destination.getY()));
	if (checkOrientation(rescueTruck->getCoord()) == "crossroad") {
		Crossroad* truckCross = dynamic_cast<Crossroad*>(matrix.getObject(rescueTruck->getCoord().getX(), rescueTruck->getCoord().getY()));
		if (truckCross->getStreet1() == destStreet->getName() || truckCross->getStreet2() == destStreet->getName()) {
			std::string orientation = checkOrientation(destination);
			if (orientation == "horizontal") {
				if (destination.getY() == cur.getY()) {
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
			rescueTruck->setTempDest(xRoad.getLocation());
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

				if (rescueTruck->getTempDest() == rescueTruck->getCoord()) {
					rescueTruck->setGoToTemp(false);
				}
			}
		}
	}

}

Crossroad City::closestCorrectCrossroad(Coordinate cur, Street* destStreet) {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling closestCrossroad()");

	std::vector<Crossroad> xRoads;

	Coordinate correctCrossroad;
	std::list<Crossroad>::iterator it_c;
	for (it_c = crossroads.begin(); it_c != crossroads.end(); it_c++) {
		if (it_c->getStreet1() == destStreet->getName() || it_c->getStreet2() == destStreet->getName()) {
			xRoads.push_back(*it_c);
		}
	}

	std::vector<Crossroad>::iterator it_vc;
	std::pair<Crossroad, int> closest (*(xRoads.begin()), calculateDistance(xRoads.begin()->getLocation(), cur));
	for (it_vc = xRoads.begin(); it_vc != xRoads.end(); it_vc++) {
		int distance = calculateDistance(it_vc->getLocation(), cur);
		if (distance < closest.second) {
			closest.first = *it_vc;
			closest.second = distance;
		}
	}
	return closest.first;
}

bool City::integrityCheck() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling integrityCheck()");

	bool integrity = true;
	std::vector<Coordinate> coordinates;

	for (std::list<House>::iterator ith = houses.begin(); ith != houses.end(); ith++){
		Coordinate location;
		CityObjects* ptr = &(*ith);
		if (getAdjecantStreet(ptr, Coordinate(0, 0)) == Coordinate(-1, -1)){
			House* houseptr = dynamic_cast<House*>(ptr);
			Coordinate houselocation = houseptr->getLocation();
			output << "\tERROR: House at location "<< houselocation << " doesn't have a street linked to it.\n";
			integrity = false;
		}
		for (int x = 0; x < 2; x++){
			for (int y = 0; y < 2; y++){
				location = ith->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*ith)){
					Coordinate houselocation = ith->getLocation();
					output << "\tERROR: House at location " << houselocation << " is supposed to be at " << location << " but is not.\n";
					integrity = false;
				}
				coordinates.push_back(location);
			}
		}
	}

	for (std::list<Fire_Department>::iterator itd = departments.begin(); itd != departments.end(); itd++){
		Coordinate location;
		CityObjects* ptr = &(*itd);
		if (getAdjecantStreet(ptr, Coordinate(0, 0)) == Coordinate(-1, -1)){
			Fire_Department* depptr = dynamic_cast<Fire_Department*>(ptr);
			Coordinate deplocation = depptr->getLocation();
			output << "\tERROR: Department at location "<< deplocation << " doesn't have a street linked to it.\n";
			integrity = false;
		}
		for (int x = 0; x < 4; x++){
			for (int y = 0; y < 4; y++){
				location = itd->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*itd)){
					Coordinate deplocation = itd->getLocation();
					output << "\tERROR: Department at location " << deplocation << " is supposed to be at " << location << " but is not.\n";
					integrity = false;
				}
				coordinates.push_back(location);
			}
		}
	}

	for (std::list<Street>::iterator its = streets.begin(); its != streets.end(); its++){
		Coordinate location;
		Coordinate start = its->getStart();
		Coordinate end = its->getEnd();
		location = start;

		if (start.getX() == end.getX()){
			for (int y = start.getY(); y <= end.getY(); y++){
				location.setY(y);
				if (matrix.getObject(location.getX(), location.getY()) == NULL) {
					continue;
				}
				if (matrix.getObject(location.getX(), location.getY())->getType() == street){
					coordinates.push_back(location);
					Street* ptr = dynamic_cast<Street*>(matrix.getObject(location.getX(), location.getY()));
					if (its->getName() != ptr->getName()){
						output << "\tERROR: Street " << its->getName() << " was supposed to be found on location " << location << " but is not.\n";
						integrity = false;
					}
					if(location.getX() == 0){
						if (matrix.getObject(location.getX()+1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()+1, location.getY())->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else if (location.getX() == matrix.getColumns()-1){
						if (matrix.getObject(location.getX()-1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()-1, location.getY())->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else {
						if (matrix.getObject(location.getX()-1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()-1, location.getY())->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
						if (matrix.getObject(location.getX()+1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()+1, location.getY())->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
				}
				else if (matrix.getObject(location.getX(), location.getY())->getType() == crossroad){
					Crossroad* ptr = dynamic_cast<Crossroad*>(matrix.getObject(location.getX(), location.getY()));
					if ((its->getName() != ptr->getStreet1()) && (its->getName() != ptr->getStreet2())){
						output << "\tERROR: Street " << its->getName() << " was supposed to be found on location " << location << " but is not. (as a crossroad)\n";
						integrity = false;
					}
				}
			}
		}

		else if (start.getY() == end.getY()){
			for (int x = start.getX(); x <= end.getX(); x++){
				location.setX(x);
				if (matrix.getObject(location.getX(), location.getY()) == NULL) {
					continue;
				}
				if (matrix.getObject(location.getX(), location.getY())->getType() == street){
					coordinates.push_back(location);
					Street* ptr = dynamic_cast<Street*>(matrix.getObject(location.getX(), location.getY()));
					if (its->getName() != ptr->getName()){
						output << "\tERROR: Street " << its->getName() << " was supposed to be found on location " << location << " but is not.\n";
						integrity = false;
					}
					if(location.getY() == 0){
						if (matrix.getObject(location.getX(), location.getY()+1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else if (location.getY() == matrix.getRows()-1){
						if (matrix.getObject(location.getX(), location.getY()-1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else {
						if (matrix.getObject(location.getX(), location.getY()-1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
						if (matrix.getObject(location.getX(), location.getY()+1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
							output << "\tERROR: Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
				}
				else if (matrix.getObject(location.getX(), location.getY())->getType() == crossroad){
					Crossroad* ptr = dynamic_cast<Crossroad*>(matrix.getObject(location.getX(), location.getY()));
					if ((its->getName() != ptr->getStreet1()) && (its->getName() != ptr->getStreet2())){
						output << "\tERROR: Street " << its->getName() << " was supposed to be found on location " << location << " but is not. (as a crossroad)\n";
						integrity = false;
					}
				}
			}
		}
	}

	for (std::list<Crossroad>::iterator itc = crossroads.begin(); itc != crossroads.end(); itc++){
		Coordinate location = itc->getLocation();
		if (matrix.getObject(location.getX(), location.getY()) != &(*itc)){
			output << "\tERROR: Crossroad " << itc->getName() << " was supposed to be found on location " << location << " but is not.\n";
			integrity = false;
		}
		coordinates.push_back(location);
	}



	for (int i = 0; i < coordinates.size(); i++){
		for (int j = i+1; j < coordinates.size(); j++){
			if (coordinates[i] == coordinates[j]){
				output << "\tERROR: Overlap found at location " << coordinates[i] << ".\n";
				integrity = false;
			}
		}
	}

	if (coordinates.size() != matrix.getRows()*matrix.getColumns()){
		output << "\tERROR: Empty spots were found in the city.\n";
		integrity = false;
	}

	for (std::list<Firetruck>::iterator itt = trucks.begin(); itt != trucks.end(); itt++){
		Fire_Department* ptr = itt->getBaseptr();
		bool found = false;
		for (std::list<Fire_Department>::iterator itd = departments.begin(); itd != departments.end(); itd++){
			if (&(*itd) == ptr){
				found = true;
			}
		}
		if (found == false){
			output << "\tERROR: Truck with name " << itt->getName() << " was not linked to a base.\n";
			integrity = false;
		}
	}
	return integrity;
}

/*void City::close(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling close()");

	output.close();

	ENSURE(!(output.is_open()), "File did not close properly when calling close()");
}*/

std::list<Firetruck>* City::getTruckList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getTruckList()");

	return &trucks;
}

std::list<House>* City::getHouseList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getHouseList()");

	return &houses;
}

std::list<Fire_Department>* City::getDepList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getDepList()");

	return &departments;
}


std::list<Street>* City::getStreetsList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getStreetList()");

	return &streets;
}

Matrix* City::getMatrix() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getMatrix()");

	return &matrix;
}

bool City::getValidCity() {
	return validCity;
}
