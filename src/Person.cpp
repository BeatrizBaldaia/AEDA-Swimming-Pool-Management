#include "Person.h"

#include <iostream>

#include "Lesson.h"

unsigned int Person::lastID = 0;

/* HOME contactInfo */

ContactInfo::ContactInfo() {
	this->city = "";
	this->street = "";
	this->number = 0;
	this->postalCode = "";
}

ContactInfo::ContactInfo(string city, string street, int number,
		string postalCode, long cellphoneNum) {
	this->city = city;
	this->street = street;
	this->number = number;
	this->postalCode = postalCode;
	this->cellphoneNum = cellphoneNum;
}
string ContactInfo::getCity() const {
	return city;
}

string ContactInfo::getStreet() const {
	return street;
}

int ContactInfo::getNumber() const {
	return number;
}

string ContactInfo::getPostalCode() const {
	return postalCode;
}

void ContactInfo::setCity(string city) {
	this->city = city;
}

void ContactInfo::setStreet(string street) {
	this->street = street;
}

void ContactInfo::setNumber(int number) {
	this->number = number;
}

long ContactInfo::getCellphoneNum() const {
	return cellphoneNum;
}

void ContactInfo::setCellphoneNum(long cellphoneNum) {
	this->cellphoneNum = cellphoneNum;
}

void ContactInfo::setPostalCode(string code) {
	this->postalCode = code;
}

/* PERSON */

Person::Person(string name, Date birthDate, ContactInfo contactInfo) :
		ID(lastID + 1) {
	this->name = name;
	this->birthDate = birthDate;
	this->contactInfo = contactInfo;
	lastID++;
}

Person::Person(string name, Date birthDate, unsigned int ID,
		ContactInfo contactInfo) :
		ID(ID) {
	this->name = name;
	this->birthDate = birthDate;
	this->contactInfo = contactInfo;
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
string Person::getCity() const {
	return contactInfo.getCity();
}
string Person::getStreet() const {
	return contactInfo.getStreet();
}
int Person::getNumber() const {
	return contactInfo.getNumber();
}

string Person::getPostalCode() const {
	return contactInfo.getPostalCode();
}

void Person::setCity(string city) {
	contactInfo.setCity(city);
}

void Person::setStreet(string street) {
	contactInfo.setStreet(street);
}

void Person::setNumber(int number) {
	contactInfo.setNumber(number);
}

long Person::getCellphoneNum() const {
	return contactInfo.getCellphoneNum();
}

void Person::setPostalCode(string code) {
	contactInfo.setPostalCode(code);
}

/* CUSTOMER */

Customer::Customer(string name, Date birthDate, ContactInfo contactInfo) :
		Person(name, birthDate, contactInfo) {
}

Customer::Customer(string name, Date birthDate, unsigned int ID,
		ContactInfo contactInfo) :
		Person(name, birthDate, ID, contactInfo) {
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

void Customer::attendLesson(GivenLesson * lesson, Date date, Time time,
		double discount) { //no menu de adicionar aula, nesta GivenLesson vamos ter de adicionar o cliente ao seu vetor de customers
	PoolUse * addlesson = new LessonUse(date, time, lesson, discount);
	uses.push_back(addlesson);
}

void Customer::addUse(PoolUse * pooluse) {
	uses.push_back(pooluse);
}

void Customer::freeSwim(Time startTime, Date date, unsigned int duration,
		double discount) {
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

void Customer::buyItem(vector<Item> items) {
	bool exist = false;
	list<Item>::iterator it = shopping.begin();
	for (int i = 0; i < items.size(); i++) {
		for (; it != shopping.end(); it++) {
			if (items[i] == (*it)) {
				int newStock = items[i].getStock() + it->getStock();
				it->setStock(newStock);
				exist = true;
				break;
			}
		}
		if (!exist) {
			shopping.push_back(items[i]);
		}

		exist = false;
	}
	shopping.sort();
}

/* TEACHER */

Teacher::Teacher(string name, Date birthDate, ContactInfo contactInfo) :
		Person(name, birthDate, contactInfo) {
	lessonsPerWeek = 0;
}

Teacher::Teacher(string name, Date birthDate, unsigned int ID,
		ContactInfo contactInfo) :
		Person(name, birthDate, ID, contactInfo) {
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

void Person::setCellphoneNum(long cellphoneNum) {
	contactInfo.setCellphoneNum(cellphoneNum);
}
