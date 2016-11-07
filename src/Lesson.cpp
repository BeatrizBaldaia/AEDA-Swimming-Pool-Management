#include "Lesson.h"

unsigned int Lesson::duration = 60;

Lesson::Lesson(LessonTime lessonTime, Modality modality) : lessonTime(lessonTime){
    this->modality = modality;
}

Teacher * Lesson::getTeacher() const{
    return teacher;
}

void Lesson::setTeacher(Teacher * teacher){
    this->teacher = teacher;
}

DayOfWeek Lesson::getDayOfWeek() const{
    return lessonTime.first;
}

Time Lesson::getTime() const{
    return lessonTime.second;
}

Modality Lesson::getModality() const{
    return modality;
}

ostream & operator << (ostream & out, const Modality & m){
    switch (m){
        case HydroGym:
            out << "Hydro Gymnastic";
            break;
        case Zumba:
            out << "Zumba";
            break;
        case AquaticPolo:
            out << "Water Polo";
            break;
        case  ArtisticSwimming:
            out << "Synchronized Swimming";
            break;
        case CompetitiveSwimming:
            out << "Competitive Swimming";
            break;
        case Learning:
            out << "Technical Lessons";
            break;
        }

    return out;
}

ostream & operator << (ostream & out, const Lesson & lesson){
    out << lesson.getDayOfWeek() << " - " << lesson.getModality() << " at " << lesson.getTime() << " - " << lesson.getTeacher()->getName();
    return out;
}
