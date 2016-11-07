#ifndef _POOL_H_
#define _POOL_H_

#include "Person.h"
#include "Lesson.h"


class Pool {
public:
	vector<Lesson *> getTeacherLessons(string name);
	void addLesson(Lesson * lesson);

private:
	vector <Customer *> customers;
	vector <Teacher *> teachers; //Quando Pool é criado os vetores devem ser logo ordenados usando as funções sort;
	vector <Lesson *> schedule;  //Se o número de elementos do vetor for inferior ou igual a 20 usar INSERTION SORT senão usar QUICK SORT
};  //Quando é criado um objeto Lesson é logo atribuido o professor

#else

class Pool;

#endif
