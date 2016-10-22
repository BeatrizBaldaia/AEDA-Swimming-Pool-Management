#pragma once

#include <vector>
#include "Date.h"
#include "Lesson.h"
#include "PoolUse.h"

using namespace std;

class Person {
public:
	Person(string name, Date birthDate);

	string getName() const;
	unsigned int getID() const;
	Date getBirthDate() const;

	void setName(string name);

	static unsigned int lastID;

private:
	const unsigned int ID;
	string name;
	Date birthDate;
};

class Customer : public Person {
public:
	float getMonthCost(unsigned int month) const;
	bool attendLesson(Lesson * lesson);
	bool freeSwim(Time startTime, Date date, unsigned int duration);

private:
	vector <PoolUse *> uses;
};

class Teacher : public Person {

};

#pragma once
