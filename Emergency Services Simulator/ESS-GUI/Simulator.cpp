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
	city.o.print("\n===========\n\n");

	if (!(city.getValidCity())){
		city.o.print("\n\t CITY WAS NOT VALID\n\n");
		return;
	}

	bool finished = false;
	// ============================
	// 		   SETTING FIRE
	// ============================
	CityObjects* ptr;
	ptr = city.setFire();
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	std::string cur = structptr->getLocation().getString();

	std::string name = structptr->getName();
	std::string hp = doubleToString(structptr->getHP());
	city.o.print(name + " at location " + cur + " started burning.\n\tIt has " + hp + " hitpoints left.\n\n");

	// ===========================
	//	   FIND CLOSEST TRUCK
	// ===========================
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
	// =============================
	//	 CHECK FOR ROBBABLE STORE
	// =============================
	std::list<Store>::iterator it_s;
	bool robable = false;
	for (it_s = city.getStoresList()->begin(); it_s != city.getStoresList()->end(); it_s++) {
		if (it_s->getState() == normal) {
			robable = true;
		}
	}
	// =============================
	//	 		ROB STORE
	// =============================
	if (robable) {
		Store* storePtr;
		storePtr = city.robStore();
		Coordinate curStore = storePtr->getLocation();
		std::string storeName = storePtr->getName();
		std::string rp = doubleToString(storePtr->getRP());
		city.o.print(storeName + " at location " + curStore.getString() + " has started being robbed.\n\tIt has " + rp + " robbery points left.\n\n");
		// ===============================
		//	FIND AN AVAILABLE POLICECAR
		// ===============================
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
	// ======================
	// 		WHILE LOOP
	// ======================
	while (true) {
		finished = true;
		int random_chance = rand() % 20;
		if (random_chance == 10) {
			// ============================
			// 		   SETTING FIRE
			// ============================
			ptr = city.setFire();
			if (ptr != NULL){
				Structures* structptr = dynamic_cast<Structures*>(ptr);
				Coordinate cur = structptr->getLocation();
				std::string name = structptr->getName();
				std::string hp = doubleToString(structptr->getHP());
				city.o.print(name + " at location " + cur.getString() + " started burning.\n \tIt has " + hp + " hitpoints left.\n\n");

				// ===========================
				//	   FIND CLOSEST TRUCK
				// ===========================
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
					structptr->setState(beingrescuedF);
				}
			}
		}

		// =============================
		//	 CHECK FOR ROBBABLE STORE
		// =============================
		std::list<Store>::iterator it_s;
		bool robable = false;
		for (it_s = city.getStoresList()->begin(); it_s != city.getStoresList()->end(); it_s++) {
			if (it_s->getState() == normal) {
				robable = true;
			}
		}
		// =============================
		//	 		ROB STORE
		// =============================
		if (robable) {
			if (rand() % 20 == 0) {
				Store* storePtr;
				storePtr = city.robStore();
				if (storePtr != NULL){
					Coordinate curStore = storePtr->getLocation();
					std::string storeName = storePtr->getName();
					std::string rp = doubleToString(storePtr->getRP());
					city.o.print(storeName + " at location " + curStore.getString() + " has started being robbed.\n \tIt has " + rp + " robbery points left.\n\n");

					// ===============================
					//	FIND AN AVAILABLE POLICECAR
					// ===============================
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
			}
		}

		//===================================
		//		RANDOM CHANCE TRAFFIC JAM
		//===================================
		city.handleTrafficJams();

		// =======================
		//		BURN & ROB
		// =======================

		for (int i = 0; i < city.getMatrix()->getColumns(); i++){
			for (int j = 0; j < city.getMatrix()->getRows(); j++){
				ptr = city.getMatrix()->getObject(i, j);
				if (ptr->getState() == burning || ptr->getState() == beingrescuedF) {
					// ==========================
					//	 BURNING BUT NO RESCUE
					// ==========================
					if (ptr->getState() == burning) {
						Structures* newFireStructure = dynamic_cast<Structures*>(ptr);

						// ===========================
						//	   FIND CLOSEST TRUCK
						// ===========================
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

					Structures* structptr = dynamic_cast<Structures*>(ptr);

					// ========================
					//	    MAKE CASUALTIES
					// ========================
					if (structptr->getHP() == structptr->getMaxHp()-10) {
						Casualty* cas = new Casualty(structptr);
						city.getCasualtyList()->push_back(cas);
						city.o.print("A new casualty has fallen, he has " + intToString(cas->getHP()) + " hp left.\n\n");

						// ==========================
						//	    FIND AN AMBULANCE
						// ==========================
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
							Ambulance* ambulance = truck_distances.begin()->second;
							ambulance->setAvailable(false);
							ambulance->setPassenger(city.getCasualtyList()->at(city.getCasualtyList()->size()-1));
							ambulance->setDestination(city.getAdjecantStreet(ambulance->getPassenger()->getHome(), ambulance->getCoord()));
							ambulance->setTarget(ambulance->getPassenger()->getHome());
							ambulance->setIsHome(false);
							ambulance->getPassenger()->setPassengerState(beingrescued);
						}
					}

					structptr->decreaseHP();
					double hp = structptr->getHP();
					if (hp/floor(hp) == 1){
						structptr->increaseSpreadcounter();
						Coordinate cur = structptr->getLocation();
						std::string name = structptr->getName();
						city.o.print(name + " at location " + cur.getString() + " is still burning.\n\tIt has " + doubleToString(hp) + " hitpoints left.\n\n");
					}

					if (structptr->getHP() <= 0){
						structptr->setState(destroyed);
						Coordinate cur = structptr->getLocation();
						std::string name = structptr->getName();
						city.o.print(name + " at location " + cur.getString() + " is destroyed.\n \tIt has " + doubleToString(hp) + " hitpoints left.\n\n");
					}

					// ========================
					//	     SPREAD FIRE
					// ========================
					if (structptr->getSpreadcounter() >= 3 && (ptr->getState() == burning || ptr->getState() == beingrescuedF)) {
						structptr->resetSpreadcounter();
						Coordinate newFire = city.getAdjecantBuilding(ptr);
						if (newFire.getX() != -1 && newFire.getY() != -1) {
							city.setFire(newFire.getX(), newFire.getY());
							city.o.print("Fire has spread and a building on location " + newFire.getString() + " has caught fire.\n\n");

							CityObjects* newFireBuilding = city.getMatrix()->getObject(newFire.getX(), newFire.getY());
							Structures* newFireStructure = dynamic_cast<Structures*>(newFireBuilding);

							// ===========================
							//	   FIND CLOSEST TRUCK
							// ===========================
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
					// ===========================
					//	   ROBBED BUT NO RESCUE
					// ===========================
					if (ptr->getState() == beingrobbed) {
						Structures* storePtr = dynamic_cast<Structures*>(ptr);

						// ===============================
						//	   FIND AVAILABLE POLICECAR
						// ===============================
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

					finished = false;

					Store* storePtr = dynamic_cast<Store*>(ptr);

					storePtr->decreaseRP();
					double rp = storePtr->getRP();
					if (rp/floor(rp) == 1){
						Coordinate cur = storePtr->getLocation();
						std::string name = storePtr->getName();
						city.o.print(name + " at location " + cur.getString() + " is still being robbed.\n\tIt has " + doubleToString(rp) + " robbery points left.\n\n");
					}

					if (storePtr->getRP() <= 0){
						storePtr->setState(destroyed);
						Coordinate cur = storePtr->getLocation();
						std::string name = storePtr->getName();
						city.o.print(name + " at location " + cur.getString() + " is robbed empty.\n \tIt has " + doubleToString(rp) + " robbery points left.\n\n");
					}
				}
				// ==========================
				//		REPAIR BUILDINGS
				// ==========================
				else if (ptr->getState() == repairing){

					Structures* structptr = dynamic_cast<Structures*>(ptr);
					double hp = structptr->getHP();
					double maxhp = structptr->getMaxHp();
					if (hp < maxhp){
						structptr->increaseHp();
						if (structptr->getHP()/floor(structptr->getHP()) == 1){
							Coordinate cur = structptr->getLocation();
							std::string name = structptr->getName();
							city.o.print(name + " at location " + cur.getString() + " is repairing.\n \tIt has " + doubleToString(structptr->getHP()) + " hitpoints left.\n\n");
						}
					}
				}
			}
		}

		// =============================
		// 	  DECREASE HP CASUALTIES
		// =============================
		std::vector<Casualty*>::iterator itc;
		for (itc = city.getCasualtyList()->begin(); itc != city.getCasualtyList()->end(); itc++) {
			if ((*itc)->getPState() == hurt || (*itc)->getPState() == beingrescued) {
				finished = false;
				(*itc)->decreaseHP();
				city.o.print("Casualty's hp has decreased, he has " + intToString((*itc)->getHP()) + " hp left.\n\n");
			}
			if ((*itc)->getPState() == hurt){
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
					rescueTruck->setPassenger((*itc));
					rescueTruck->setDestination(city.getAdjecantStreet(rescueTruck->getPassenger()->getHome(), rescueTruck->getCoord()));
					rescueTruck->setTarget(rescueTruck->getPassenger()->getHome());
					rescueTruck->setIsHome(false);
					(*itc)->setPassengerState(beingrescued);
				}
			}
		}

		// ==========================
		// 		MOVE FIRETRUCKS
		// ==========================
		for (std::list<Firetruck>::iterator it = city.getTruckList()->begin(); it != city.getTruckList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				if (it->getAvailable() == false) {
					Structures* saved = it->getTarget();
					if (saved->getState() == beingrescuedF || saved->getState() == burning) {
						saved->setState(repairing);
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Firetruck " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey have extinguished the fire and are returning to the base.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Firetruck " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey saw that the structure was destroyed and are returning to the base.\n\n");
					}
				}
				else {
					if (it->getIsHome() == false){
						city.o.print("Firetruck " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + ".\n\n");
						it->setIsHome(true);
						it->setAvailable(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Firetruck " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location" + destination.getString() + ".\n");
				city.o.print("\tThe firetruck is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
			}
		}

		// ==========================
		// 		MOVE POLICECARS
		// ==========================
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
						city.o.print("Policecar " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey stopped the robbery and caught the bad guys and are now returning to the base.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Policecar " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey were too late and the store was completely robbed and are now returning to the base.\n\n");
					}
				}
				else {
					if (it->getIsHome() == false){
						city.o.print("Policecar " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + ".\n\n");
						it->setIsHome(true);

					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Policecar " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location " + destination.getString() + ".\n");
				city.o.print("\tThe policecar is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
			}
		}

		// ==========================
		// 		MOVE AMBULANCES
		// ==========================
		for (std::list<Ambulance>::iterator it = city.getAmbulancesList()->begin(); it != city.getAmbulancesList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				Coordinate cur_dest = it->getCoord();
				if (it->getAvailable() == false && (it->getBaseptr() != it->getTarget())) {
					Casualty* passenger = it->getPassenger();
					if (!(passenger->getPState() == dead)) {
						it->setContaining(true);
						passenger->setPassengerState(inCare);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Ambulance " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey picked up the injured person and are now returning to the hospital.\n\n");
					}
					else if (passenger->getPState() == dead) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Ambulance " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey were too late, the person died and was burried and they are now returning to the hospital.\n\n");
						it->setContaining(false);
					}
				}
				else {
					if (it->getIsHome() == false){
						city.o.print("Ambulance " + it->getName() + " has arrived at the hospital " + it->getBaseptr()->getName() + ".\n");
						if(it->getContaining() == true){
							city.o.print("\tThey have dropped of the injured person.\n\n");
							it->setContaining(false);
						}
						else {
							city.o.print("\n");
						}
						it->setIsHome(true);
						it->setAvailable(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Ambulance " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location " + destination.getString() + ".\n");
				city.o.print("\tThe ambulance is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
			}
		}

		int at_home = 0;

		for(std::list<Firetruck>::iterator it = city.getTruckList()->begin(); it != city.getTruckList()->end(); it++){
			if (it->getIsHome()){
				at_home++;
			}
		}

		for(std::list<PoliceCar>::iterator it = city.getPoliceCarsList()->begin(); it != city.getPoliceCarsList()->end(); it++){
			if (it->getIsHome()){
				at_home++;
			}
		}

		for(std::list<Ambulance>::iterator it = city.getAmbulancesList()->begin(); it != city.getAmbulancesList()->end(); it++){
			if (it->getIsHome()){
				at_home++;
			}
		}

		city.getMatrix()->printVehicles(city.o, city.getVehicles());

		if ((at_home == city.getAmountTrucks()+city.getAmountCars()+city.getAmountAmbulances()) && finished) {
			city.o.print("\n");
			city.o.print("================================================================================================================================");
			return;
		}
		else {
			city.o.print("\n");
			city.o.print("--------------------------------------------------------------------------------------------------------------------------------\n\n");
		}

	}
}


void simulateCity_Test(City& city,
		Coordinate Fire_location1, Coordinate Fire_location2, int turns_fire,
		Coordinate Rob_location1, Coordinate Rob_location2, int turns_robbery) {

	REQUIRE(city.properlyInitialized(), "Object 'City' was not properly properlyInitializedialized when calling update()");

	city.o.print("\nSIMULATION:");
	city.o.print("\n===========\n\n");

	if (!(city.getValidCity())){
		city.o.print("\n\t CITY WAS NOT VALID\n\n");
		return;
	}

	bool finished = false;

	// ============================
	// 		   SETTING FIRE
	// ============================
	CityObjects* ptr;
	ptr = city.setFire(Fire_location1.getX(), Fire_location1.getY());
	Structures* structptr = dynamic_cast<Structures*>(ptr);
	std::string cur = structptr->getLocation().getString();

	std::string name = structptr->getName();
	std::string hp = doubleToString(structptr->getHP());
	city.o.print(name + " at location " + cur + " started burning.\n\tIt has " + hp + " hitpoints left.\n\n");

	// ===========================
	//	   FIND CLOSEST TRUCK
	// ===========================
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

	// =============================
	//	 CHECK FOR ROBBABLE STORE
	// =============================
	std::list<Store>::iterator it_s;
	bool robable = false;
	for (it_s = city.getStoresList()->begin(); it_s != city.getStoresList()->end(); it_s++) {
		if (it_s->getState() == normal) {
			robable = true;
		}
	}
	// =============================
	//	 		ROB STORE
	// =============================
	if (robable && Rob_location1 != Coordinate(-1, -1)) {
		Store* storePtr;
		storePtr = city.robStore(Rob_location1.getX(), Rob_location1.getY());
		Coordinate curStore = storePtr->getLocation();
		std::string storeName = storePtr->getName();
		std::string rp = doubleToString(storePtr->getRP());
		city.o.print(storeName + " at location " + curStore.getString() + " has started being robbed.\n\tIt has " + rp + " robbery points left.\n\n");

		// ===============================
		//	FIND AN AVAILABLE POLICECAR
		// ===============================
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

	// ======================
	// 		WHILE LOOP
	// ======================
	int loops = 0;

	while (true) {
		finished = true;

		if (loops == turns_fire) {
			// ============================
			// 		   SETTING FIRE
			// ============================
			ptr = city.setFire(Fire_location2.getX(), Fire_location2.getY());
			Structures* structptr = dynamic_cast<Structures*>(ptr);
			Coordinate cur = structptr->getLocation();
			std::string name = structptr->getName();
			std::string hp = doubleToString(structptr->getHP());
			city.o.print(name + " at location " + cur.getString() + " started burning.\n \tIt has " + hp + " hitpoints left.\n\n");

			// ===========================
			//	   FIND CLOSEST TRUCK
			// ===========================
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
			}
		}

		// =============================
		//	 		ROB STORE
		// =============================
		if (loops == turns_robbery && Rob_location2 != Coordinate(-1, -1)) {
			Store* storePtr;
			storePtr = city.robStore(Rob_location2.getX(), Rob_location2.getY());
			Coordinate curStore = storePtr->getLocation();
			std::string storeName = storePtr->getName();
			std::string rp = doubleToString(storePtr->getRP());
			city.o.print(storeName + " at location " + curStore.getString() + " has started being robbed.\n \tIt has " + rp + " robbery points left.\n\n");

			// ===============================
			//	FIND AN AVAILABLE POLICECAR
			// ===============================
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

		// =======================
		//		BURN & ROB
		// =======================
		for (int i = 0; i < city.getMatrix()->getColumns(); i++){
			for (int j = 0; j < city.getMatrix()->getRows(); j++){
				ptr = city.getMatrix()->getObject(i, j);
				if (ptr->getState() == burning || ptr->getState() == beingrescuedF) {
					// ==========================
					//	 BURNING BUT NO RESCUE
					// ==========================
					if (ptr->getState() == burning) {
						Structures* newFireStructure = dynamic_cast<Structures*>(ptr);

						// ===========================
						//	   FIND CLOSEST TRUCK
						// ===========================
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

					Structures* structptr = dynamic_cast<Structures*>(ptr);

					// ========================
					//	    MAKE CASUALTIES
					// ========================
					if (structptr->getHP() == structptr->getMaxHp()-10) {
						Casualty* cas = new Casualty(structptr);
						city.getCasualtyList()->push_back(cas);
						city.o.print("A new casualty has fallen, he has " + intToString(cas->getHP()) + " hp left.\n\n");

						// ==========================
						//	    FIND AN AMBULANCE
						// ==========================
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
							Ambulance* ambulance = truck_distances.begin()->second;
							ambulance->setAvailable(false);
							ambulance->setPassenger(city.getCasualtyList()->at(city.getCasualtyList()->size()-1));
							ambulance->setDestination(city.getAdjecantStreet(ambulance->getPassenger()->getHome(), ambulance->getCoord()));
							ambulance->setTarget(ambulance->getPassenger()->getHome());
							ambulance->setIsHome(false);
							ambulance->getPassenger()->setPassengerState(beingrescued);
						}
					}

					structptr->decreaseHP();
					double hp = structptr->getHP();
					if (hp/floor(hp) == 1){
						structptr->increaseSpreadcounter();
						Coordinate cur = structptr->getLocation();
						std::string name = structptr->getName();
						city.o.print(name + " at location " + cur.getString() + " is still burning.\n\tIt has " + doubleToString(hp) + " hitpoints left.\n\n");
					}

					if (structptr->getHP() <= 0){
						structptr->setState(destroyed);
						Coordinate cur = structptr->getLocation();
						std::string name = structptr->getName();
						city.o.print(name + " at location " + cur.getString() + " is destroyed.\n \tIt has " + doubleToString(hp) + " hitpoints left.\n\n");
					}

					// ========================
					//	     SPREAD FIRE
					// ========================
					if (structptr->getSpreadcounter() >= 3 && (ptr->getState() == burning || ptr->getState() == beingrescuedF)) {
						structptr->resetSpreadcounter();
						Coordinate newFire = city.getAdjecantBuilding(ptr);
						if (newFire.getX() != -1 && newFire.getY() != -1) {
							city.setFire(newFire.getX(), newFire.getY());
							city.o.print("Fire has spread and a building on location " + newFire.getString() + " has caught fire.\n\n");

							CityObjects* newFireBuilding = city.getMatrix()->getObject(newFire.getX(), newFire.getY());
							Structures* newFireStructure = dynamic_cast<Structures*>(newFireBuilding);

							// ===========================
							//	   FIND CLOSEST TRUCK
							// ===========================
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

					finished = false;

					Store* storePtr = dynamic_cast<Store*>(ptr);

					storePtr->decreaseRP();
					double rp = storePtr->getRP();
					if (rp/floor(rp) == 1){
						Coordinate cur = storePtr->getLocation();
						std::string name = storePtr->getName();
						city.o.print(name + " at location " + cur.getString() + " is still being robbed.\n\tIt has " + doubleToString(rp) + " robbery points left.\n\n");
					}

					if (storePtr->getRP() <= 0){
						storePtr->setState(destroyed);
						Coordinate cur = storePtr->getLocation();
						std::string name = storePtr->getName();
						city.o.print(name + " at location " + cur.getString() + " is robbed empty.\n \tIt has " + doubleToString(rp) + " robbery points left.\n\n");
					}
				}
				else if (ptr->getState() == repairing){

					Structures* structptr = dynamic_cast<Structures*>(ptr);
					double hp = structptr->getHP();
					double maxhp = structptr->getMaxHp();
					if (hp < maxhp){
						structptr->increaseHp();
						if (structptr->getHP()/floor(structptr->getHP()) == 1){
							Coordinate cur = structptr->getLocation();
							std::string name = structptr->getName();
							city.o.print(name + " at location " + cur.getString() + " is repairing.\n \tIt has " + doubleToString(structptr->getHP()) + " hitpoints left.\n\n");
						}
					}
				}
			}
		}

		int i = 0;

		// =============================
		// 	  DECREASE HP CASUALTIES
		// =============================
		std::vector<Casualty*>::iterator itc;
		for (itc = city.getCasualtyList()->begin(); itc != city.getCasualtyList()->end(); itc++) {
			if ((*itc)->getPState() == hurt || (*itc)->getPState() == beingrescued) {
				finished = false;
				(*itc)->decreaseHP();
				city.o.print("Casualty's hp has decreased, he has " + intToString((*itc)->getHP()) + " hp left.\n\n");
			}
			if ((*itc)->getPState() == hurt){
				std::list<Ambulance>::iterator it_t;
				structptr = (*itc)->getHome();
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
					rescueTruck->setPassenger((*itc));
					rescueTruck->setDestination(city.getAdjecantStreet(rescueTruck->getPassenger()->getHome(), rescueTruck->getCoord()));
					rescueTruck->setTarget(rescueTruck->getPassenger()->getHome());
					rescueTruck->setIsHome(false);
					(*itc)->setPassengerState(beingrescued);
				}
			}
		}

		// ==========================
		// 		MOVE FIRETRUCKS
		// ==========================
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
						city.o.print("Firetruck " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey have extinguished the fire and are returning to the base.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Firetruck " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey saw that the structure was destroyed and are returning to the base.\n\n");
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.o.print("Firetruck " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + ".\n\n");
						it->setIsHome(true);
						it->setAvailable(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Firetruck " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location" + destination.getString() + ".\n");
				city.o.print("\tThe firetruck is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
			}
		}

		// ==========================
		// 		MOVE POLICECARS
		// ==========================
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
						city.o.print("Policecar " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey stopped the robbery and caught the bad guys and are now returning to the base.\n\n");
					}
					else if (saved->getState() == destroyed) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Policecar " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey were too late and the store was completely robbed and are now returning to the base.\n\n");
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.o.print("Policecar " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + ".\n\n");
						it->setIsHome(true);

					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Policecar " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location " + destination.getString() + ".\n");
				city.o.print("\tThe policecar is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
			}
		}

		// ==========================
		// 		MOVE AMBULANCES
		// ==========================
		for (std::list<Ambulance>::iterator it = city.getAmbulancesList()->begin(); it != city.getAmbulancesList()->end(); it++) {
			city.driveTruck(&(*it));
			Coordinate destination = it->getDestination();
			if (it->getCoord() == destination) {
				Coordinate cur_dest = it->getCoord();
				if (it->getAvailable() == false && (it->getBaseptr() != it->getTarget())) {
					Casualty* passenger = it->getPassenger();
					if (!(passenger->getPState() == dead)) {
						it->setContaining(true);
						passenger->setPassengerState(inCare);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Ambulance " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey picked up the injured person and are now returning to the hospital.\n\n");
					}
					else if (passenger->getPState() == dead) {
						it->setAvailable(true);
						it->setDestination(it->getBaseptr()->getEntrance());
						it->setTarget(it->getBaseptr());
						city.o.print("Ambulance " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
						city.o.print("\tThey were too late, the person died and was burried and they are now returning to the hospital.\n\n");
						it->setContaining(false);
					}
				}
				else {
					i++;
					if (it->getIsHome() == false){
						city.o.print("Ambulance " + it->getName() + " has arrived at the hospital " + it->getBaseptr()->getName() + ".\n\n");
						if(it->getContaining() == true){
							city.o.print("\tThey have dropped of the injured person.");
							it->setContaining(false);
						}
						it->setIsHome(true);
						it->setAvailable(true);
					}
				}
			}
			else {
				Coordinate location = it->getCoord();
				Roads* truckStreet = dynamic_cast<Roads*>(city.getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
				city.o.print("Ambulance " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location " + destination.getString() + ".\n");
				city.o.print("\tThe ambulance is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
			}
		}

		city.getMatrix()->printVehicles(city.o, city.getVehicles());

		if ((i == city.getAmountTrucks()+city.getAmountCars()+city.getAmountAmbulances()) && finished) {
			city.o.print("\n");
			city.o.print("================================================================================================================================");
			return;
		}
		else {
			city.o.print("\n");
			city.o.print("--------------------------------------------------------------------------------------------------------------------------------\n\n");
		}

		loops++;
	}
}

void singleSimulate(City* city){
	// =======================
	//		BURN & ROB
	// =======================
	for (int i = 0; i < city->getMatrix()->getColumns(); i++){
		for (int j = 0; j < city->getMatrix()->getRows(); j++){
			CityObjects *ptr = city->getMatrix()->getObject(i, j);
			if (ptr->getState() == burning || ptr->getState() == beingrescuedF) {
				// ==========================
				//	 BURNING BUT NO RESCUE
				// ==========================
				if (ptr->getState() == burning) {
					Structures* newFireStructure = dynamic_cast<Structures*>(ptr);

					// ===========================
					//	   FIND CLOSEST TRUCK
					// ===========================
					std::list<Firetruck>::iterator it_t;
					std::list<std::pair<int, Firetruck*> > truck_distances;
					for (it_t = city->getTruckList()->begin(); it_t != city->getTruckList()->end(); it_t++) {
						if (it_t->getAvailable()) {
							std::pair<int, Firetruck*> temp(city->calculateDistance(city->getAdjecantStreet(newFireStructure, it_t->getCoord()), it_t->getCoord()), &(*it_t));
							truck_distances.push_back(temp);
						}
					}
					truck_distances.sort();
					if (truck_distances.size() != 0){
						Firetruck* rescueTruck = truck_distances.begin()->second;
						rescueTruck->setAvailable(false);
						rescueTruck->setDestination(city->getAdjecantStreet(newFireStructure, rescueTruck->getCoord()));
						rescueTruck->setTarget(newFireStructure);
						rescueTruck->setIsHome(false);
						ptr->setState(beingrescuedF);
					}
				}

				Structures* structptr = dynamic_cast<Structures*>(ptr);

				// ========================
				//	    MAKE CASUALTIES
				// ========================
				if (structptr->getHP() == structptr->getMaxHp()-10) {
					Casualty* cas = new Casualty(structptr);
					city->getCasualtyList()->push_back(cas);
					city->o.print("A new casualty has fallen, he has " + intToString(cas->getHP()) + " hp left.\n\n");

					// ==========================
					//	    FIND AN AMBULANCE
					// ==========================
					std::list<Ambulance>::iterator it_t;
					std::list<std::pair<int, Ambulance*> > truck_distances;
					for (it_t = city->getAmbulancesList()->begin(); it_t != city->getAmbulancesList()->end(); it_t++) {
						if (it_t->getAvailable()) {
							std::pair<int, Ambulance*> temp(city->calculateDistance(city->getAdjecantStreet(structptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
							truck_distances.push_back(temp);
						}
					}
					truck_distances.sort();
					if (truck_distances.size() != 0){
						Ambulance* ambulance = truck_distances.begin()->second;
						ambulance->setAvailable(false);
						ambulance->setPassenger(city->getCasualtyList()->at(city->getCasualtyList()->size()-1));
						ambulance->setDestination(city->getAdjecantStreet(ambulance->getPassenger()->getHome(), ambulance->getCoord()));
						ambulance->setTarget(ambulance->getPassenger()->getHome());
						ambulance->setIsHome(false);
						ambulance->getPassenger()->setPassengerState(beingrescued);
					}
				}

				structptr->decreaseHP();
				double hp = structptr->getHP();
				if (hp/floor(hp) == 1){
					structptr->increaseSpreadcounter();
					Coordinate cur = structptr->getLocation();
					std::string name = structptr->getName();
					city->o.print(name + " at location " + cur.getString() + " is still burning.\n\tIt has " + doubleToString(hp) + " hitpoints left.\n\n");
				}

				if (structptr->getHP() <= 0){
					structptr->setState(destroyed);
					Coordinate cur = structptr->getLocation();
					std::string name = structptr->getName();
					city->o.print(name + " at location " + cur.getString() + " is destroyed.\n \tIt has " + doubleToString(hp) + " hitpoints left.\n\n");
				}

				// ========================
				//	     SPREAD FIRE
				// ========================
				if (structptr->getSpreadcounter() >= 3 && (ptr->getState() == burning || ptr->getState() == beingrescuedF)) {
					structptr->resetSpreadcounter();
					Coordinate newFire = city->getAdjecantBuilding(ptr);
					if (newFire.getX() != -1 && newFire.getY() != -1) {
						city->setFire(newFire.getX(), newFire.getY());
						city->o.print("Fire has spread and a building on location " + newFire.getString() + " has caught fire.\n\n");

						CityObjects* newFireBuilding = city->getMatrix()->getObject(newFire.getX(), newFire.getY());
						Structures* newFireStructure = dynamic_cast<Structures*>(newFireBuilding);

						// ===========================
						//	   FIND CLOSEST TRUCK
						// ===========================
						std::list<Firetruck>::iterator it_t;
						std::list<std::pair<int, Firetruck*> > truck_distances;
						for (it_t = city->getTruckList()->begin(); it_t != city->getTruckList()->end(); it_t++) {
							if (it_t->getAvailable()) {
								std::pair<int, Firetruck*> temp(city->calculateDistance(city->getAdjecantStreet(newFireStructure, it_t->getCoord()), it_t->getCoord()), &(*it_t));
								truck_distances.push_back(temp);
							}
						}
						truck_distances.sort();
						if (truck_distances.size() != 0){
							Firetruck* rescueTruck = truck_distances.begin()->second;
							rescueTruck->setAvailable(false);
							rescueTruck->setDestination(city->getAdjecantStreet(newFireStructure, rescueTruck->getCoord()));
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
					for (it_pc = city->getPoliceCarsList()->begin(); it_pc != city->getPoliceCarsList()->end(); it_pc++) {
						if (it_pc->getAvailable()) {
							std::pair<int, PoliceCar*> temp(city->calculateDistance(city->getAdjecantStreet(storePtr, it_pc->getCoord()), it_pc->getCoord()), &(*it_pc));
							car_distances.push_back(temp);
						}
					}
					car_distances.sort();
					if (car_distances.size() != 0){
						PoliceCar* rescueCar = car_distances.begin()->second;
						rescueCar->setAvailable(false);
						rescueCar->setDestination(city->getAdjecantStreet(storePtr, rescueCar->getCoord()));
						rescueCar->setTarget(storePtr);
						rescueCar->setIsHome(false);
						storePtr->setState(beingrescuedR);
					}
				}

				Store* storePtr = dynamic_cast<Store*>(ptr);

				storePtr->decreaseRP();
				double rp = storePtr->getRP();
				if (rp/floor(rp) == 1){
					Coordinate cur = storePtr->getLocation();
					std::string name = storePtr->getName();
					city->o.print(name + " at location " + cur.getString() + " is still being robbed.\n\tIt has " + doubleToString(rp) + " robbery points left.\n\n");
				}

				if (storePtr->getRP() <= 0){
					storePtr->setState(destroyed);
					Coordinate cur = storePtr->getLocation();
					std::string name = storePtr->getName();
					city->o.print(name + " at location " + cur.getString() + " is robbed empty.\n \tIt has " + doubleToString(rp) + " robbery points left.\n\n");
				}
			}
			else if (ptr->getState() == repairing){

				Structures* structptr = dynamic_cast<Structures*>(ptr);
				double hp = structptr->getHP();
				double maxhp = structptr->getMaxHp();
				if (hp < maxhp){
					structptr->increaseHp();
					if (structptr->getHP()/floor(structptr->getHP()) == 1){
						Coordinate cur = structptr->getLocation();
						std::string name = structptr->getName();
						city->o.print(name + " at location " + cur.getString() + " is repairing.\n \tIt has " + doubleToString(structptr->getHP()) + " hitpoints left.\n\n");
					}
				}
			}
		}
	}

	// =============================
	// 	  DECREASE HP CASUALTIES
	// =============================
	std::vector<Casualty*>::iterator itc;
	for (itc = city->getCasualtyList()->begin(); itc != city->getCasualtyList()->end(); itc++) {
		if ((*itc)->getPState() == hurt || (*itc)->getPState() == beingrescued) {
			(*itc)->decreaseHP();
			city->o.print("Casualty's hp has decreased, he has " + intToString((*itc)->getHP()) + " hp left.\n\n");
		}
		if ((*itc)->getPState() == hurt){
			std::list<Ambulance>::iterator it_t;
			Structures *structptr = (*itc)->getHome();
			std::list<std::pair<int, Ambulance*> > truck_distances;
			for (it_t = city->getAmbulancesList()->begin(); it_t != city->getAmbulancesList()->end(); it_t++) {
				if (it_t->getAvailable()) {
					std::pair<int, Ambulance*> temp(city->calculateDistance(city->getAdjecantStreet(structptr, it_t->getCoord()), it_t->getCoord()), &(*it_t));
					truck_distances.push_back(temp);
				}
			}
			truck_distances.sort();
			if (truck_distances.size() != 0){
				Ambulance* rescueTruck = truck_distances.begin()->second;
				rescueTruck->setAvailable(false);
				rescueTruck->setPassenger((*itc));
				rescueTruck->setDestination(city->getAdjecantStreet(rescueTruck->getPassenger()->getHome(), rescueTruck->getCoord()));
				rescueTruck->setTarget(rescueTruck->getPassenger()->getHome());
				rescueTruck->setIsHome(false);
				(*itc)->setPassengerState(beingrescued);
			}
		}
	}

	// ==========================
	// 		MOVE FIRETRUCKS
	// ==========================
	for (std::list<Firetruck>::iterator it = city->getTruckList()->begin(); it != city->getTruckList()->end(); it++) {
		city->driveTruck(&(*it));
		Coordinate destination = it->getDestination();
		if (it->getCoord() == destination) {
			if (it->getAvailable() == false) {
				Structures* saved = it->getTarget();
				if (saved->getState() == beingrescuedF) {
					saved->setState(repairing);
					it->setAvailable(true);
					it->setDestination(it->getBaseptr()->getEntrance());
					it->setTarget(it->getBaseptr());
					city->o.print("Firetruck " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
					city->o.print("\tThey have extinguished the fire and are returning to the base.\n\n");
				}
				else if (saved->getState() == destroyed) {
					it->setAvailable(true);
					it->setDestination(it->getBaseptr()->getEntrance());
					it->setTarget(it->getBaseptr());
					city->o.print("Firetruck " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
					city->o.print("\tThey saw that the structure was destroyed and are returning to the base.\n\n");
				}
			}
			else {
				if (it->getIsHome() == false){
					city->o.print("Firetruck " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + ".\n\n");
					it->setIsHome(true);
					it->setAvailable(true);
				}
			}
		}
		else {
			Coordinate location = it->getCoord();
			Roads* truckStreet = dynamic_cast<Roads*>(city->getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
			city->o.print("Firetruck " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location" + destination.getString() + ".\n");
			city->o.print("\tThe firetruck is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
		}
	}

	// ==========================
	// 		MOVE POLICECARS
	// ==========================
	for (std::list<PoliceCar>::iterator it = city->getPoliceCarsList()->begin(); it != city->getPoliceCarsList()->end(); it++) {
		city->driveTruck(&(*it));
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
					city->o.print("Policecar " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
					city->o.print("\tThey stopped the robbery and caught the bad guys and are now returning to the base.\n\n");
				}
				else if (saved->getState() == destroyed) {
					it->setAvailable(true);
					it->setDestination(it->getBaseptr()->getEntrance());
					it->setTarget(it->getBaseptr());
					city->o.print("Policecar " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
					city->o.print("\tThey were too late and the store was completely robbed and are now returning to the base.\n\n");
				}
			}
			else {
				if (it->getIsHome() == false){
					city->o.print("Policecar " + it->getName() + " has arrived at its base " + it->getBaseptr()->getName() + ".\n\n");
					it->setIsHome(true);

				}
			}
		}
		else {
			Coordinate location = it->getCoord();
			Roads* truckStreet = dynamic_cast<Roads*>(city->getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
			city->o.print("Policecar " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location " + destination.getString() + ".\n");
			city->o.print("\tThe policecar is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
		}
	}

	// ==========================
	// 		MOVE AMBULANCES
	// ==========================
	for (std::list<Ambulance>::iterator it = city->getAmbulancesList()->begin(); it != city->getAmbulancesList()->end(); it++) {
		city->driveTruck(&(*it));
		Coordinate destination = it->getDestination();
		if (it->getCoord() == destination) {
			Coordinate cur_dest = it->getCoord();
			if (it->getAvailable() == false && (it->getBaseptr() != it->getTarget())) {
				Casualty* passenger = it->getPassenger();
				if (!(passenger->getPState() == dead)) {
					it->setContaining(true);
					passenger->setPassengerState(inCare);
					it->setDestination(it->getBaseptr()->getEntrance());
					it->setTarget(it->getBaseptr());
					city->o.print("Ambulance " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
					city->o.print("\tThey picked up the injured person and are now returning to the hospital.\n\n");
				}
				else if (passenger->getPState() == dead) {
					it->setAvailable(true);
					it->setDestination(it->getBaseptr()->getEntrance());
					it->setTarget(it->getBaseptr());
					city->o.print("Ambulance " + it->getName() + " has reached its destination at location " + destination.getString() + ".\n");
					city->o.print("\tThey were too late, the person died and was burried and they are now returning to the hospital.\n\n");
					it->setContaining(false);
				}
			}
			else {
				if (it->getIsHome() == false){
					city->o.print("Ambulance " + it->getName() + " has arrived at the hospital " + it->getBaseptr()->getName() + ".\n\n");
					if(it->getContaining() == true){
						city->o.print("\tThey have dropped of the injured person.");
						it->setContaining(false);
					}
					it->setIsHome(true);
					it->setAvailable(true);
				}
			}
		}
		else {
			Coordinate location = it->getCoord();
			Roads* truckStreet = dynamic_cast<Roads*>(city->getMatrix()->getObject(it->getCoord().getX(), it->getCoord().getY()));
			city->o.print("Ambulance " + it->getName() + " is on its way to " + it->getTarget()->getName() + " on location " + destination.getString() + ".\n");
			city->o.print("\tThe ambulance is at " + truckStreet->getName() + " on location " + location.getString() + ".\n\n");
		}
	}

    city->getMatrix()->generateHTMLMap(city->getVehicles());
}


