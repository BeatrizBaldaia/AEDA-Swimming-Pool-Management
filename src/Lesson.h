#pragma once

#include "Date.h"
#include "Person.h"

class Lesson {
public:
	static unsigned int duration = 60;

private:
	Teacher * teacher;
	Time time;
	DayOfWeek day;
};
