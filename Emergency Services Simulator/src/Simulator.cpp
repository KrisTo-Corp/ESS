/*
 * Simulator.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: kristof
 */

#include "Simulator.h"

void simulateCity(City& city) {

	REQUIRE(city.properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update()");

	city.o.print("\nSIMULATION:");
	city.o.print("\n==========\n\n");

	if (!(city.getValidCity())){
		city.o.print("\n\t CITY WAS NOT VALID\n\n");
		return;
	}

	bool finished = false;

	std::cout << "JA" << std::endl;

	/*
	 * Fire
	 */
	// set fire
	CityObjects* ptr;
	ptr = city.setFire();
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	std::string cur = structptr->getLocation().getString();
	std::cout << "FIRECOORD: " << cur << std::endl;

	std::string name = structptr->getName();
	city.o.print(name + " at location " + cur + " started burning.\n");
	std::string hp = doubleToString(structptr->getHP());
	city.o.print("\t It has " + hp + " hitpoints left.\n\n");

	// Find an available firetruck.
	std::list<Firetruck>::iterator it_t;
	std::list<std::pair<int, Firetruck*> > truck_distances;
	for (it_t = city.getTruckList()->begin(); it_t != city.getTruckList()->end(); it_t++) {
		if (it_t->getAvailable()) {
			std::pair<int, Firetruck*> temp(city.calculateDistance(city.getAdjecantStreet(structptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
			truck_distances.push_back(temp);
		}
	}
	truck_distances.sort();
	if (truck_distances.size() != 0){
		Firetruck* rescueTruck = truck_distances.begin()->second;
		rescueTruck->setAvailable(false);
		rescueTruck->setDestination(city.getAdjecantStreet(structptr, rescueTruck->getCoord()));
		rescueTruck->setTarget(structptr);
		rescueTruck->setIsHome(false);
		ptr->setState(beingrescuedF);
	}

	/*
	 * Robbery
	 */

	// Check if there is a robable store.
	std::list<Store>::iterator it_s;
	bool robable = false;
	for (it_s = city.getStoresList()->begin(); it_s != city.getStoresList()->end(); it_s++) {
		std::cout << "LET's SEE: " << it_s->getRobable() << std::endl;
		if (it_s->getState() == normal) {
			std::cout << " HERE" << it_s->getRP() << std::endl;
			robable = true;
		}
	}
	if (robable) {
		// rob store
		Store* storePtr;
		storePtr = city.robStore();
		Coordinate curStore = storePtr->getLocation();
		std::cout << "STORECOORD: " << curStore << std::endl;
		std::string storeName = storePtr->getName();
		city.o.print(storeName + " at location " + curStore.getString() + " has started being robbed.\n");
		std::string rp = doubleToString(storePtr->getRP());
		city.o.print("\t It has " + rp + " robbery points left.\n\n");

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
			rescueCar->setTarget(storePtr);
			rescueCar->setIsHome(false);
			storePtr->setState(beingrescuedR);
		}
	}

	std::cout << "LOOP" << std::endl;
	while (true) {
		finished = true;
		// Random chance to setFire()
		int chance = rand() % 20;
		if (chance == 20) {
			ptr = city.setFire();
			Structures* structptr = dynamic_cast<Structures*>(ptr);
			Coordinate cur = structptr->getLocation();
			std::string name = structptr->getName();
			city.o.print(name + " at location " + cur.getString() + " started burning.\n");
			House* houseptr = dynamic_cast<House*>(structptr);
			std::string hp = doubleToString(houseptr->getHP());
			city.o.print("\t It has " + hp + " hitpoints left.\n\n");

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

		std::cout << "Burn & Rob" << std::endl;

		// Burn and rob
		for (int i = 0; i < city.getMatrix()->getColumns(); i++){
			for (int j = 0; j < city.getMatrix()->getRows(); j++){
				//std::cout << i << " " << j << std::endl;
				ptr = city.getMatrix()->getObject(i, j);
				if (ptr->getState() == burning || ptr->getState() == beingrescuedF) {
					if (ptr->getState() == burning) {
						Structures* newFireStructure = dynamic_cast<Structures*>(ptr);

						// Find an available firetruck.
						std::list<Firetruck>::iterator it_t;
						std::list<std::pair<int, Firetruck*> > truck_distances;
						for (it_t = city.getTruckList()->begin(); it_t != city.getTruckList()->end(); it_t++) {
							if (it_t->getAvailable()) {
								std::pair<int, Firetruck*> temp(city.calculateDistance(city.getAdjecantStreet(newFireStructure, it_t->getCoord()), it_t->getCoord()), &(*it_t));
								truck_distances.push_back(temp);
							}
						}
						truck_distances.sort();
						if (truck_distances.size() != 0){
							Firetruck* rescueTruck = truck_distances.begin()->second;
							rescueTruck->setAvailable(false);
							rescueTruck->setDestination(city.getAdjecantStreet(newFireStructure, rescueTruck->getCoord()));
							rescueTruck->setTarget(newFireStructure);
							rescueTruck->setIsHome(false);
							ptr->setState(beingrescuedF);
						}
					}
					finished = false;
					std::cout << "kaka1" << std::endl;
					std::cout << ptr->getType() << std::endl;
					Structures* houseptr = dynamic_cast<Structures*>(ptr);

					// Casualties
					if (houseptr->getHP() == houseptr->getMaxHp()-5) {

						Casualty cas;
						city.getCasualtyList()->push_back(cas);
						city.o.print("A new casualty has fallen, he has " + intToString(cas.getHP()) + "hp left");

						//find available ambulanceS
						std::list<Ambulance>::iterator it_t;
						std::list<std::pair<int, Ambulance*> > truck_distances;
						for (it_t = city.getAmbulancesList()->begin(); it_t != city.getAmbulancesList()->end(); it_t++) {
							if (it_t->getAvailable()) {
								std::pair<int, Ambulance*> temp(city.calculateDistance(city.getAdjecantStreet(structptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
								truck_distances.push_back(temp);
							}
						}
						truck_distances.sort();
						if (truck_distances.size() != 0){
							Ambulance* rescueTruck = truck_distances.begin()->second;
							rescueTruck->setAvailable(false);
							rescueTruck->setDestination(city.getAdjecantStreet(structptr, rescueTruck->getCoord()));
							rescueTruck->setTarget(structptr);
							rescueTruck->setPassenger(&(*city.getCasualtyList()->end()));
							rescueTruck->setIsHome(false);
						}
					}



					houseptr->decreaseHP();
					double hp = houseptr->getHP();
					if (hp/floor(hp) == 1){
						houseptr->increaseSpreadcounter();
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						city.o.print(name + " at location " + cur.getString() + " is still burning.\n");
						city.o.print("\t It has " + doubleToString(hp) + " hitpoints left.\n\n");
					}

					if (houseptr->getHP() <= 0){
						houseptr->setState(destroyed);
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						city.o.print(name + " at location " + cur.getString() + " is destroyed.\n");
						city.o.print("\t It has " + doubleToString(hp) + " hitpoints left.\n\n");
					}

					// Spread fire.
					Structures* structptr = dynamic_cast<Structures*>(ptr);
					if (structptr->getSpreadcounter() >= 3 && (ptr->getState() == burning || ptr->getState() == beingrescuedF)) {
						city.o.print("spreadcounter = " + doubleToString(structptr->getSpreadcounter()));
						std::cout << "ENTERED" << std::endl;
						structptr->resetSpreadcounter();
						Coordinate newFire = city.getAdjecantBuilding(ptr);
						std::cout << newFire << std::endl;
						if (newFire.getX() != -1 && newFire.getY() != -1) {
							city.setFire(newFire.getX(), newFire.getY());
							city.o.print("Fire has spread and a building on location " + newFire.getString() + " has caught fire.\n");

							CityObjects* newFireBuilding = city.getMatrix()->getObject(newFire.getX(), newFire.getY());
							Structures* newFireStructure = dynamic_cast<Structures*>(newFireBuilding);

							// Find an available firetruck.
							std::list<Firetruck>::iterator it_t;
							std::list<std::pair<int, Firetruck*> > truck_distances;
							for (it_t = city.getTruckList()->begin(); it_t != city.getTruckList()->end(); it_t++) {
								if (it_t->getAvailable()) {
									std::pair<int, Firetruck*> temp(city.calculateDistance(city.getAdjecantStreet(newFireStructure, it_t->getCoord()), it_t->getCoord()), &(*it_t));
									truck_distances.push_back(temp);
								}
							}
							truck_distances.sort();
							if (truck_distances.size() != 0){
								Firetruck* rescueTruck = truck_distances.begin()->second;
								rescueTruck->setAvailable(false);
								rescueTruck->setDestination(city.getAdjecantStreet(newFireStructure, rescueTruck->getCoord()));
								rescueTruck->setTarget(newFireStructure);
								rescueTruck->setIsHome(false);
								newFireBuilding->setState(beingrescuedF);
							}
						}
					}
				}
				else if (ptr->getState() == beingrobbed || ptr->getState() == beingrescuedR) {
					if (ptr->getState() == beingrobbed) {
						Structures* storePtr = dynamic_cast<Structures*>(ptr);

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
							rescueCar->setTarget(storePtr);
							rescueCar->setIsHome(false);
							storePtr->setState(beingrescuedR);
						}
					}

					std::cout << "kaka2" << std::endl;

					finished = false;

					Store* storePtr = dynamic_cast<Store*>(ptr);

					storePtr->decreaseRP();
					double rp = storePtr->getRP();
					if (rp/floor(rp) == 1){
						Coordinate cur = storePtr->getLocation();
						std::string name = storePtr->getName();
						city.o.print(name + " at location " + cur.getString() + " is still burning.\n");
						city.o.print("\t It has " + doubleToString(rp) + " robbery points left.\n\n");
					}

					if (storePtr->getRP() <= 0){
						storePtr->setState(destroyed);
						Coordinate cur = storePtr->getLocation();
						std::string name = storePtr->getName();
						city.o.print(name + " at location " + cur.getString() + " is robbed empty.\n");
						city.o.print("\t It has " + doubleToString(rp) + " robbery points left.\n\n");
					}
				}
				else if (ptr->getState() == repairing){
					std::cout << "kaka3" << std::endl;

					Structures* structptr = dynamic_cast<Structures*>(ptr);
					double hp = structptr->getHP();
					double maxhp = structptr->getMaxHp();
					//std::cout << "HP = " << hp << "\tMAXHP = " << maxhp << std::endl;
					if (hp < maxhp){
						//std::cout << "HP NOT EQUAL" << std::endl;
						structptr->increaseHp();
						if (structptr->getHP()/floor(structptr->getHP()) == 1){
							Coordinate cur = structptr->getLocation();
							std::string name = structptr->getName();
							city.o.print(name + " at location " + cur.getString() + " is repairing.\n");
							city.o.print("\t It has " + doubleToString(structptr->getHP()) + " hitpoints left.\n\n");
						}
					}
				}
			}
		}
		std::cout << "kaka4" << std::endl;


		int i = 0;

		if (city.getTruckList()->size() == 0) {
			city.o.print("There are no firetrucks in this city.\n");
		}
		else if (city.getAmbulancesList()->size() == 0) {
			city.o.print("There are no ambulances in this city.\n");
		}
		else if (city.getPoliceCarsList()->size() == 0) {
			city.o.print("There are no policecars in this city.\n");
		}

		// Decrease HP (casualties)
		std::vector<Casualty>::iterator itc;
		for (itc = city.getCasualtyList()->begin(); itc != city.getCasualtyList()->end(); itc++) {
			if (!(itc->getInCare())) {
				itc->decreaseHP();
				city.o.print("casualty's hp has decreased, he has " + intToString(itc->getHP()) + " hp left");
			}
		}

		// Move
		for (std::list<Firetruck>::iterator it = city.getTruckList()->begin(); it != city.getTruckList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				if (it->getAvailable() == false) {
					Structures* saved = it->getTarget();
					if (saved->getState() == beingrescuedF) {
						saved->setState(repairing);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Firetruck " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and has extinguished the fire and are returning home.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Firetruck " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and saw that the structure was destroyed and are now returning home.\n\n");
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.o.print("Firetruck " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + "\n\n");
						it->setIsHome(true);
						it->setAvailable(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Firetruck " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location ");
				city.o.print(destination.getString() + ". The firetruck is at " + truckStreet->getName() + " on location " + location.getString() + "\n\n\n");
			}
		}

		for (std::list<PoliceCar>::iterator it = city.getPoliceCarsList()->begin(); it != city.getPoliceCarsList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				Coordinate cur_dest = it->getCoord();
				if (it->getAvailable() == false) {
					Structures* saved = it->getTarget();
					if (saved->getState() == beingrescuedR) {
						saved->setState(normal);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Policecar " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and has stopped the robbery and are returning home.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Policecar " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and saw that the store was robbed empty and are now returning home.\n\n");
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.o.print("Policecar " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + "\n\n");
						it->setIsHome(true);

					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Policecar " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location ");
				city.o.print(destination.getString() + ". The policecar is at " + truckStreet->getName() + " on location " + location.getString() + "\n\n\n");
			}
		}

		for (std::list<Ambulance>::iterator it = city.getAmbulancesList()->begin(); it != city.getAmbulancesList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				Coordinate cur_dest = it->getCoord();
				if (it->getAvailable() == false) {
					Casualty* passenger = it->getPassenger();
					if (saved->getState() == beingrescuedR) {
						saved->setState(normal);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Policecar " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and has stopped the robbery and are returning home.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Policecar " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and saw that the store was robbed empty and are now returning home.\n\n");
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.o.print("Policecar " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + "\n\n");
						it->setIsHome(true);

					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Policecar " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location ");
				city.o.print(destination.getString() + ". The policecar is at " + truckStreet->getName() + " on location " + location.getString() + "\n\n\n");
			}
		}

		if ((i == city.getAmountTrucks()+city.getAmountCars()) && finished) {
			city.o.print("\n================================================================================================================================");
			return;
		}
		else {
			city.o.print("\n--------------------------------------------------------------------------------------------------------------------------------\n\n");
		}
	}
}

void simulateCity_Test(City& city, Coordinate c1, Coordinate c2) {

	REQUIRE(city.properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update()");

	city.o.print("\nSIMULATION:");
	city.o.print("\n==========\n\n");

	if (!(city.getValidCity())){
		city.o.print("\n\t CITY WAS NOT VALID\n\n");
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
	city.o.print(name + " at location " + cur.getString() + " started burning.\n");
	House* houseptr = dynamic_cast<House*>(structptr);
	double hp = houseptr->getHP();
	city.o.print("\t It has " + doubleToString(hp) + " hitpoints left.\n\n");

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
			city.o.print(name + " at location " + cur.getString() + " started burning.\n");
			House* houseptr = dynamic_cast<House*>(structptr);
			double hp = houseptr->getHP();
			city.o.print("\t It has " + doubleToString(hp) + " hitpoints left.\n\n");

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
						city.o.print(name + " at location " + cur.getString() + " is still burning.\n");
						city.o.print("\t It has " + doubleToString(hp) + " hitpoints left.\n\n");
					}

					if (houseptr->getHP() <= 0){
						houseptr->setState(destroyed);
						Coordinate cur = houseptr->getLocation();
						std::string name = houseptr->getName();
						city.o.print(name + " at location " + cur.getString() + " is destroyed.\n");
						city.o.print("\t It has " + doubleToString(hp) + " hitpoints left.\n\n");
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
						city.o.print("Firetruck " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and has extinguished the fire and are returning home.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Firetruck " + it->getName() + " has reached its destination ");
						city.o.print(" at location " + destination.getString() + " and saw that the structure was destroyed and are now returning home.\n");
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.o.print("Firetruck " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + "\n\n");
						it->setIsHome(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Firetruck " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location ");
				city.o.print(destination.getString() + ". The firetruck is at " + truckStreet->getName() + " on location " + location.getString() + "\n\n");
			}
		}

		if (i == city.getAmountTrucks()) {
			finished = true;
			city.o.print("\n================================================================================================================================");
		}
		else {
			city.o.print("\n--------------------------------------------------------------------------------------------------------------------------------\n\n");
		}
		loopcounter++;
	}
}

