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

City::City() : o(std::cout, false){
	validCity = false;
	_initCheck = this;
}

City::City(const std::string filename, std::ostream& stream, std::string vehiclesXML, bool html) : o(stream, html) {

	validCity = true;
	_initCheck = this;

	o.print("\t\t\t\t\t\t\t\tEMERGENCY SERVICES SIMULATION \n");
	o.print("\t\t\t\t\t\t\t\t============================= \n\n");

	XmlParser parser(this);
	if (vehiclesXML != "empty") {
		parser.parseCity(vehiclesXML);
	}
	parser.parseCity(filename);

	std::pair<int, int> maxCoords =	parser.getMaxValues();

	if(maxCoords.first == -1 && maxCoords.second == -1){
		o.print("ERROR: .XML CONTAINED SYNTAX ERRORS !\n\n");
		validCity = false;
		return;
	}

	else if(maxCoords.first == -2 && maxCoords.second == -2){
		o.print("ERROR: THERE WAS NO ROOT FOUND IN THE XMLFILE !\n\n");
		validCity = false;
		return;
	}

	else if(maxCoords.first == -3 && maxCoords.second == -3){
		o.print("ERROR: THERE WAS FOUND AN OBJECT THAT'S NOT SUPPORTED !\n\n");
		validCity = false;
		return;
	}

	matrix = Matrix(maxCoords.second + 1, maxCoords.first +1);

	link_vehicles_to_bases();

	matrix.addHouses(houses);
	matrix.addFiredeps(departments);
	crossroads = matrix.addStreets(streets);
	matrix.addCrossroads(crossroads);
	matrix.addStores(stores);
	matrix.addHospitals(hospitals);
	matrix.addPolStations(poliStats);

	//o.print(matrix << "\n");
	matrix.printMatrix(o);

	o.print("\nINTEGRITYCHECK: \n");
	o.print("===============\n");
	if (!(integrityCheck())){
		validCity = false;
		return;
	}
	else {
		o.print("\tPASSED\n\n");
	}


	ENSURE(properlyInitialized(), "Object 'City' was not properly initialized.");
}


City::~City()
{
	std::vector<Casualty*>::iterator it;
	for (it = casualties.begin(); it != casualties.end(); it++) {
		delete (*it);
	}
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

int City::getAmountAmbulances(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountAmbulances()");

	return ambulances.size();
}

int City::getAmountCars(){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmountCars()");

	return policecars.size();
}

std::vector<Casualty*>* City::getCasualtyList() {
	return &casualties;
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

void City::link_vehicles_to_bases() {
	std::list<PoliceCar>::iterator it_p;
	std::list<PoliceStation>::iterator it_pstation;
	std::list<Ambulance>::iterator it_a;
	std::list<Hospital>::iterator it_hosp;
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

	for (it_a = ambulances.begin(); it_a != ambulances.end(); it_a++) {
		Ambulance* ambPtr = &(*it_a);
		std::string basename = ambPtr->getBasename();
		for (it_hosp = hospitals.begin(); it_hosp != hospitals.end(); it_hosp++) {
			Hospital* hosPtr = &(*it_hosp);
			std::string hosp_name = hosPtr->getName();
			if (basename == hosp_name) {
				// Add truck to the fire department.
				hosPtr->addAmbulance(ambPtr);
				// Set values in Firetruck
				ambPtr->setCoord(hosPtr->getEntrance());
				ambPtr->linkBase(hosPtr);
				ambPtr->setDestination(hosPtr->getEntrance());
			}
		}
		if (ambPtr->getBaseptr() == NULL){
			continue;
		}
	}

	for (it_p = policecars.begin(); it_p != policecars.end(); it_p++) {
		PoliceCar* carPtr = &(*it_p);
		std::string basename = carPtr->getBasename();
		for (it_pstation = poliStats.begin(); it_pstation != poliStats.end(); it_pstation++) {
			PoliceStation* polPtr = &(*it_pstation);
			std::string pol_name = polPtr->getName();
			if (basename == pol_name) {
				// Add truck to the fire department.
				polPtr->addCar(carPtr);
				// Set values in Firetruck
				carPtr->setCoord(polPtr->getEntrance());
				carPtr->linkBase(polPtr);
				carPtr->setDestination(polPtr->getEntrance());
			}
		}
		if (carPtr->getBaseptr() == NULL){
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
	int loops = 0;

	while (!succes){

		int random_y = rand()% matrix.getRows();
		int random_x = rand()% matrix.getColumns();


		ptr = matrix.getObject(random_x, random_y);

		if (ptr->getState() == normal || ptr->getState() == repairing){
			succes = true;
		}
		if (loops == 100){
			return NULL;
		}
		loops++;
	}

	ptr->setState(burning);

	ENSURE(ptr->getState() == burning, "setFire() did not correctly set fire to a house.");

	return ptr;
}

Store* City::robStore() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling robStore()");

	bool success = false;
	Store* ptr;
	int loops = 0;

	while (!success) {
		std::list<Store>::iterator it = stores.begin();
		int randomInt = rand()% stores.size();
		for (int i = 0; i < randomInt; i++) {
			it++;
		}

		ptr = &(*it);
		if (ptr->getState() == normal) {
			success = true;
		}
		if (loops == 100){
			return NULL;
		}
		loops++;
	}

	ptr->setState(beingrobbed);

	ENSURE(ptr->getState() == beingrobbed, "robStore() did not cause a robbery.");

	return ptr;
}

Store* City::robStore(int x, int y){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling robStore(int, int)");

	CityObjects* ptr;
	ptr = matrix.getObject(x, y);
	Store* storeptr = dynamic_cast<Store*>(ptr);
	if (storeptr->getState() != normal || storeptr->getType() != store){
		return NULL;
	}

	storeptr->setState(beingrobbed);

	ENSURE(storeptr->getState() == beingrobbed, "setFire() did not correctly set fire to the given house.");

	return storeptr;
}

CityObjects* City::setFire(int x, int y){
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling setFire()");

	bool succes = false;
	CityObjects* ptr;

	ptr = matrix.getObject(x, y);

	if (ptr->getState() == normal || ptr->getState() == repairing){
		succes = true;
	}

	ptr->setState(burning);

	ENSURE(ptr->getState() == burning, "setFire() did not correctly set fire to the given house.");

	return ptr;
}

Coordinate City::getAdjecantBuilding(CityObjects* building) {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAdjecantBuilding(CityObjects*)");

	Structures* ptr = dynamic_cast<Structures*>(building);
	std::vector<Coordinate> coordinates;
	Coordinate location;

	for (int x = 0; x < ptr->getWidth(); x++){
		for (int y = 0; y < ptr->getLength(); y++){
			location = ptr->getLocation();
			location.setX(location.getX()+x);
			location.setY(location.getY()-y);

			CityObjects* obj = matrix.getObject(location.getX(), location.getY()+1);
			if (location.getY() < matrix.getRows()-1) {
				if (obj == NULL) {
					continue;
				}
				else if(obj->getType() != street && obj->getType() != crossroad && obj != building && obj->getState() == normal){
					return (Coordinate(location.getX(), location.getY()+1));
				}
			}

			obj = matrix.getObject(location.getX(), location.getY()-1);
			if (location.getY() > 0){
				if ( obj == NULL) {
					continue;
				}
				else if(obj->getType() != street && obj->getType() != crossroad && obj != building && obj->getState() == normal){
					return (Coordinate(location.getX(), location.getY()-1));
				}
			}

			obj = matrix.getObject(location.getX()+1, location.getY());
			if (location.getX() < matrix.getColumns()-1){
				if (obj == NULL) {
					continue;
				}
				else if (obj->getType() != street && obj->getType() != crossroad && obj != building && obj->getState() == normal){
					return (Coordinate(location.getX()+1, location.getY()));
				}
			}

			obj = matrix.getObject(location.getX()-1, location.getY());
			if (location.getX() > 0){
				if (obj == NULL) {
					continue;
				}
				else if(obj->getType() != street && obj->getType() != crossroad && obj != building && obj->getState() == normal){
					return (Coordinate(location.getX()-1, location.getY()));
				}
			}
		}
	}
	return (Coordinate(-1, -1));
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

void City::driveTruck(Vehicles* rescueTruck) {
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
			std::string houselocation = houseptr->getLocation().getString();
			o.print("\tERROR: House at location " + houselocation + " doesn't have a street linked to it.\n");
			integrity = false;
		}
		for (int x = 0; x < 2; x++){
			for (int y = 0; y < 2; y++){
				location = ith->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*ith)){
					std::string houselocation = ith->getLocation().getString();
					o.print("\tERROR: House at location " + houselocation + " is supposed to be at " + location.getString() + " but is not.\n");
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
			std::string deplocation = depptr->getLocation().getString();
			o.print("\tERROR: Department at location " + deplocation + " doesn't have a street linked to it.\n");
			integrity = false;
		}
		for (int x = 0; x < 4; x++){
			for (int y = 0; y < 4; y++){
				location = itd->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*itd)){
					std::string deplocation = itd->getLocation().getString();
					o.print("\tERROR: Department at location " + deplocation + " is supposed to be at " + location.getString() + " but is not.\n");
					integrity = false;
				}
				coordinates.push_back(location);
			}
		}
	}

	for (std::list<Store>::iterator itd = stores.begin(); itd != stores.end(); itd++){
		Coordinate location;
		CityObjects* ptr = &(*itd);
		Store* storeptr = dynamic_cast<Store*>(ptr);
		if (getAdjecantStreet(ptr, Coordinate(0, 0)) == Coordinate(-1, -1)){
			std::string storeLocation = storeptr->getLocation().getString();
			o.print("\tERROR: Store at location " + storeLocation + " doesn't have a street linked to it.\n");
			integrity = false;
		}
		for (int x = 0; x < storeptr->getWidth(); x++){
			for (int y = 0; y < storeptr->getLength(); y++){
				location = itd->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*itd)){
					std::string storeLocation = itd->getLocation().getString();
					o.print("\tERROR: Store at location " + storeLocation + " is supposed to be at " + location.getString() + " but is not.\n");
					integrity = false;
				}
				coordinates.push_back(location);
			}
		}
	}

	for (std::list<Hospital>::iterator itd = hospitals.begin(); itd != hospitals.end(); itd++){
		Coordinate location;
		CityObjects* ptr = &(*itd);
		Hospital* hospitalPtr = dynamic_cast<Hospital*>(ptr);
		if (getAdjecantStreet(ptr, Coordinate(0, 0)) == Coordinate(-1, -1)){
			std::string hospitalLocation = hospitalPtr->getLocation().getString();
			o.print("\tERROR: Hospital at location " + hospitalLocation + " doesn't have a street linked to it.\n");
			integrity = false;
		}
		for (int x = 0; x < hospitalPtr->getWidth(); x++){
			for (int y = 0; y < hospitalPtr->getLength(); y++){
				location = itd->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*itd)){
					std::string storeLocation = itd->getLocation().getString();
					o.print("\tERROR: Hospital at location " + storeLocation + " is supposed to be at " + location.getString() + " but is not.\n");
					integrity = false;
				}
				coordinates.push_back(location);
			}
		}
	}

	for (std::list<PoliceStation>::iterator itd = poliStats.begin(); itd != poliStats.end(); itd++){
		Coordinate location;
		CityObjects* ptr = &(*itd);
		PoliceStation* polPtr = dynamic_cast<PoliceStation*>(ptr);
		if (getAdjecantStreet(ptr, Coordinate(0, 0)) == Coordinate(-1, -1)){
			std::string polLocation = polPtr->getLocation().getString();
			o.print("\tERROR: Policestation at location " + polLocation + " doesn't have a street linked to it.\n");
			integrity = false;
		}
		for (int x = 0; x < polPtr->getWidth(); x++){
			for (int y = 0; y < polPtr->getLength(); y++){
				location = itd->getLocation();
				location.setX(location.getX()+x);
				location.setY(location.getY()-y);
				if (matrix.getObject(location.getX(), location.getY()) != &(*itd)){
					std::string polLocation = itd->getLocation().getString();
					o.print("\tERROR: Policestation at location " + polLocation + " is supposed to be at " + location.getString() + " but is not.\n");
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
						o.print("\tERROR: Street " + its->getName() + " was supposed to be found on location " + location.getString() + " but is not.\n");
						integrity = false;
					}
					if(location.getX() == 0){
						if (matrix.getObject(location.getX()+1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()+1, location.getY())->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
					}
					else if (location.getX() == matrix.getColumns()-1){
						if (matrix.getObject(location.getX()-1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()-1, location.getY())->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
					}
					else {
						if (matrix.getObject(location.getX()-1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()-1, location.getY())->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
						if (matrix.getObject(location.getX()+1, location.getY()) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX()+1, location.getY())->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
					}
				}
				else if (matrix.getObject(location.getX(), location.getY())->getType() == crossroad){
					Crossroad* ptr = dynamic_cast<Crossroad*>(matrix.getObject(location.getX(), location.getY()));
					if ((its->getName() != ptr->getStreet1()) && (its->getName() != ptr->getStreet2())){
						o.print("\tERROR: Street " + its->getName() + " was supposed to be found on location " + location.getString() + " but is not. (as a crossroad)\n");
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
						o.print("\tERROR: Street " + its->getName() + " was supposed to be found on location " + location.getString() + " but is not.\n");
						integrity = false;
					}
					if(location.getY() == 0){
						if (matrix.getObject(location.getX(), location.getY()+1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
					}
					else if (location.getY() == matrix.getRows()-1){
						if (matrix.getObject(location.getX(), location.getY()-1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
					}
					else {
						if (matrix.getObject(location.getX(), location.getY()-1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()-1)->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
						if (matrix.getObject(location.getX(), location.getY()+1) == NULL) {
							continue;
						}
						if (matrix.getObject(location.getX(), location.getY()+1)->getType() == street){
							o.print("\tERROR: Street " + its->getName() + " on location " + location.getString() + " was more than one wide.\n");
							integrity = false;
						}
					}
				}
				else if (matrix.getObject(location.getX(), location.getY())->getType() == crossroad){
					Crossroad* ptr = dynamic_cast<Crossroad*>(matrix.getObject(location.getX(), location.getY()));
					if ((its->getName() != ptr->getStreet1()) && (its->getName() != ptr->getStreet2())){
						o.print("\tERROR: Street " + its->getName() + " was supposed to be found on location " + location.getString() + " but is not. (as a crossroad)\n");
						integrity = false;
					}
				}
			}
		}
	}

	for (std::list<Crossroad>::iterator itc = crossroads.begin(); itc != crossroads.end(); itc++){
		Coordinate location = itc->getLocation();
		if (matrix.getObject(location.getX(), location.getY()) != &(*itc)){
			o.print("\tERROR: Crossroad " + itc->getName() + " was supposed to be found on location " + location.getString() + " but is not.\n");
			integrity = false;
		}
		coordinates.push_back(location);
	}



	for (int i = 0; i < coordinates.size(); i++){
		for (int j = i+1; j < coordinates.size(); j++){
			if (coordinates[i] == coordinates[j]){
				o.print("\tERROR: Overlap found at location " + coordinates[i].getString() + ".\n");
				integrity = false;
			}
		}
	}

	if (coordinates.size() != matrix.getRows()*matrix.getColumns()){
		o.print("\tERROR: Empty spots were found in the city.\n");
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
			o.print("\tERROR: Truck with name " + itt->getName() + " was not linked to a base.\n");
			integrity = false;
		}
	}
	return integrity;
}

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

std::list<Store>* City::getStoresList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getStoresList()");

	return &stores;
}

std::list<Hospital>* City::getHospitalsList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getHospitalsList()");

	return &hospitals;
}

std::list<PoliceStation>* City::getPoliStatsList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getPolStatsList()");

	return &poliStats;
}

std::list<PoliceCar>* City::getPoliceCarsList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getPolStatsList()");

	return &policecars;
}
std::list<Ambulance>* City::getAmbulancesList() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getAmbulancesList()");

	return &ambulances;
}

Matrix* City::getMatrix() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getMatrix()");

	return &matrix;
}

bool City::getValidCity() {
	REQUIRE(properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling getValidCity()");

	return validCity;
}



// ===========================
//		TESTS FOR CITY
// ===========================

// TEST THE CITY CONSTRUCTOR
TEST_F(CityTest, Constructor){
	std::ofstream stream("Output files/unusedOutput.txt");
	City city("XML Files/stad.xml", stream);
	EXPECT_TRUE(city.properlyInitialized());
	EXPECT_EQ(50, city.getAmountHouses());
	EXPECT_EQ(1, city.getAmountDepartments());
	EXPECT_EQ(8, city.getAmountStreets());
	EXPECT_EQ(16, city.getAmountCrossroads());
	EXPECT_EQ(2, city.getAmountTrucks());
	stream.close();
}

// TEST THE SETFIRE FUNCTION
TEST_F(CityTest, SetFire){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	CityObjects* burning_object = c.setFire(9, 12);
	EXPECT_EQ(burning, burning_object->getState());
	CityObjects* object = c.getObject(9, 12);
	EXPECT_EQ(burning, object->getState());
}

// TEST THE GET ADJECANTSTREET FUNCTION
TEST_F(CityTest, AdjecantStreet){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	CityObjects* object = c.getObject(3, 13);
	EXPECT_EQ(Coordinate(4, 15), c.getAdjecantStreet(object, Coordinate(8, 10)));
	object = c.getObject(20, 3);
	EXPECT_EQ(Coordinate(19, 5), c.getAdjecantStreet(object, Coordinate(8, 10)));
	object = c.getObject(8, 12);
	EXPECT_EQ(Coordinate(9, 10), c.getAdjecantStreet(object, Coordinate(16, 10)));
}

// TEST THE CHECK ORIENTATION FUNCTION
TEST_F(CityTest, CheckOrientation){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 0)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 0)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 0)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 0)));

	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 5)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 5)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 5)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 5)));

	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 10)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 10)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 10)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 10)));

	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(3, 15)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(11, 15)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(14, 15)));
	EXPECT_EQ("horizontal", c.checkOrientation(Coordinate(19, 15)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(0, 2)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(7, 2)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(16, 2)));

	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 13)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 8)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 6)));
	EXPECT_EQ("vertical", c.checkOrientation(Coordinate(21, 2)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 0)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 0)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 0)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 0)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 5)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 5)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 5)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 5)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 10)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 10)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 10)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 10)));

	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(0, 15)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(7, 15)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(16, 15)));
	EXPECT_EQ("crossroad", c.checkOrientation(Coordinate(21, 15)));
	stream.close();
}

// TEST THE CLOSEST CROSSROAD FUNCTION
TEST_F(CityTest, ClosestCrossroad){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);

	EXPECT_EQ(Coordinate(0, 10), c.closestCrossroad(Coordinate(3, 10)).getLocation());
	EXPECT_EQ(Coordinate(7, 5), c.closestCrossroad(Coordinate(11, 5)).getLocation());
	EXPECT_EQ(Coordinate(0, 0), c.closestCrossroad(Coordinate(0, 2)).getLocation());
	EXPECT_EQ(Coordinate(16, 15), c.closestCrossroad(Coordinate(12, 15)).getLocation());
	EXPECT_EQ(Coordinate(7, 10), c.closestCrossroad(Coordinate(7, 10)).getLocation());
	stream.close();
}

// TEST THE CLOSEST CORRECT CROSSROAD
TEST_F(CityTest, ClosestCorrectCrossroad){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	CityObjects* ptr = c.getObject(7,12);
	Street* streetptr = dynamic_cast<Street*>(ptr);
	EXPECT_EQ(Coordinate(7, 15), c.closestCorrectCrossroad(Coordinate(12, 15), streetptr).getLocation());
	stream.close();
}

// TEST CALCULATE DISTANCE
TEST_F(CityTest, CalculateDistance){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	EXPECT_EQ(23, c.calculateDistance(Coordinate(0, 5), Coordinate(21, 15)));
	EXPECT_EQ(15, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 15)));
	EXPECT_EQ(25, c.calculateDistance(Coordinate(0, 15), Coordinate(21, 0)));
	EXPECT_EQ(0, c.calculateDistance(Coordinate(9, 0), Coordinate(9, 0)));
	stream.close();
}
// TEST DRIVE TRUCK
TEST_F(CityTest, DriveTruck){
	std::ofstream stream("Output files/unusedOutput.txt");
	City c("XML Files/stad.xml", stream);
	Firetruck* ptr = c.getTruck(0);
	ptr->setDestination(Coordinate(7, 13));
	EXPECT_EQ(Coordinate(8, 10), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 10), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 11), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 12), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 13), ptr->getCoord());
	c.driveTruck(ptr);
	EXPECT_EQ(Coordinate(7, 13), ptr->getCoord());
	stream.close();
}

