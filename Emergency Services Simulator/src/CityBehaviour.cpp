/*
 * CityBehaviour.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: kristof
 */

#include "DesignByContract.h"
#include "City.h"
#include "CityObjects.h"
#include "CityBehaviour.h"

CityBehaviour::CityBehaviour(City* the_city) {
	city = the_city;

}

CityBehaviour::~CityBehaviour() {
	// TODO Auto-generated destructor stub
}

CityObjects* CityBehaviour::setFire(){

	bool succes = false;
	CityObjects* ptr;

	Matrix* matrix = city->getMatrix();

	while (!succes){

		int random_y = rand()% matrix->getRows();
		int random_x = rand()% matrix->getColumns();

		ptr = matrix->getObject(random_x, random_y);

		if (ptr->getState() == normal){
			succes = true;
		}
	}

	ptr->setState(burning);

	ENSURE(ptr->getState() == burning, "setFire() did not correctly set fire to a house.");

	return ptr;
}

CityObjects* CityBehaviour::setFire(int x, int y){

	Matrix* matrix = city->getMatrix();

	bool succes = false;
	CityObjects* ptr;

	ptr = matrix->getObject(x, y);

	if (ptr->getState() == normal){
		succes = true;
	}

	ptr->setState(burning);

	ENSURE(ptr->getState() == burning, "setFire() did not correctly set fire to the given house.");

	return ptr;
}

void CityBehaviour::driveTruck(Firetruck* rescueTruck) {

	Matrix* matrix = city->getMatrix();

	Coordinate cur = rescueTruck->getCoord();
	Coordinate destination = rescueTruck->getDestination();

	if (cur == destination) {
		return;
	}

	Street* destStreet = dynamic_cast<Street*>(matrix->getObject(destination.getX(), destination.getY()));
	if (city->checkOrientation(rescueTruck->getCoord()) == "crossroad") {
		Crossroad* truckCross = dynamic_cast<Crossroad*>(matrix->getObject(rescueTruck->getCoord().getX(), rescueTruck->getCoord().getY()));
		if (truckCross->getStreet1() == destStreet->getName() || truckCross->getStreet2() == destStreet->getName()) {
			std::string orientation = city->checkOrientation(destination);
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

			Crossroad xRoad = city->closestCorrectCrossroad(cur, destStreet);
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
		Street* curStreet = dynamic_cast<Street*>(matrix->getObject(rescueTruck->getCoord().getX(), rescueTruck->getCoord().getY()));
		if (destStreet->getName() == curStreet->getName()) {
		std::string orientation = city->checkOrientation(destination);
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
			std::string orientation = city->checkOrientation(rescueTruck->getCoord());
			if (!rescueTruck->getGoToTemp()) {
				//Go to the closest crossroad
				Crossroad xroad = city->closestCrossroad(rescueTruck->getCoord());
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
