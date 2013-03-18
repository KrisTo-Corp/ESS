//=======================================================================================
// Name        : City.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : City in C++, Ansi-style
//=======================================================================================

#include "City.h"

#include <cstdlib>

#include <cmath>

City::City(){
	validCity = false;
	_initCheck = this;
}

City::City(const std::string filename, std::string outputname): output(outputname.c_str()){

	validCity = true;

	output << "\t\tEMERGENCY SERVICES SIMULATION \n\n\n";

	std::pair<int, int> maxCoords =	parseCity(filename);

	if(maxCoords.first == -1 && maxCoords.second == -1){
		output << ".XML CONTAINED SYNTAX ERRORS !\n\n";
		validCity = false;
		return;
	}

	else if(maxCoords.first == -2 && maxCoords.second == -2){
		output << "THERE WAS NO ROOT FOUND IN THE XMLFILE !\n\n";
		validCity = false;
		return;
	}

	else if(maxCoords.first == -3 && maxCoords.second == -3){
		output << "THERE WAS FOUND AN OBJECT THAT'S NOT SUPPORTED !\n\n";
		validCity = false;
		return;
	}

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

	if (!(integrityCheck())){
		output << "THE GENERATED CITY WAS NOT VALID !\n";
		validCity = false;
		return;
	}

	output << matrix << "\n\n\n";

	_initCheck = this;

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
	return houses.size();
}
int City::getAmountDepartments(){
	return departments.size();
}
int City::getAmountStreets(){
	return streets.size();
}
int City::getAmountCrossroads(){
	return crossroads.size();
}
int City::getAmountTrucks(){
	return trucks.size();
}

CityObjects* City::getObject(int x, int y){
	return matrix.getObject(x, y);
}

Firetruck* City::getTruck(int loop){
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
				it_t->setDestination(it_t->getBaseptr()->getEntrance());
			}
		}
		if (it_t->getBaseptr() == NULL){
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

	return ptr;
}

CityObjects* City::setFire(int x, int y){
	bool succes = false;
	CityObjects* ptr;

	ptr = matrix.getObject(x, y);

	if (ptr->getState() == normal){
		succes = true;
	}

	ptr->setState(burning);

	return ptr;
}

void City::update() {

	if (!(validCity)){
		return;
	}

	bool finished = false;
	CityObjects* ptr;

	ptr = setFire();
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	Coordinate cur = structptr->getLocation();
	std::string name = structptr->getName();
	output << name << " at location " << cur << " started burning." << std::endl;
	House* houseptr = dynamic_cast<House*>(structptr);
	double hp = houseptr->getHP();
	output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

	// Find an available firetruck.
	std::list<Firetruck>::iterator it_t;
	Firetruck* rescueTruck;
	for (it_t = trucks.begin(); it_t != trucks.end(); it_t++) {
		if (it_t->getAvailable()) {
			it_t->setAvailable(false);
			it_t->setDestination(getAdjecantStreet(houseptr, it_t->getCoord()));
			it_t->setTarget(houseptr);
			it_t->setIsHome(false);
			break;
		}
	}

	while (!finished) {
		// Random chance to setFire()
		int chance = rand() % 20;
		if (chance == 20) {
			ptr = setFire();
			Structures* structptr = dynamic_cast<Structures*>(ptr);
			Coordinate cur = structptr->getLocation();
			std::string name = structptr->getName();
			output << name << " at location " << cur << " started burning." << std::endl;
			House* houseptr = dynamic_cast<House*>(structptr);
			double hp = houseptr->getHP();
			output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

			// Find an available firetruck.
			std::list<Firetruck>::iterator it_t;
			Firetruck* rescueTruck;
			for (it_t = trucks.begin(); it_t != trucks.end(); it_t++) {
				if (it_t->getAvailable()) {
					it_t->setAvailable(false);
					it_t->setDestination(getAdjecantStreet(houseptr, it_t->getCoord()));
					it_t->setTarget(houseptr);
					it_t->setIsHome(false);
					break;
				}
			}
		}

		// Burn
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

		int i = 0;

		// Move
		for (std::list<Firetruck>::iterator it = trucks.begin(); it != trucks.end(); it++) {
			driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				if (it->getAvailable() == false) {
					Structures* saved = it->getTarget();
					if (saved->getState() == burning) {
						saved->setState(normal);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						output << "Firetruck " << it->getName() << " has reached its destination ";
						output << " at location " << destination << " and has extinguished the fire and are returning home.\n" << std::endl;
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						output << "Firetruck " << it->getName() << " has reached its destination ";
						output << " at location " << destination << " and saw that the structure was destroyed and are now returning home.\n" << std::endl;
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						output << "Firetruck " << it->getName() << " has arrived at its base " << it->getBaseptr()->getName() << std::endl << std::endl;
						it->setIsHome(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(matrix.getObject(it->getCoord().getX(), it->getCoord().getY()));
				output << "Firetruck " << it->getName() << " is on its way to " << name << " on location ";
				output << destination << ". The firetruck is at " << truckStreet->getName() << " on location " << location << std::endl << std::endl;
			}
		}

		// Determine if finished
		if (i == trucks.size()) {
			finished = true;
		}
	}
}

void City::update_test() {

	if (!(validCity)){
		return;
	}

	bool finished = false;
	CityObjects* ptr;
	int loopcounter = 0;

	ptr = setFire(4, 14);
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	Coordinate cur = structptr->getLocation();
	std::string name = structptr->getName();
	output << name << " at location " << cur << " started burning." << std::endl;
	House* houseptr = dynamic_cast<House*>(structptr);
	double hp = houseptr->getHP();
	output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

	// Find an available firetruck.
	std::list<Firetruck>::iterator it_t;
	Firetruck* rescueTruck;
	for (it_t = trucks.begin(); it_t != trucks.end(); it_t++) {
		if (it_t->getAvailable()) {
			it_t->setAvailable(false);
			it_t->setDestination(getAdjecantStreet(houseptr, it_t->getCoord()));
			it_t->setTarget(houseptr);
			it_t->setIsHome(false);
			break;
		}
	}

	while (!finished) {

		if (loopcounter == 5) {
			ptr = setFire(15, 1);
			Structures* structptr = dynamic_cast<Structures*>(ptr);
			Coordinate cur = structptr->getLocation();
			std::string name = structptr->getName();
			output << name << " at location " << cur << " started burning." << std::endl;
			House* houseptr = dynamic_cast<House*>(structptr);
			double hp = houseptr->getHP();
			output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

			// Find an available firetruck.
			std::list<Firetruck>::iterator it_t;
			Firetruck* rescueTruck;
			for (it_t = trucks.begin(); it_t != trucks.end(); it_t++) {
				if (it_t->getAvailable()) {
					it_t->setAvailable(false);
					it_t->setDestination(getAdjecantStreet(houseptr, it_t->getCoord()));
					it_t->setTarget(houseptr);
					it_t->setIsHome(false);
					break;
				}
			}
		}

		// Burn
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

		int i = 0;

		// Move
		for (std::list<Firetruck>::iterator it = trucks.begin(); it != trucks.end(); it++) {
			driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				if (it->getAvailable() == false) {
					Structures* saved = it->getTarget();
					if (saved->getState() == burning) {
						saved->setState(normal);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						output << "Firetruck " << it->getName() << " has reached its destination ";
						output << " at location " << destination << " and has extinguished the fire and are returning home.\n" << std::endl;
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						output << "Firetruck " << it->getName() << " has reached its destination ";
						output << " at location " << destination << " and saw that the structure was destroyed and are now returning home.\n" << std::endl;
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						output << "Firetruck " << it->getName() << " has arrived at its base " << it->getBaseptr()->getName() << std::endl << std::endl;
						it->setIsHome(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(matrix.getObject(it->getCoord().getX(), it->getCoord().getY()));
				output << "Firetruck " << it->getName() << " is on its way to " << name << " on location ";
				output << destination << ". The firetruck is at " << truckStreet->getName() << " on location " << location << std::endl << std::endl;
			}
		}

		// Determine if finished
		if (i == trucks.size()) {
			finished = true;
		}
		loopcounter++;
	}
}


/*
 * 1. setFire to 1 house to start the simulation
 * 2. select a truck and give its destination
 * 					WHILE
 * 3. random chance to setFire()
 * 4. IF succes
 * 		-> select a truck
 * 5. move truck to destination
 *
 */


Coordinate City::getAdjecantStreet(CityObjects* building, Coordinate truckLoc) {

	Structures* ptr = dynamic_cast<Structures*>(building);
	std::vector<Coordinate> coordinates;
	Coordinate location;

	for (int x = 0; x < ptr->getWidth(); x++){
		for (int y = 0; y < ptr->getLength(); y++){

			location = ptr->getLocation();
			location.setX(location.getX()+x);
			location.setY(location.getY()-y);

			if (location.getY() < matrix.getRows()-1) {
				if(matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
					coordinates.push_back(Coordinate(location.getX(), location.getY()+1));
				}
			}

			if (location.getY() > 0){
				if(matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
					coordinates.push_back(Coordinate(location.getX(), location.getY()-1));
				}
			}

			if (location.getX() < matrix.getColumns()-1){
				if(matrix.getObject(location.getX()+1, location.getY())->getType() == street){
					coordinates.push_back(Coordinate(location.getX()+1, location.getY()));
				}
			}

			if (location.getX() > 0){
				if(matrix.getObject(location.getX()-1, location.getY())->getType() == street){
					coordinates.push_back(Coordinate(location.getX()-1, location.getY()));
				}
			}
		}
	}

	std::pair<double, Coordinate> closest(calculateDistance(*coordinates.begin(), truckLoc), *coordinates.begin());

	if (coordinates.size() == 0){
		return Coordinate(-1, -1);
	}

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

void City::driveTruck(Firetruck* rescueTruck) {
	Coordinate cur = rescueTruck->getCoord();
	Coordinate destination = rescueTruck->getDestination();

	if (cur == destination) {
		return;
	}

	Street* destStreet = dynamic_cast<Street*>(matrix.getObject(destination.getX(), destination.getY()));
	// Scenario 1: rescueTruck is in the same street as destination.
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

	bool integrity = true;

	std::vector<Coordinate> coordinates;

	for (std::list<House>::iterator ith = houses.begin(); ith != houses.end(); ith++){
		Coordinate location;
		CityObjects* ptr = &(*ith);
		if (getAdjecantStreet(ptr, Coordinate(0, 0)) == Coordinate(-1, -1)){
			House* houseptr = dynamic_cast<House*>(ptr);
			Coordinate houselocation = houseptr->getLocation();
			output << "House at location "<< houselocation << " doesn't have a street linked to it.\n";
			integrity = false;
		}
		for (int x = 0; x < 2; x++){
			for (int y = 0; y < 2; y++){
				location = ith->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*ith)){
					Coordinate houselocation = ith->getLocation();
					output << "House at location " << houselocation << " is supposed to be at " << location << " but is not.\n";
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
			output << "Department at location "<< deplocation << " doesn't have a street linked to it.\n";
			integrity = false;
		}
		for (int x = 0; x < 4; x++){
			for (int y = 0; y < 4; y++){
				location = itd->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*itd)){
					Coordinate deplocation = itd->getLocation();
					output << "Department at location " << deplocation << " is supposed to be at " << location << " but is not.\n";
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
				if (matrix.getObject(location.getX(), location.getY())->getType() == street){
					coordinates.push_back(location);
					Street* ptr = dynamic_cast<Street*>(matrix.getObject(location.getX(), location.getY()));
					if (its->getName() != ptr->getName()){
						output << "Street " << its->getName() << " was supposed to be found on location " << location << " but is not.\n";
						integrity = false;
					}
					if(location.getX() == 0){
						if (matrix.getObject(location.getX()+1, location.getY())->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else if (location.getX() == matrix.getColumns()-1){
						if (matrix.getObject(location.getX()-1, location.getY())->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else {
						if (matrix.getObject(location.getX()-1, location.getY())->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
						if (matrix.getObject(location.getX()+1, location.getY())->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
				}
				else if (matrix.getObject(location.getX(), location.getY())->getType() == crossroad){
					Crossroad* ptr = dynamic_cast<Crossroad*>(matrix.getObject(location.getX(), location.getY()));
					if ((its->getName() != ptr->getStreet1()) && (its->getName() != ptr->getStreet2())){
						output << "Street " << its->getName() << " was supposed to be found on location " << location << " but is not. (as a crossroad)\n";
						integrity = false;
					}
				}
			}
		}

		else if (start.getY() == end.getY()){
			for (int x = start.getX(); x <= end.getX(); x++){
				location.setX(x);
				if (matrix.getObject(location.getX(), location.getY())->getType() == street){
					coordinates.push_back(location);
					Street* ptr = dynamic_cast<Street*>(matrix.getObject(location.getX(), location.getY()));
					if (its->getName() != ptr->getName()){
						output << "Street " << its->getName() << " was supposed to be found on location " << location << " but is not.\n";
						integrity = false;
					}
					if(location.getY() == 0){
						if (matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else if (location.getY() == matrix.getRows()-1){
						if (matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
					else {
						if (matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
						if (matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
							output << "Street " << its->getName() << " on location " << location << " was more than one wide.\n";
							integrity = false;
						}
					}
				}
				else if (matrix.getObject(location.getX(), location.getY())->getType() == crossroad){
					Crossroad* ptr = dynamic_cast<Crossroad*>(matrix.getObject(location.getX(), location.getY()));
					if ((its->getName() != ptr->getStreet1()) && (its->getName() != ptr->getStreet2())){
						output << "Street " << its->getName() << " was supposed to be found on location " << location << " but is not. (as a crossroad)\n";
						integrity = false;
					}
				}
			}
		}
	}


	for (std::list<Crossroad>::iterator itc = crossroads.begin(); itc != crossroads.end(); itc++){
		Coordinate location = itc->getLocation();
		if (matrix.getObject(location.getX(), location.getY()) != &(*itc)){
			output << "Crossroad " << itc->getName() << " was supposed to be found on location " << location << " but is not.\n";
			integrity = false;
		}
		coordinates.push_back(location);
	}



	for (int i = 0; i < coordinates.size(); i++){
		for (int j = i+1; j < coordinates.size(); j++){
			if (coordinates[i] == coordinates[j]){
				output << "There is an overlap at location " << coordinates[i] << ".\n";
				integrity = false;
			}
		}
	}

	if (coordinates.size() != matrix.getRows()*matrix.getColumns()){
		output << "There were empty spots found in the city\n";
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
			output << "Truck with name " << itt->getName() << " was not linked to a base.\n";
			integrity = false;
		}
	}
	return integrity;
}

void City::close(){
	output.close();
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
