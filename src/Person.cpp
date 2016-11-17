#include "Person.h"

#include <iostream>

#include "Lesson.h"

unsigned int Person::lastID = 0;

/* PERSON */

Person::Person(string name, Date birthDate) :
		ID(lastID + 1) {
	this->name = name;
	this->birthDate = birthDate;
	lastID++;
}

Person::Person(string name, Date birthDate, unsigned int ID) :
		ID(ID) {
	this->name = name;
	this->birthDate = birthDate;
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

/* CUSTOMER */

Customer::Customer(string name, Date birthDate) :
		Person(name, birthDate) {

}

Customer::Customer(string name, Date birthDate, unsigned int ID) :
		Person(name, birthDate, ID) {

}

float Customer::getMonthCost(unsigned int month, unsigned int year) const {
	float sum = 0;
	for (PoolUse * x : uses) {
		if (x->getDate().getMonth() == month && x->getDate().getYear() == year) {
			cout << endl;
			sum += x->getCost();
		}
	}
	return sum;
}

void Customer::attendLesson(GivenLesson * lesson, Date date, Time time) { //no menu de adicionar aula, nesta GivenLesson vamos ter de adicionar o cliente ao seu vetor de customers
	PoolUse * addlesson = new LessonUse(date, time, lesson);
	uses.push_back(addlesson);
}

void Customer::addUse(PoolUse * pooluse) {
	uses.push_back(pooluse);
}

void Customer::freeSwim(Time startTime, Date date, unsigned int duration) {
	PoolUse * x = new FreeSwimUse(date, startTime, duration);
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
	if (uses.size() == 0) {
		return 0;
	}
	Date d = uses[0]->getDate();
	int result = 1;
	for (int i = 1; 1 < uses.size(); i++) {
		if (!(d == uses[i]->getDate())) {
			d = uses[i]->getDate();
			result++;
		}
	}

	return result;
}

/* TEACHER */

Teacher::Teacher(string name, Date birthDate) :
		Person(name, birthDate) {
	lessonsPerWeek = 0;
}

Teacher::Teacher(string name, Date birthDate, unsigned int ID) :
		Person(name, birthDate, ID) {
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
