#ifndef _POOL_H_
#define _POOL_H_

#include "PoolUse"
#include "Person.h"
#include "Lesson.h"


class Pool {
public:
	vector<Lesson *> getTeacherLessons(string name);
	void addLesson(Lesson * lesson);
	unsigned int numberCostumerLesson(Lesson * lesson);
	unsigned int numberCostumerFree(Date day, Time startTime, Time endTime);
	Lesson * getLesson(DayOfWeek day, Time time) const; //usa exceção: try{...} catch(InvalidLesson x){cout << "There's no lesson on " << x.day << " at " << x.time;
	vector<Customer *> getAllCostumer() const;
	Customer * getCostumer(string name) const; //usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer named " << x.name;
	Customer * getCostumer (unsigned int ID) const; //usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer with ID " << x.ID;
private:
	vector <Customer *> customers;
	vector <Teacher *> teachers; //Quando Pool é criado os vetores devem ser logo ordenados usando as funções sort;
	vector <Lesson *> schedule;     //Se o número de elementos do vetor for inferior ou igual a 20 usar INSERTION SORT senão usar QUICK SORT
	vector <FreeSwimUse> freeuse; //Quando é criado um objeto Lesson é logo atribuido o professor
	static unsigned int maxCustomers;
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
