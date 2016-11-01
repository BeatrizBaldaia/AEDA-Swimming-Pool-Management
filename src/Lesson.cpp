#include "Lesson.h"

unsigned int Lesson::duration = 60;

Lesson::Lesson(LessonTime lessonTime, Modality modality){
	this->lessonTime = lessonTime;
	this->modality = modality;
}
Teacher * Lesson::getTeacher(){
	return teacher;
}







