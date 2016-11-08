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

class Lesson {
public:
    Lesson(LessonTime lessonTime, Modality modality);
    static unsigned int duration;
    Teacher * getTeacher() const;
    void setTeacher(Teacher * teacher);
    DayOfWeek getDayOfWeek() const;
    Time getTime() const;
    Modality getModality() const;

private:
    Teacher * teacher;
    Modality modality;
    LessonTime lessonTime;
};

ostream & operator << (ostream & out, const Modality & m);
ostream & operator << (ostream & out, const Lesson & lesson);

#else
class Lesson;
#endif
