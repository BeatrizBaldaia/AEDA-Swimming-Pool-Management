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
	Person(string name, Date birthDate, unsigned int ID);

	string getName() const;
	unsigned int getID() const;
	Date getBirthDate() const;
	void setName(string name);
	virtual int getEntryNumber() const = 0;

	static unsigned int lastID;

private:
	const unsigned int ID;
	string name;
	Date birthDate;
};

class Customer : public Person {
public:
	Customer(string name, Date birthDate);
	Customer(string name, Date birthDate, unsigned int ID);
	float getMonthCost(unsigned int month) const;
	void attendLesson(GivenLesson * lesson, Date date, Time time); //adicionar aula (cliente foi a aula)
	void freeSwim(Time startTime, Date date, unsigned int duration); //adicionar uso em modo livre
	void addUse(PoolUse * pooluse); //o mesmo que a função de cima...
	bool attendedLesson(const GivenLesson * lesson);
	int getEntryNumber() const;
	vector <PoolUse *> getPoolUses();
private:
	vector <PoolUse *> uses;
};

class Teacher : public Person {
public:
	Teacher(string name, Date birthDate);
	Teacher(string name, Date birthDate, unsigned int ID);
	float getMonthCost(unsigned int month) const;
	int getNumberLessons() const;
	bool operator < (const Teacher & t2) const;
	void setLesson();
	int getEntryNumber() const;
private:
	int lessonsPerWeek;
};
#else
class Customer;
class Teacher;

#endif
