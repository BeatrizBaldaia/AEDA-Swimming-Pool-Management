#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
#include <vector>

#include "Date.h"
#include "PoolUse.h"
#include "Lesson.h"

using namespace std;

class Person {
public:
	Person(string name, Date birthDate);
	Person(string name, Date birthDate, unsigned int ID);

	string getName() const;
	unsigned int getID() const;
	Date getBirthDate() const;
	virtual int getEntryNumber() const = 0;

	void setName(string name);

	static unsigned int lastID;
private:
	const unsigned int ID;
	string name;
	Date birthDate;
};

class Customer: public Person {
public:
	Customer(string name, Date birthDate);
	Customer(string name, Date birthDate, unsigned int ID);

	float getMonthCost(unsigned int month, unsigned int year) const;
	int getEntryNumber() const; /// frequência com que os clientes vão á piscina
	vector<PoolUse *> getPoolUses();

	void attendLesson(GivenLesson * lesson, Date date, Time time); ///adicionar aula (cliente foi a aula)
	void freeSwim(Time startTime, Date date, unsigned int duration); ///adicionar uso em modo livre
	void addUse(PoolUse * pooluse); ///adicionar uso em modo livre

	bool attendedLesson(const GivenLesson * lesson);
private:
	vector<PoolUse *> uses;
};

class Teacher: public Person {
public:
	Teacher(string name, Date birthDate);
	Teacher(string name, Date birthDate, unsigned int ID);

	float getMonthCost(unsigned int month) const;///possivel implementação para a segunda parte do projeto
	int getNumberLessons() const;///numero de aulas por semana
	int getEntryNumber() const;

	void setLesson();///atribuir aula ao professor, e atribuir o mesmo número de aulas aos professores

	bool operator <(const Teacher & t2) const;
private:
	int lessonsPerWeek;
};
#else

class Customer;
class Teacher;

#endif
