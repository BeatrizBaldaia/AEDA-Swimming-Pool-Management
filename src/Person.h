#pragma once

#include <vector>
#include "PoolUse.h"

using namespace std;

class Person {
public:
	Person(string name, Date birthDate);

	static unsigned int lastID;

private:
	unsigned int ID;
	string name;
	Date birthDate;
};

class Customer : public Person {
public:
	float getMonthCost(unsigned int month) const;
	bool attendLesson();
	bool freeSwim();

private:
	vector <* PoolUse> uses;
};

class Teacher : public Person {

};

#pragma once
