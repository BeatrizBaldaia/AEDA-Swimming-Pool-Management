#ifndef _POOLUSE_H_
#define _POOLUSE_H_

#include "Date.h"
#include "Lesson.h"

class PoolUse {
public:
	PoolUse(Date d, Time t, unsigned int dur) : date(d), time(t), duration(dur) {}; // TODO pass to .cpp
	Time getTime() const;
	int getMonth() const;
	virtual float getCost() const = 0;
protected:
	Date date;
	Time time;
	unsigned int duration;
};

class FreeSwimUse : public PoolUse {
public:
	FreeSwimUse (Date d, Time t, unsigned int dur); // TODO pass to .cpp 2 euros meia hora de uso livre
	float getCost() const;
private:
	static float cost30;
};

class LessonUse : public PoolUse {
public:
	LessonUse (Date d, Time t, Lesson *l); //6 euros por aula, por exemplo, e duração sempre 1 hora
	float getCost() const;
	Lesson * getLesson() const;
private:
	Lesson * lesson;

	static float lessonCost;
};

#endif
