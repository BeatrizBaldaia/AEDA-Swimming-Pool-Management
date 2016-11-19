#ifndef _POOL_H_
#define _POOL_H_

#include <string>
#include <vector>

#include "Date.h"
#include "Lesson.h"
#include "Person.h"
#include "PoolUse.h"

class Pool {
public:
	unsigned int getMaxCustomers() const;
	Lesson getNextLesson(DayOfWeek day, Time time, bool & currentlesson) const;
	vector<Lesson> getLessons(unsigned int ID); /// retorna vetor com as aulas dadas por um professor
	vector<Lesson> getLessons(Date date, Time time);
	vector<GivenLesson *> getGivenLessons(); /// dá o vetor givenLessons
	vector<GivenLesson *> getGivenLessons(unsigned int ID);
	GivenLesson * getGivenLesson(Lesson lesson, Date date); /// dá GivenLesson que tem uma certa Lesson e ocorreu num certo Date
	void addLesson(Lesson lesson); /// adiciona aula ao vetor schedule e atribui a mesma um professor
	unsigned int CustomersInLesson(GivenLesson lesson); /// dá o número de clientes numa certa aula
	unsigned int CustomersFreeUse(Date date, Time time); /// dá o número de clientes a usar a piscina numa certa data e tempo
	Lesson getLesson(DayOfWeek day, Time time) const; //usa exceção: try{...} catch(InvalidLesson x){cout << "There's no lesson on " << x.day << " at " << x.time;
	vector<Customer *> getCustomers(); /// retorna vetor customers
	Customer * getCustomer(string name); //usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer named " << x.name;
	Customer * getCustomer(unsigned int ID); //usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer with ID " << x.ID;
	void setName(string name); ///dá nome a piscina
	void setMaxCustomers(unsigned int n); /// define o numero maximo de pessoas na piscina
	string getName() const; ///dá nome da piscina
	vector<Lesson> getSchedule() const;
	vector<Teacher *> getTeachers() const;

	void setFileNames(vector<string> v);
	void addFreeUse(PoolUse * freeUse);

	void attendLesson(Lesson lesson, Customer * customer, Date date);
	void addFreeSwim(Customer * customer, Date date, Time time,
			unsigned int duration);

	void removeCustomer(unsigned int ID);
	void removeTeacher(unsigned int ID);

	void addCustomer(Customer * c);
	void addTeacher(Teacher * t);
	Teacher * getTeacher(unsigned int ID);

	void load();
	void loadPoolInfo();
	void loadCustomers();
	void loadTeachers();
	void loadSchedule();
	void loadGivenLessons();

	void write();
	void writePoolInfo();
	void writeCustomers();
	void writeTeachers();
	void writeSchedule();
	void writeGivenLessons();
private:
	vector<Customer *> customers;
	vector<Teacher *> teachers; //Quando Pool é criado os vetores devem ser logo ordenados usando as funções sort;
	vector<Lesson> schedule; //Se o número de elementos do vetor for inferior ou igual a 20 usar INSERTION SORT senão usar QUICK SORT
	vector<GivenLesson *> givenLessons;
	vector<PoolUse *> freeUses; //sempre que alguem que usar a piscina em modo livre, o uso é guardado neste vetor; usar freeuses.insert(freeuses.begin(), PoolUse * objeto) e não freeuses.push_back(...) para termos sempre os objetos mais recentes no inicio

	vector<string> fileNames;
	// 0 poolinfo
	// 1 customers
	// 2 teachers
	// 3 schedule
	// 4 givenlessons
	// 5 freeuses

	string name;
	unsigned int maxCustomers;
};

class NoMoreLessonsInDay {
public:
	NoMoreLessonsInDay();
};

class InvalidLesson {
public:
	InvalidLesson(DayOfWeek day, Time time);
	DayOfWeek day;
	Time time;
};

class NonExistentCustomerName {
public:
	NonExistentCustomerName(string name);
	string name;
};

class NonExistentCustomerID {
public:
	NonExistentCustomerID(unsigned int ID);
	unsigned int ID;
};

class NonExistentTeacherID {
public:
	NonExistentTeacherID(unsigned int ID);
	unsigned int ID;
};

class NotSameDayAsDate {
public:
	NotSameDayAsDate();
};

class NonExistentGivenLesson {
public:
	NonExistentGivenLesson(Lesson lesson, Date date);
	Lesson lesson;
	Date date;
};

class CustomerAlreadyAttendedLesson {

};

#else

class Pool;

#endif
