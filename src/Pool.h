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
	vector <Teacher *> teachers; //Quando Pool � criado os vetores devem ser logo ordenados usando as fun��es sort;
	vector <Lesson *> schedule;  //Se o n�mero de elementos do vetor for inferior ou igual a 20 usar INSERTION SORT sen�o usar QUICK SORT
};  //Quando � criado um objeto Lesson � logo atribuido o professor

#else

class Pool;

#endif
