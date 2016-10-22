#pragma once

#include "Date.h"
#include "Lesson.h"

class PoolUse {
public:

private:
	Date date;
	unsigned int duration;
};

class FreeSwimUse : public PoolUse {
public:

private:

};

class LessonUse : public PoolUse {
public:

private:
	Lesson * lesson;
};
