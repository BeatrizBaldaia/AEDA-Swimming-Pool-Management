#ifndef _PERSON_H_
#define _PERSON_H_

#include <list>
#include <string>
#include <vector>

#include "Date.h"
#include "PoolUse.h"
#include "Shop.h"

using namespace std;

class ContactInfo {
private:
	string city;
	string street;
	int number;
	string postalCode;
	long cellphoneNum;
public:
	ContactInfo();
	ContactInfo(string city, string street, int number, string postalCode,
			long cellphoneNum);
	string getCity() const;
	string getStreet() const;
	int getNumber() const;
	string getPostalCode() const;
	void setCity(string city);
	void setStreet(string street);
	void setNumber(int number);
	void setPostalCode(string code);
	long getCellphoneNum() const;
	void setCellphoneNum(long cellphoneNum);
};

class Person {
public:
	Person(string name, Date birthDate, ContactInfo contactInfo);
	Person(string name, Date birthDate, unsigned int ID,
			ContactInfo contactInfo);

	string getName() const;
	unsigned int getID() const;
	Date getBirthDate() const;
	virtual int getEntryNumber() const = 0;
	void setName(string name);

	string getCity() const;
	string getStreet() const;
	int getNumber() const;
	string getPostalCode() const;
	long getCellphoneNum() const;
	void setCity(string city);
	void setStreet(string street);
	void setNumber(int number);
	void setPostalCode(string code);
	void setCellphoneNum(long cellphoneNum);

	static unsigned int lastID;
private:
	const unsigned int ID;
	string name;
	Date birthDate;
	ContactInfo contactInfo;

};

class Customer: public Person {
public:
	Customer(string name, Date birthDate, ContactInfo contactInfo);
	Customer(string name, Date birthDate, unsigned int ID,
			ContactInfo contactInfo);

	float getMonthCost(unsigned int month, unsigned int year) const;
	int getEntryNumber() const; /// frequência com que os clientes vão á piscina
	vector<PoolUse *> getPoolUses();

	void attendLesson(GivenLesson * lesson, Date date, Time time,
			double discount); ///adicionar aula (cliente foi a aula)
	void freeSwim(Time startTime, Date date, unsigned int duration,
			double discount); ///adicionar uso em modo livre
	void addUse(PoolUse * pooluse); ///adicionar uso em modo livre

	bool attendedLesson(const GivenLesson * lesson);
	void buyItem(vector<Item> items);
private:
	vector<PoolUse *> uses;
	list<Item> shopping;
};

class Teacher: public Person {
public:
	Teacher(string name, Date birthDate, ContactInfo contactInfo);
	Teacher(string name, Date birthDate, unsigned int ID,
			ContactInfo contactInfo);

	float getMonthCost(unsigned int month) const; ///possivel implementação para a segunda parte do projeto
	int getNumberLessons() const; ///numero de aulas por semana
	int getEntryNumber() const;

	void setLesson(); ///atribuir aula ao professor, e atribuir o mesmo número de aulas aos professores

	bool operator <(const Teacher & t2) const;
private:
	int lessonsPerWeek;
};
#else

class Customer;
class Teacher;

#endif
