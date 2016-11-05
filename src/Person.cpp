#include "Person.h"

unsigned int Person::lastID = 0;

/* PERSON */

Person::Person(string name, Date birthDate) : ID(lastID) {
	this->name = name;
	this->birthDate = birthDate;
	lastID++;
}

/* CUSTOMER */

Customer::Customer(string name, Date birthDate) : Person(name, birthDate){}

float Customer::getMonthCost(unsigned int month) const{
	float sum = 0;
	for(PoolUse * x : uses){
		if(x->getMonth() == month){
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
/* TEACHER */

Teacher::Teacher(string name, Date birthDate) : Person(name, birthDate){}

float Teacher::getMonthCost(unsigned int month) const{
	return 0.0;
}
