#ifndef _POOL_H_
#define _POOL_H_

#include "PoolUse"
#include "Person.h"
#include "Lesson.h"
#include "Sort.h"


class Pool {
public:
	vector<Lesson *> getTeacherLessons(string name);
	void addLesson(Lesson * lesson);
	int numberCostumerLesson(Lesson * lesson);
	int numberCostumerFree(Date day, Time startTime, Time endTime);
	Lesson * getLesson(DayOfWeek day, Time time) const; //usa exceção: try{...} catch(InvalidLesson x){cout << "There's no lesson on " << x.day << " at " << x.time;

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
#endif
