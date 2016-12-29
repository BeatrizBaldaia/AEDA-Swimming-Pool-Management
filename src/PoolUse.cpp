#include "PoolUse.h"

#include <stddef.h>


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

LessonUse::LessonUse(Date d, Time t, GivenLesson * l, double discount) :
		PoolUse(d, t, Lesson::duration) {
	this->discount = discount;
	lesson = l;
	currentCost = lessonCost - (lessonCost*discount);///se nao esta a haver nehuma campanha promocional o desconto vai ser de 0, ou seja, nao ha desconto
}

GivenLesson * LessonUse::getLesson() const {
	return lesson;
}

float LessonUse::getCost() const {
	return currentCost;
}

/* FREE_SWIM_USE */

FreeSwimUse::FreeSwimUse(Date d, Time t, unsigned int dur, double discount) :
						PoolUse(d, t, dur) {
	this->discount = discount;
	float cost = (getDuration() % 30) != 0 ? getDuration() / 30 + 1 : getDuration() / 30;
	cost *= cost30;
	currentCost = cost - (cost*discount);///se nao esta a haver nehuma campanha promocional o desconto vai ser de 0, ou seja, nao ha desconto
}

float FreeSwimUse::getCost() const {
	return currentCost;
}

GivenLesson * FreeSwimUse::getLesson() const {
	return NULL;
}
