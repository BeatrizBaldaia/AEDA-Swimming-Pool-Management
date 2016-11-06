#ifndef _PERSON_H_
#define _PERSON_H_

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
	Customer(string name, Date birthDate);
	float getMonthCost(unsigned int month) const;
	void attendLesson(Lesson * lesson, Date date, Time time);
	void freeSwim(Time startTime, Date date, unsigned int duration);
	void addUse(PoolUse * pooluse);

private:
	vector <PoolUse *> uses;
};

class Teacher : public Person {
public:
	Teacher(string name, Date birthDate);
	float getMonthCost(unsigned int month) const;
	int getNumberLessons() const;
	string getName() const;
	bool operator < (const Teacher & t2) const;
	void setLesson();
private:
	int lessonsGiven;
};

#endif
