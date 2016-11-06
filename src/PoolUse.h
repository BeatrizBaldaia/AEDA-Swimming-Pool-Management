#ifndef _POOLUSE_H_
#define _POOLUSE_H_

#include "Date.h"
#include "Lesson.h"

class PoolUse {
public:
	PoolUse(Date d, Time t, unsigned int dur);
	Time getTime() const; //é para definir isto???
	int getMonth() const; //é para definir isto???
	virtual float getCost() const = 0;
protected:
	Date date;
	Time time;
	unsigned int duration;
};

class FreeSwimUse : public PoolUse {
public:
	FreeSwimUse (Date d, Time t, unsigned int dur);
	float getCost() const;
private:
	static float cost30;
};

class LessonUse : public PoolUse {
public:
	LessonUse (Date d, Time t, Lesson *l); //duração sempre 1 hora
	float getCost() const;
	Lesson * getLesson() const;
private:
	Lesson * lesson;

	static float lessonCost;
};

#endif
