#ifndef _POOL_H_
#define _POOL_H_

#include "Person.h"
#include "Lesson.h"

//TODO: uma função que seleciona um professor para o objeto da classe Lesson criado para que depois o mesmo possa ser colocado no vetor schedule

class Pool {
public:
	vector<Lesson *> getTeacherLessons(string name); //TODO
private:
	vector <Customer *> customers;
	vector <Teacher *> teachers;
	vector <Lesson *> schedule;
};

#endif
