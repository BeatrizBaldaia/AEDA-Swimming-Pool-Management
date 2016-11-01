#pragma once

#include <iostream>
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
	Customer(string name, Date birthDate) : Person(name, birhtDate) {}
	float getMonthCost(unsigned int month) const;
	bool attendLesson(Lesson * lesson);
	bool freeSwim(Time startTime, Date date, unsigned int duration); //tenho que fazer a distinção entre FreeSwimUse e LessonUse porque ambas as classes derivadas têm estes 3 parâmetros
	void addUse(PoolUse * pooluse);

private:
	vector <PoolUse *> uses;
};

class Teacher : public Person {
public:
	Teacher(string name, Date birthDate) : Person(name, birhtDate) {}
	float getMonthCost(unsigned int month) const {return 0.0;}
};

#pragma once
