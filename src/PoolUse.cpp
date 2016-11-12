#include "PoolUse.h"

float FreeSwimUse::cost30 = 2.00;
float LessonUse::lessonCost = 3.00;

/* POOL_USE */

PoolUse::PoolUse(Date d, Time t, unsigned int dur){
	date=d;
	time=t;
	duration=dur;
}

Time PoolUse::getTime() const{
	return time;
}

Date PoolUse::getDate() const{
	return date;
}
/* LESSON_USE */

LessonUse::LessonUse(Date d, Time t, GivenLesson * l) : PoolUse (d, t, Lesson::duration) {
	lesson = l;
}

GivenLesson * LessonUse::getLesson() const{
	return lesson;
}

float LessonUse::getCost() const{
	return lessonCost;
}

 /* FREE_SWIM_USE */

FreeSwimUse::FreeSwimUse(Date d, Time t, unsigned int dur) : PoolUse(d, t, dur) {}

float FreeSwimUse::getCost() const{
	float cost = (duration % 30) != 0 ? duration / 30 + 1 : duration / 30;
	return cost;
}

GivenLesson * FreeSwimUse::getLesson() const{
	return NULL;
}

unsigned int PoolUse::getDuration() const {
	return duration;
}
