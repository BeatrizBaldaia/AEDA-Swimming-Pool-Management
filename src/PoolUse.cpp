#include "PoolUse.h"

#include <stddef.h>

#include "Lesson.h"

float FreeSwimUse::cost30 = 2.00;
float LessonUse::lessonCost = 3.00;

/* POOL_USE */

PoolUse::PoolUse(Date d, Time t, unsigned int dur) {
	date = d;
	time = t;
	duration = dur;
}

Time PoolUse::getTime() const {
	return time;
}

Date PoolUse::getDate() const {
	return date;
}

unsigned int PoolUse::getDuration() const {
	return duration;
}

/* LESSON_USE */

LessonUse::LessonUse(Date d, Time t, GivenLesson * l) :
		PoolUse(d, t, Lesson::duration) {
	lesson = l;
}

GivenLesson * LessonUse::getLesson() const {
	return lesson;
}

float LessonUse::getCost() const {
	return lessonCost;
}

/* FREE_SWIM_USE */

FreeSwimUse::FreeSwimUse(Date d, Time t, unsigned int dur) :
		PoolUse(d, t, dur) {
}

float FreeSwimUse::getCost() const {
	float cost = (getDuration() % 30) != 0 ? getDuration() / 30 + 1 : getDuration() / 30;
	cost *= cost30;
	return cost;
}

GivenLesson * FreeSwimUse::getLesson() const {
	return NULL;
}
