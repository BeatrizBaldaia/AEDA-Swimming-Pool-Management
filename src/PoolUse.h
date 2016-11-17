#ifndef _POOLUSE_H_
#define _POOLUSE_H_

#include "Date.h"

class GivenLesson;

class PoolUse {
public:
	PoolUse(Date d, Time t, unsigned int dur);
	Time getTime() const;
	Date getDate() const;
	unsigned int getDuration() const;
	virtual float getCost() const = 0;
	virtual GivenLesson * getLesson() const = 0;

protected:
	Date date;
	Time time;
	unsigned int duration;
};

class FreeSwimUse: public PoolUse {
public:
	FreeSwimUse(Date d, Time t, unsigned int dur);
	float getCost() const;
	GivenLesson * getLesson() const;
	unsigned int getDuration() const;
private:
	static float cost30;
};

class LessonUse: public PoolUse {
public:
	LessonUse(Date d, Time t, GivenLesson *l); //duração sempre 1 hora
	float getCost() const;
	GivenLesson * getLesson() const;
	unsigned int getDuration() const;
private:
	GivenLesson * lesson;

	static float lessonCost;
};

#else
class PoolUse;
class FreeSwimUse;
class LessonUse;

#endif
