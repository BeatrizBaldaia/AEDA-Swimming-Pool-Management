#include "Person.h"

unsigned int Person::lastID = 0;


/* PERSON */

Person::Person(string name, Date birthDate) : ID(lastID) {
	this->name = name;
	this->birthDate = birthDate;
	lastID++;
}

string Person::getName() const{
	return name;
}

unsigned int Person::getID() const{
	return ID;
}

Date Person::getBirthDate() const{
	return birthDate;
}

void Person::setName(string name){
	this->name = name;
}


/* CUSTOMER */

Customer::Customer(string name, Date birthDate) : Person(name, birthDate){}

float Customer::getMonthCost(unsigned int month) const{
	float sum = 0;
	for(PoolUse * x : uses){
		if(x->getDate().getMonth() == month){
			cout << endl;
			sum += x->getCost();
		}
	}
	return sum;
}

void Customer::attendLesson(Lesson * lesson, Date date, Time time){
	PoolUse * x = new LessonUse(date, time, lesson);
	uses.push_back(x);
}

void Customer::addUse(PoolUse * pooluse){
	uses.push_back(pooluse);
}

void Customer::freeSwim(Time startTime, Date date, unsigned int duration){
	PoolUse * x = new FreeSwimUse(date, startTime, duration);
	uses.push_back(x);
}

bool Customer::attendedLesson(Lesson * lesson){
	for(PoolUse * x : uses){
		if(x->getLesson() == lesson){
			return true;
		}
	}
	return false;
}

/* TEACHER */

Teacher::Teacher(string name, Date birthDate) : Person(name, birthDate){
	lessonsGiven = 0;
}

float Teacher::getMonthCost(unsigned int month) const{
	return 0.0;
}

int Teacher::getNumberLessons() const{
	return lessonsGiven;
}

string Teacher::getName() const{
	return Person::getName();
}

bool Teacher::operator < (const Teacher & t2) const{
	return lessonsGiven < t2.getNumberLessons();
}

void Teacher::setLesson(){
	lessonsGiven ++;
}
