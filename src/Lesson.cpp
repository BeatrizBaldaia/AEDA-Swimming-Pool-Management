#include "Lesson.h"

unsigned int GivenLesson::lastID = 0;

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

Lesson::Lesson() {
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

bool Lesson::operator == (const Lesson &lesson) const{
	return teacher == lesson.getTeacher() && modality == lesson.getModality() && lessonTime.first == lesson.getDayOfWeek() && lessonTime.second == lesson.getTime();
}
GivenLesson::GivenLesson(Lesson lesson, Date date) {
	this->lesson = lesson;
	this->date = date;
}

GivenLesson::GivenLesson(Lesson lesson, Date date, unsigned int ID) {
	this->lesson = lesson;
	this->date = date;
	if(ID > lastID) {
		lastID = ID;
	}
}

void GivenLesson::addCustomer(Customer* customer) {
	customers.push_back(customer);
}

unsigned int GivenLesson::getID() const {
	return ID;
}

Lesson GivenLesson::getLesson() const {
	return lesson;
}

Date GivenLesson::getDate() const {
	return date;
}

vector<Customer*> GivenLesson::getCustomers() const{
	return customers;
}

bool GivenLesson::operator == (const GivenLesson &givenlesson) const{
	return (lesson == givenlesson.getLesson() && date == givenlesson.getDate());
}
