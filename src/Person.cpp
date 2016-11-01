#include "Person.h"

unsigned int Person::lastID = 0;

Person::Person(string name, Date birthDate) : ID(lastID) {
	this->name = name;
	this->birthDate = birthDate;
	lastID++;
}

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

void Customer::attendLesson(Lesson * lesson){
	//TODO add LessonUse to uses;
}

void Customer::addUse(PoolUse * pooluse){
	uses.push_back(pooluse);
}
