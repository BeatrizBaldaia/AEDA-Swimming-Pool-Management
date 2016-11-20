#ifndef _POOLUSE_H_
#define _POOLUSE_H_

#include "Lesson.h"


class PoolUse {
public:
	PoolUse(Date d, Time t, unsigned int dur);
	Time getTime() const;///retorna hora do uso
	Date getDate() const;///retorna data do uso
	unsigned int getDuration() const;
	virtual float getCost() const = 0;
	virtual GivenLesson * getLesson() const = 0;

private:
	Date date;
	Time time;
	unsigned int duration;
};

class FreeSwimUse: public PoolUse {
public:
	FreeSwimUse(Date d, Time t, unsigned int dur);///retorna dura��o do uso livre
	float getCost() const;///retorna pre�o do uso livre
	GivenLesson * getLesson() const;
private:
	static float cost30;
};

class LessonUse: public PoolUse {
public:
	LessonUse(Date d, Time t, GivenLesson *l); ///dura��o sempre 1 hora
	float getCost() const;///retorna pre�o da aula dada (est�tico)
	GivenLesson * getLesson() const;
private:
	GivenLesson * lesson;

	static float lessonCost;
};

#else
class PoolUse;
class FreeSwimUse;
class LessonUse;

#endif
