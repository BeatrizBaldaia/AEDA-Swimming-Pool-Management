#pragma once

#include "Date.h"
#include "Lesson.h"

class PoolUse {
public:
	PoolUse(Date d, Time t, unsigned int dur) : date(d), time(t), duration(dur) {}
	void TimeDisplay2() const;
	void LessonDisplay() const {} //DEIXAMOS PollUse COMO UMA CLASSE ABSTRATA???
	float getCost() const {return 0;} //tentei pôr abstrata e estava a dar erro na inicialização
	int getMonth2() {return 0;}
	Lesson * getLesson() const = 0;
protected:
	Date date;
	Time time;
	unsigned int duration;
};

class FreeSwimUse : public PoolUse {
public:
	FreeSwimUse (Date d, Time t, unsigned int dur) : PoolUse(d, t, dur) { cost30min = 2;} //2 euros meia hora de uso livre
	void LessonDisplay() const;
	float getCost() const;
	int getMonth2();
	Lesson * getLesson() const {return NULL;}
private:
	float cost30min;
};

class LessonUse : public PoolUse {
public:
	LessonUse (Date d, Time t, Lesson *l); //6 euros por aula, por exemplo, e duração sempre 1 hora
	void LessonDisplay() const;
	float getCost() const;
	int getMonth2();
	Lesson * getLesson() const;

private:
	Lesson * lesson;
	float costlesson;
};
