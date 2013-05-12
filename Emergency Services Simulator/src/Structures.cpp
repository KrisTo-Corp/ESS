//=======================================================================================
// Name        : Structures.cpp
// Author      : Kristof De Middelaer & Tom Roels
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - University of Antwerp
// Description : Structures in C++, Ansi-style
//=======================================================================================
#include "Structures.h"

#include <iostream>


//=====================
//	CLASS STRUCTURES
//=====================

Structures::Structures(): CityObjects(none), name(""), location(0, 0), width(0), length(0)
{
	hp = 0;
	maxhp = 0;
	spreadcounter = 0;

	ENSURE(init(), "Object 'Structures' was not properly initialized.");
}

Structures::Structures(const int x, const int y, const std::string n, const int w, const int l, Eobjects t, int hitp): CityObjects(t), name(n), location(x, y), width(w), length(l)
{
	hp = hitp;
	maxhp = hitp;
	spreadcounter = 0;

	//std::cout << "THIS OBJECT MAXHP : " << maxhp << std::endl;

	ENSURE(init(), "Object 'Structures' was not properly initialized.");
}

Structures::~Structures() {
}

std::string Structures::getName() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return name;
}

Coordinate Structures::getLocation() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return location;
}

int Structures::getWidth() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return width;
}

int Structures::getLength() {
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getName()");

	return length;
}

Structures::Structures(const Structures& c){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling copy constructor");

	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	hp = c.hp;
	maxhp = c.maxhp;
	spreadcounter = c.spreadcounter;

	_initCheck = this;
}

Structures& Structures::operator =(const Structures& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	maxhp = c.maxhp;
	hp = c.hp;
	spreadcounter = c.spreadcounter;

	_initCheck = this;

	return *this;
}

void Structures::decreaseHP(){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling decreaseHP()");

	double oldHP = hp;
	hp = hp - (1.0/(width*length));

	ENSURE(hp == oldHP - (1.0/(width*length)), "HP of structure was not decreased successfully.");
}

void Structures::increaseHp(){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling increaseHP()");

	hp = hp + ((1.0/(width*length))/2);

	ENSURE(hp = hp + ((((1.0)/width*length))/2), "Method increaseHP() of Structures did not correctly increase the object's hp");
}

double Structures::getHP(){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getHP()");

	return hp;
}

double Structures::getMaxHp(){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getMaxHp()");

	return maxhp;
}

double Structures::getSpreadcounter(){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling getSpreadcounter()");

	return spreadcounter;
}

void Structures::resetSpreadcounter(){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling resetSpreadcounter()");

	spreadcounter = 0;

	ENSURE(spreadcounter == 0, "Method resetSpreadcounter() of object 'Structures' did not correctly reset the spreadcounter.");
}

void Structures::increaseSpreadcounter(){
	REQUIRE(init(), "Object 'Structures' was not properly initialized when calling increaseSpreadcounter()");

	double oldSpreadCounter = spreadcounter;
	spreadcounter++;

	ENSURE(spreadcounter == oldSpreadCounter + 1, "Method increaseSpreadcounter() of object 'Structures' did not correctly increase the spreadcounter.");
}



//================
//	CLASS HOUSE
//================

House::House(): Structures(0, 0, "", 2, 2, house) {

	ENSURE(init(), "Object 'House' was not properly initialized.");
}

House::House(const int x, const int y, int hitp, const std::string n): Structures(x, y, n, 2, 2, house, hitp) {

	ENSURE(init(), "Object 'House' was not properly initialized.");
}

House::~House()
{
}

std::ostream& operator <<(std::ostream& s, House& house){
	REQUIRE(house.init(), "Object 'House' was not properly initialized when calling overloaded operator '<<'");

	s << "Structure: House \n";
	s << "Name: " << house.name << "\n";
	s << "hp: " << house.hp << "\n";
	s << "Location:" << house.location << "\n";

	return s;
}

House::House(const House& c){
	REQUIRE(init(), "Object 'House' was not properly initialized when calling copy constructor");

	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;
}

House& House::operator =(const House& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;

	return *this;
}


//==========================
//	CLASS FIRE DEPARTMENTS
//==========================

Fire_Department::Fire_Department(): Structures(0, 0, "", 4, 4, department), entrance(0, 0) {

	ENSURE(init(), "Object 'Fire_Department' was not properly initialized.");

}

Fire_Department::Fire_Department(const int x, const int y, const int x_entrance, const int y_entrance, const std::string n, int hp): Structures(x, y, n, 4, 4, department, hp), entrance(x_entrance, y_entrance) {

	ENSURE(init(), "Object 'Fire_Department' was not properly initialized.");
}

Fire_Department::~Fire_Department()
{
}

void Fire_Department::addTruck(Firetruck* t) {
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling addTruck()");

	trucks.push_back(t);

	ENSURE((trucks[trucks.size()-1] == t), "Firetruck was not succesfully added to trucks Vector");
}

Firetruck* Fire_Department::useTruck() {
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling useTruck()");

	int size = trucks.size();
	if (trucks.size() != 0) {
		Firetruck* readyTruck = *(trucks.begin());
		trucks.erase(trucks.begin());
		return readyTruck;
		ENSURE((size - 1 == trucks.size()), "Firetruck was not succesfully added to trucks Vector");
	}
}

Coordinate& Fire_Department::getEntrance() {
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling getEntrance().");

	return entrance;
}

std::ostream& operator <<(std::ostream& s, Fire_Department& department){
	REQUIRE(department.init(), "Object 'House' was not properly initialized when calling overloaded operator '<<'");

	s << "Structure: Fire Department \n";
	s << "Name: " << department.name << "\n";
	s << "Entrance: " << department.entrance << "\n";
	s << "Location: " << department.location << "\n";

	return s;
}

int Fire_Department::getAmountTrucks(){
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling getAmountTrucks()");

	return trucks.size();
}

Fire_Department::Fire_Department(const Fire_Department& c){
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling copy constructor");

	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	trucks = c.trucks;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;
}

Fire_Department Fire_Department::operator =(const Fire_Department& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	trucks = c.trucks;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;

	return *this;
}


//==========================
//	CLASS STORE
//==========================

Store::Store(): Structures(0, 0, "", 4, 4, store) {

	rp = 0;
	robable = true;

	ENSURE(init(), "Object 'Store' was not properly initialized.");
}

Store::Store(const int x, const int y, int hitp, int robberyPoints, const std::string n, const int width, const int length, bool rob) : Structures(x, y, n, width, length, store, hitp) {

	rp = robberyPoints;
	robable = rob;

	ENSURE(init(), "Object 'Store' was not properly initialized.");
}

double Store::getRP() {
	REQUIRE(init(), "Object 'Store' was not properly initialized when calling getRP()");

	return rp;
}

bool Store::getRobable() {
	REQUIRE(init(), "Object 'Store' was not properly initialized when calling getRobable()");

	return robable;
}

void Store::decreaseRP(){
	REQUIRE(init(), "Object 'Store' was not properly initialized when calling decreaseRP()");

	double oldRP = rp;
	rp = rp - (1.0/(width*length));

	ENSURE(rp == oldRP - (1.0/(width*length)), "HP of house was not decreased successfully.");
}

Store::Store(const Store& c){
	REQUIRE(init(), "Object 'Store' was not properly initialized when calling copy constructor");

	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	rp = c.rp;
	hp = c.hp;
	maxhp = c.maxhp;
	robable = c.robable;

	_initCheck = this;
}

Store& Store::operator =(const Store& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	rp = c.rp;
	hp = c.hp;
	maxhp = c.maxhp;
	robable = c.robable;

	_initCheck = this;

	return *this;
}

//==========================
//	CLASS POLICESTATION
//==========================

PoliceStation::PoliceStation() : Structures(0, 0, "", 0, 0, policeStation), entrance(0, 0) {
	ENSURE(init(), "Object 'policeStation' was not properly initialized.");
}

PoliceStation::PoliceStation(const int x, const int y, const int x_entrance, const int y_entrance, int hitp, const std::string n, const int width, const int length) : Structures(x, y, n, width, length, policeStation, hitp), entrance(x_entrance, y_entrance) {
	ENSURE(init(), "Object 'policeStation' was not properly initialized.");
}

Coordinate& PoliceStation::getEntrance() {
	REQUIRE(init(), "Object 'PoliceStation' was not properly initialized when calling getEntrance().");

	return entrance;
}

void PoliceStation::addCar(PoliceCar* t) {
	REQUIRE(init(), "Object 'PoliceStation' was not properly initialized when calling addCar()");

	cars.push_back(t);

	ENSURE((cars[cars.size()-1] == t), "PoliceCar was not succesfully added to cars Vector");
}

int PoliceStation::getAmountCars(){
	return cars.size();
}

PoliceStation::PoliceStation(const PoliceStation& c){
	REQUIRE(init(), "Object 'PoliceStation' was not properly initialized.");

	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;
}

PoliceStation& PoliceStation::operator =(const PoliceStation& c){

	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;

	return *this;
}

//==========================
//	CLASS HOSPITAL
//==========================

Hospital::Hospital() : Structures(0, 0, "", 0, 0, hospital), entrance(0, 0) {

	ENSURE(init(), "Object 'Hospital' was not properly initialized.");
}

Hospital::Hospital(const int x, const int y, const int x_entrance, const int y_entrance, int hitp, const std::string n, const int width, const int length) : Structures(x, y, n, width, length, hospital, hitp), entrance(x_entrance, y_entrance) {

	ENSURE(init(), "Object 'Hospital' was not properly initialized.");
}

Coordinate& Hospital::getEntrance() {
	REQUIRE(init(), "Object 'Hospital' was not properly initialized when calling getEntrance().");

	return entrance;
}

void Hospital::addAmbulance(Ambulance* t) {
	REQUIRE(init(), "Object 'Fire_Department' was not properly initialized when calling addAmbulance()");

	ambulances.push_back(t);

	ENSURE((ambulances[ambulances.size()-1] == t), "Ambulance was not succesfully added to ambulances Vector");
}

int Hospital::getAmountAmbulances(){
	return ambulances.size();
}

Hospital::Hospital(const Hospital& c){
	REQUIRE(init(), "Object 'Hospital' was not properly initialized when calling copy constructor.");

	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;
}

Hospital& Hospital::operator =(const Hospital& c){
	name = c.name;
	location = c.location;
	width = c.width;
	length = c.length;
	type = c.type;
	state = c.state;
	entrance = c.entrance;
	hp = c.hp;
	maxhp = c.maxhp;

	_initCheck = this;

	return *this;
}
