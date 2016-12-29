#include "Person.h"

#include <iostream>

#include "Lesson.h"

unsigned int Person::lastID = 0;

/* HOME ADDRESS */

HomeAddress::HomeAddress(){
	this->city = "";
	this->street = "";
	this->number = 0;
	this->postalCode = "";
}

HomeAddress::HomeAddress(string city, string street, int number, string postalCode){
	this->city = city;
	this->street = street;
	this->number = number;
	this->postalCode = postalCode;
}
string HomeAddress::getCity() const{
	return city;
}

string HomeAddress::getStreet() const{
	return street;
}

int HomeAddress::getNumber() const{
	return number;
}

string HomeAddress::getPostalCode() const{
	return postalCode;
}

void HomeAddress::setCity(string city){
	this->city = city;
}

void HomeAddress::setStreet(string street){
	this->street = street;
}

void HomeAddress::setNumber(int number){
	this->number = number;
}

void HomeAddress::setPostalCode(string code){
	this->postalCode = code;
}

/* PERSON */

Person::Person(string name, Date birthDate, HomeAddress address) :
		ID(lastID + 1) {
	this->name = name;
	this->birthDate = birthDate;
	this->address = address;
	lastID++;
}

Person::Person(string name, Date birthDate, unsigned int ID, HomeAddress address) :
		ID(ID) {
	this->name = name;
	this->birthDate = birthDate;
	this->address = address;
	if (ID > lastID) {
		lastID = ID;
	}
}

string Person::getName() const {
	return name;
}

unsigned int Person::getID() const {
	return ID;
}

Date Person::getBirthDate() const {
	return birthDate;
}

void Person::setName(string name) {
	this->name = name;
}
string Person::getCity() const{
	return address.getCity();
}
string Person::getStreet() const{
	return address.getStreet();
}
int Person::getNumber() const{
	return address.getNumber();
}

string Person::getPostalCode() const{
	return address.getPostalCode();
}

void Person::setCity(string city){
	address.setCity(city);
}

void Person::setStreet(string street){
	address.setStreet(street);
}

void Person::setNumber(int number){
	address.setNumber(number);
}

void Person::setPostalCode(string code){
	address.setPostalCode(code);
}

/* CUSTOMER */

Customer::Customer(string name, Date birthDate, HomeAddress address) :
		Person(name, birthDate, address) {
}

Customer::Customer(string name, Date birthDate,  unsigned int ID, HomeAddress address) :
				Person(name, birthDate, ID, address) {
}

string Customer::getCity() const{
	return Person::getCity();
}

string Customer::getStreet() const{
	return Person::getStreet();
}

int Customer::getNumber() const{
	return Person::getNumber();
}

string Customer::getPostalCode() const{
	return Person::getPostalCode();
}

void Customer::setCity(string city){
	Person::setCity(city);
}

void Customer::setStreet(string street){
	Person::setStreet(street);
}

void Customer::setNumber(int number){
	Person::setNumber(number);
}

void Customer::setPostalCode(string code){
	Person::setPostalCode(code);
}

float Customer::getMonthCost(unsigned int month, unsigned int year) const {
	float sum = 0;
	for (PoolUse * x : uses) {
		if (x->getDate().getMonth() == month
				&& x->getDate().getYear() == year) {
			cout << endl;
			sum += x->getCost();
		}
	}
	return sum;
}

void Customer::attendLesson(GivenLesson * lesson, Date date, Time time, double discount) { //no menu de adicionar aula, nesta GivenLesson vamos ter de adicionar o cliente ao seu vetor de customers
	PoolUse * addlesson = new LessonUse(date, time, lesson, discount);
	uses.push_back(addlesson);
}

void Customer::addUse(PoolUse * pooluse) {
	uses.push_back(pooluse);
}

void Customer::freeSwim(Time startTime, Date date, unsigned int duration, double discount) {
	PoolUse * x = new FreeSwimUse(date, startTime, duration, discount);
	uses.push_back(x);
}

bool Customer::attendedLesson(const GivenLesson * lesson) {
	for (PoolUse * x : uses) {
		if (x->getLesson() == lesson) {
			return true;
		}
	}
	return false;
}

int Customer::getEntryNumber() const { //frequência com que os clientes vão á piscina
	return uses.size();
}

void Customer::buyItem(vector<Item> items){
	bool exist = false;
	list<Item>::iterator it = shopping.begin();
	for(int i = 0; i < items.size(); i++){
		for(; it != shopping.end(); it++){
			if(items[i] == (*it)){
				int newStock = items[i].getStock() + it->getStock();
				it->setStock(newStock);
				exist = true;
				break;
			}
		}
		if(!exist){
			shopping.push_back(items[i]);
		}

		exist = false;
	}
	shopping.sort();
}

/* TEACHER */

Teacher::Teacher(string name, Date birthDate, HomeAddress address) :
		Person(name, birthDate, address) {
	lessonsPerWeek = 0;
}

Teacher::Teacher(string name, Date birthDate, unsigned int ID, HomeAddress address) :
		Person(name, birthDate, ID, address) {
	lessonsPerWeek = 0;
}

float Teacher::getMonthCost(unsigned int month) const {
	return 0;
}

int Teacher::getNumberLessons() const {
	return lessonsPerWeek;
}

bool Teacher::operator <(const Teacher & t2) const {
	return lessonsPerWeek < t2.getNumberLessons();
}

void Teacher::setLesson() {
	lessonsPerWeek++;
}

int Teacher::getEntryNumber() const {
	return 0;
}

vector<PoolUse*> Customer::getPoolUses() {
	return uses;
}
