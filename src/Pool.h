#ifndef _POOL_H_
#define _POOL_H_

#include "Person.h"
#include "Lesson.h"

class Pool {
public:

private:
	vector <Customer *> customers;
	vector <Teacher *> teachers;
	vector <Lesson *> schedule;
};

#endif
