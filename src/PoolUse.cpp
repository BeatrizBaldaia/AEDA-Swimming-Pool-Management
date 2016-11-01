#include "PoolUse.h"

float FreeSwimUse::cost30 = 2.00;
float LessonUse::lessonCost = 3.00;

LessonUse::LessonUse(Date d, Time t, Lesson * l) : PoolUse (d, t, Lesson::duration) {
	lesson = l;
}

Lesson * LessonUse::getLesson() const{
	return lesson;
}

float LessonUse::getCost() const{
	return lessonCost;
}

float FreeSwimUse::getCost() const{
	float cost = (duration % 30) != 0 ? duration / 30 + 1 : duration / 30;
	return cost;
}

FreeSwimUse::FreeSwimUse(Date d, Time t, unsigned int dur) : PoolUse(d, t, dur) {

}
