#ifndef _LESSON_H_
#define _LESSON_H_

#include <vector>
#include "Date.h"
#include "Person.h"
#include "Pool.h"

typedef pair <DayOfWeek, Time> LessonTime;

enum Modality {
	HydroGym, Zumba, AquaticPolo, ArtisticSwimming, CompetitiveSwimming, Learning
};

ostream & operator << (ostream & out, const Modality & m);
ostream & operator << (ostream & out, const Lesson & lesson);

class Lesson {
public:
	Lesson(LessonTime lessonTime, Modality modality);
	static unsigned int duration;
	Teacher * getTeacher();
	void setTeacher(Teacher * teacher);
	DayOfWeek getDayOfWeek() const;
	Time getTime() const;
	Modality getModality() const;

private:
	Teacher * teacher;
	Modality modality;
	LessonTime lessonTime;
};

#endif
