#include "Person.h"


Person::Person(string name, Date birthDate) : ID(lastID) {
	this->name = name;
	this->birthDate = birthDate;
	lastID ++;
}

float Customer::getMonthCost(unsigned int month) const{
	float sum = 0;
	for(auto x : uses ){ // nao estava a comseguir fazer const PoolUse * &x : uses
		if(x->getMonth2() == month){
			x->LessonDisplay();
			cout << endl;
			sum += x->getCost();
		}
	}
	return sum;
}

bool Customer::attendLesson(Lesson * lesson){
	for(auto x : uses){
		if(x->getLesson() == lesson){
			return true;
		}
	}
	return false;
}

void Customer::addUse(PoolUse * pooluse){
	uses.push_back(pooluse)
}
