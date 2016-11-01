#pragma once

#include "Person.h"
#include "Lesson.h"

class Pool {
public:

private:
	vector <Customer *> customers;
	vector <Teacher *> teachers;
	vector <Lesson *> schedule;
};
