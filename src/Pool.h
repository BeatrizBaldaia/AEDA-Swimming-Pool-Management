#ifndef _POOL_H_
#define _POOL_H_

#include "PoolUse.h"
#include "Person.h"
#include "Lesson.h"


class Pool {
public:
	vector<Lesson> getLessonsByTeacher(string name);
	vector<GivenLesson *> getGivenLessons();
	GivenLesson * getGivenLesson(Lesson lesson, Date date);
	void addLesson(Lesson lesson);
	unsigned int CustomersInLesson(GivenLesson lesson);
	unsigned int CustomersFreeUse(Date date, Time time);
	Lesson getLesson(DayOfWeek day, Time time) const; //usa exceção: try{...} catch(InvalidLesson x){cout << "There's no lesson on " << x.day << " at " << x.time;
	vector<Customer *> getAllCustomer();
	Customer * getCustomer(string name); //usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer named " << x.name;
	Customer * getCustomer (unsigned int ID); //usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer with ID " << x.ID;
	void setName(string name);
	void setMaxCustomers(unsigned int n);
	string getName() const;
	unsigned int getMaxCustomers() const;
	Lesson getNextLesson(DayOfWeek day, Time time, bool & currentlesson) const;
	void setFileNames(vector <string> v);
	void addFreeUse(PoolUse * freeUse);

	void attendLesson(Lesson lesson, Customer * customer, Date date);
	void addFreeSwim(Customer * customer, Date date, Time time, unsigned int duration);

	void addCustomer(Customer * c);
	void addTeacher(Teacher * t);
	Teacher * getTeacher(unsigned int ID);

	void load();
	void write();

	void loadPoolInfo();
	void loadCustomers();
	void loadTeachers();
	void loadSchedule();
	void loadGivenLessons();

	void writePoolInfo();
	void writeCustomers();
	void writeTeachers();
	void writeSchedule();
	void writeGivenLessons();
private:
	vector <Customer *> customers;
	vector <Teacher *> teachers; //Quando Pool é criado os vetores devem ser logo ordenados usando as funções sort;
	vector <Lesson> schedule;     //Se o número de elementos do vetor for inferior ou igual a 20 usar INSERTION SORT senão usar QUICK SORT
	vector <GivenLesson *> givenLessons;
	vector <PoolUse *> freeUses; //sempre que alguem que usar a piscina em modo livre, o uso é guardado neste vetor; usar freeuses.insert(freeuses.begin(), PoolUse * objeto) e não freeuses.push_back(...) para termos sempre os objetos mais recentes no inicio

	vector <string> fileNames;
	// 0 poolinfo
	// 1 customers
	// 2 teachers
	// 3 schedule
	// 4 givenlessons
	// 5 freeuses

	string name;
	unsigned int maxCustomers;
};

class NoMoreLesson{
public:
	NoMoreLesson();
};

class InvalidLesson{
public:
	InvalidLesson(DayOfWeek day,Time time);
	DayOfWeek day;
	Time time;
};

class NonExistentCustomerName{
public:
	NonExistentCustomerName(string name);
	string name;
};

class NonExistentCustomerID{
public:
	NonExistentCustomerID(unsigned int ID);
	unsigned int ID;
};

#else

class Pool;

#endif
