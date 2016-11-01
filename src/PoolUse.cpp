#include "PoolUse.h"

LessonUse::LessonUse(Date d, Time t,Lesson *l) : PoolUse (d, t, 1){
	lesson = l;
}
void PoolUse::TimeDisplay2() const{
	time.TimeDisplay();
}

int LessonUse::getMonth2(){
	return date.getMonth();
}

Lesson * LessonUse::getLesson() const{
	return lesson;
}

float LessonUse::getCost() const{
	return costlesson;
}


void LessonUse::LessonDisplay() const{
	cout << "Lesson of ";
	lesson->ModalityDisplay();
	cout << " given by " << lesson->getTeacher() << " on ";
	lesson->DayDisplay();
	cout << " at ";
	PoolUse::TimeDisplay2();
	cout << endl << "    " << costlesson << endl;
}

float FreeSwimUse::getCost() const{
	unsigned int d = duration;
	float result;
	result = d/30 * cost30min;
	return result;
}
void FreeSwimUse::LessonDisplay() const{
	cout << duration << "minutes of Free Use" << endl << "    " << getCost();
}

int FreeSwimUse::getMonth2(){
	return date.getMonth();
}
