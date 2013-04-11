/*
 * Simulator.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: kristof
 */

#include "Simulator.h"

void simulateCity(City& city) {

	REQUIRE(city.properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update()");

	city.output << "\nSIMULATION:";
	city.output << "\n==========\n\n";

	if (!(city.getValidCity())){
		city.output << "\n\t CITY WAS NOT VALID\n\n";
		return;
	}

	bool finished = false;

	/*
	 * Fire
	 */
	// set fire
	CityObjects* ptr;
	ptr = city.setFire();
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	Coordinate cur = structptr->getLocation();
	std::string name = structptr->getName();
	city.output << name << " at location " << cur << " started burning." << std::endl;
	House* houseptr = dynamic_cast<House*>(structptr);
	double hp = houseptr->getHP();
	city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

	// Find an available firetruck.
	std::list<Firetruck>::iterator it_t;
	std::list<std::pair<int, Firetruck*> > truck_distances;
	for (it_t = city.getTruckList()->begin(); it_t != city.getTruckList()->end(); it_t++) {
		if (it_t->getAvailable()) {
			std::pair<int, Firetruck*> temp(city.calculateDistance(city.getAdjecantStreet(houseptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
			truck_distances.push_back(temp);
		}
	}
	truck_distances.sort();
	if (truck_distances.size() != 0){
		Firetruck* rescueTruck = truck_distances.begin()->second;
		rescueTruck->setAvailable(false);
		rescueTruck->setDestination(city.getAdjecantStreet(houseptr, rescueTruck->getCoord()));
		rescueTruck->setTarget(houseptr);
		rescueTruck->setIsHome(false);
	}

	/*
	 * Robbery
	 */
	// rob store
	Store* storePtr;
	storePtr = city.robStore();
	Coordinate curStore = storePtr->getLocation();
	std::string storeName = storePtr->getName();
	city.output << storeName << " at location " << curStore << " has started being robbed." << std::endl;
	double rp = storePtr->getRP();
	city.output << "\t It has " << rp << " robbery points left." << std::endl << std::endl;

	// Find an available police car.
	std::list<PoliceCar>::iterator it_pc;
	std::list<std::pair<int, PoliceCar*> > car_distances;
	for (it_pc = city.getPoliceCarsList()->begin(); it_pc != city.getPoliceCarsList()->end(); it_pc++) {
		if (it_pc->getAvailable()) {
			std::pair<int, PoliceCar*> temp(city.calculateDistance(city.getAdjecantStreet(storePtr, it_pc->getCoord()), it_pc->getCoord()), &(*it_pc));
			car_distances.push_back(temp);
		}
	}
	car_distances.sort();
	if (car_distances.size() != 0){
		PoliceCar* rescueCar = car_distances.begin()->second;
		rescueCar->setAvailable(false);
		rescueCar->setDestination(city.getAdjecantStreet(storePtr, rescueCar->getCoord()));
		rescueCar->setTarget(houseptr);
		rescueCar->setIsHome(false);
	}

	while (!finished) {
		// Random chance to setFire()
		int chance = rand() % 20;
		if (chance == 20) {
			ptr = city.setFire();
			Structures* structptr = dynamic_cast<Structures*>(ptr);
			Coordinate cur = structptr->getLocation();
			std::string name = structptr->getName();
			city.output << name << " at location " << cur << " started burning." << std::endl;
			House* houseptr = dynamic_cast<House*>(structptr);
			double hp = houseptr->getHP();
			city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

			// Find an available firetruck.
			std::list<Firetruck>::iterator it_t;
			std::list<std::pair<int, Firetruck*> > truck_distances;
			for (it_t = city.getTruckList()->begin(); it_t != city.getTruckList()->end(); it_t++) {
				if (it_t->getAvailable()) {
					std::pair<int, Firetruck*> temp(city.calculateDistance(city.getAdjecantStreet(houseptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
					truck_distances.push_back(temp);
				}
			}
			truck_distances.sort();
			if (truck_distances.size() != 0){
				Firetruck* rescueTruck = truck_distances.begin()->second;
				rescueTruck->setAvailable(false);
				rescueTruck->setDestination(city.getAdjecantStreet(houseptr, rescueTruck->getCoord()));
				rescueTruck->setTarget(houseptr);
				rescueTruck->setIsHome(false);
			}
		}

		// Burn and rob
		for (int i = 0; i < city.getMatrix()->getColumns(); i++){
			for (int j = 0; j < city.getMatrix()->getRows(); j++){
				ptr = city.getMatrix()->getObject(i, j);

				if (ptr->getState() == burning){
					finished = false;

					House* houseptr = dynamic_cast<House*>(ptr);

					houseptr->decreaseHP();
					double hp = houseptr->getHP();
					if (hp/floor(hp) == 1){
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						city.output << name << " at location " << cur << " is still burning." << std::endl;
						city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;
					}

					if (houseptr->getHP() <= 0){
						houseptr->setState(destroyed);
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						city.output << name << " at location " << cur << " is destroyed." << std::endl;
						city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;
					}
				}
			}
		}

		int i = 0;

		if (city.getTruckList()->size() == 0) {
			city.output << "There are no firetrucks in this city." << std::endl;
		}
		else if (city.getAmbulancesList()->size() == 0) {
			city.output << "There are no ambulances in this city." << std::endl;
		}
		else if (city.getPoliceCarsList()->size() == 0) {
			city.output << "There are no policecars in this city." << std::endl;
		}

		// Move
		for (std::list<Firetruck>::iterator it = city.getTruckList()->begin(); it != city.getTruckList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				if (it->getAvailable() == false) {
					Structures* saved = it->getTarget();
					if (saved->getState() == burning) {
						saved->setState(normal);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.output << "Firetruck " << it->getName() << " has reached its destination ";
						city.output << " at location " << destination << " and has extinguished the fire and are returning home.\n" << std::endl;
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.output << "Firetruck " << it->getName() << " has reached its destination ";
						city.output << " at location " << destination << " and saw that the structure was destroyed and are now returning home.\n" << std::endl;
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.output << "Firetruck " << it->getName() << " has arrived at its base " << it->getBaseptr()->getName() << "\n\n";
						it->setIsHome(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.output << "Firetruck " << it->getName() << " is on its way to " << it->getTarget()->getName() << " on location ";
				city.output << destination << ". The firetruck is at " << truckStreet->getName() << " on location " << location << std::endl << std::endl;
			}
		}

		if (i == city.getAmountTrucks()) {
			finished = true;
			city.output << "\n================================================================================================================================";
		}
		else {
			city.output << "\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
		}
	}
}

void simulateCity_Test(City& city, Coordinate c1, Coordinate c2) {

	REQUIRE(city.properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update()");

	city.output << "\nSIMULATION:";
	city.output << "\n==========\n\n";

	if (!(city.getValidCity())){
		city.output << "\n\t CITY WAS NOT VALID\n\n";
		return;
	}

	bool finished = false;

	/*
	 * Fire
	 */
	// Set fire
	CityObjects* ptr;
	ptr = city.setFire(c1.getX(), c1.getY());
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	Coordinate cur = structptr->getLocation();
	std::string name = structptr->getName();
	city.output << name << " at location " << cur << " started burning." << std::endl;
	House* houseptr = dynamic_cast<House*>(structptr);
	double hp = houseptr->getHP();
	city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

	// Find an available firetruck.
	std::list<Firetruck>::iterator it_t;
	std::list<std::pair<int, Firetruck*> > truck_distances;
	for (it_t = city.getTruckList()->begin(); it_t != city.getTruckList()->end(); it_t++) {
		if (it_t->getAvailable()) {
			std::pair<int, Firetruck*> temp(city.calculateDistance(city.getAdjecantStreet(houseptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
			truck_distances.push_back(temp);
		}
	}
	truck_distances.sort();
	if (truck_distances.size() != 0){
		Firetruck* rescueTruck = truck_distances.begin()->second;
		rescueTruck->setAvailable(false);
		rescueTruck->setDestination(city.getAdjecantStreet(houseptr, rescueTruck->getCoord()));
		rescueTruck->setTarget(houseptr);
		rescueTruck->setIsHome(false);
	}

	/*
	 * Robbery
	 */
	// rob store
	//Store* storePtr;
	//storePtr = city.robStore();

	int loopcounter = 0;

	while (!finished) {
		if (loopcounter == 5) {
			ptr = city.setFire(c2.getX(), c2.getY());
			Structures* structptr = dynamic_cast<Structures*>(ptr);
			Coordinate cur = structptr->getLocation();
			std::string name = structptr->getName();
			city.output << name << " at location " << cur << " started burning." << std::endl;
			House* houseptr = dynamic_cast<House*>(structptr);
			double hp = houseptr->getHP();
			city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;

			// Find an available firetruck.
			std::list<Firetruck>::iterator it_t;
			Firetruck* rescueTruck;
			std::list<std::pair<int, Firetruck*> > truck_distances;
			for (it_t = city.getTruckList()->begin(); it_t != city.getTruckList()->end(); it_t++) {
				if (it_t->getAvailable()) {
					std::pair<int, Firetruck*> temp(city.calculateDistance(city.getAdjecantStreet(houseptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
					truck_distances.push_back(temp);
				}
			}
			truck_distances.sort();
			if (truck_distances.size() != 0){
				Firetruck* rescueTruck = truck_distances.begin()->second;
				rescueTruck->setAvailable(false);
				rescueTruck->setDestination(city.getAdjecantStreet(houseptr, rescueTruck->getCoord()));
				rescueTruck->setTarget(houseptr);
				rescueTruck->setIsHome(false);
			}
		}

		// Burn
		for (int i = 0; i < city.getMatrix()->getColumns(); i++){
			for (int j = 0; j < city.getMatrix()->getRows(); j++){
				ptr = city.getMatrix()->getObject(i, j);

				if (ptr->getState() == burning){
					finished = false;

					House* houseptr = dynamic_cast<House*>(ptr);

					houseptr->decreaseHP();
					double hp = houseptr->getHP();
					if (hp/floor(hp) == 1){
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						city.output << name << " at location " << cur << " is still burning." << std::endl;
						city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;
					}

					if (houseptr->getHP() <= 0){
						houseptr->setState(destroyed);
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						city.output << name << " at location " << cur << " is destroyed." << std::endl;
						city.output << "\t It has " << hp << " hitpoints left." << std::endl << std::endl;
					}
				}
			}
		}

		int i = 0;

		// Move
		for (std::list<Firetruck>::iterator it = city.getTruckList()->begin(); it != city.getTruckList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				if (it->getAvailable() == false) {
					Structures* saved = it->getTarget();
					if (saved->getState() == burning) {
						saved->setState(normal);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.output << "Firetruck " << it->getName() << " has reached its destination ";
						city.output << " at location " << destination << " and has extinguished the fire and are returning home.\n" << std::endl;
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.output << "Firetruck " << it->getName() << " has reached its destination ";
						city.output << " at location " << destination << " and saw that the structure was destroyed and are now returning home.\n" << std::endl;
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.output << "Firetruck " << it->getName() << " has arrived at its base " << it->getBaseptr()->getName() << "\n\n";
						it->setIsHome(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.output << "Firetruck " << it->getName() << " is on its way to " << it->getTarget()->getName() << " on location ";
				city.output << destination << ". The firetruck is at " << truckStreet->getName() << " on location " << location << std::endl << std::endl;
			}
		}

		if (i == city.getAmountTrucks()) {
			finished = true;
			city.output << "\n================================================================================================================================";
		}
		else {
			city.output << "\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
		}
		loopcounter++;
	}
}
