#ifndef _LESSON_H_
#define _LESSON_H_

#include <vector>
#include "Date.h"
#include "Person.h"

typedef pair <DayOfWeek, Time> LessonTime;

enum Modality {
	HydroGym, Zumba, AquaticPolo, ArtisticSwimming, CompetitiveSwimming, Learning
};

ostream & operator << (ostream & out, const Modality & m); //TODO: definir em .cpp
 //TODO: fazer o overload do operador << para Lesson

class Lesson {
public:
	Lesson(LessonTime lessonTime, Modality modality);
	static unsigned int duration;
	Teacher * getTeacher();
	void setTeacher(Teacher * teacher);

private:
	Teacher * teacher;
	Modality modality;
	LessonTime lessonTime;
};

#endif
