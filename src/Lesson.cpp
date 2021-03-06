#include "Lesson.h"

#include <algorithm>
#include <iterator>
#include <string>

unsigned int GivenLesson::lastID = 0;

unsigned int Lesson::duration = 60;

Lesson::Lesson(LessonTime lessonTime, Modality modality) :
		lessonTime(lessonTime) {
	this->modality = modality;
}

Teacher * Lesson::getTeacher() const {
	return teacher;
}

void Lesson::setTeacher(Teacher * teacher) {
	this->teacher = teacher;
}

DayOfWeek Lesson::getDayOfWeek() const {
	return lessonTime.first;
}

Time Lesson::getTime() const {
	return lessonTime.second;
}

Lesson::Lesson() {
}

Modality Lesson::getModality() const {
	return modality;
}

ostream & operator <<(ostream & out, const Modality & m) {
	switch (m) {
	case HydroGym:
		out << "Hydro Gymnastic";
		break;
	case Zumba:
		out << "Zumba";
		break;
	case AquaticPolo:
		out << "Aquatic Polo";
		break;
	case ArtisticSwimming:
		out << "Artistic Swimming";
		break;
	case CompetitiveSwimming:
		out << "Competitive Swimming";
		break;
	case Learning:
		out << "Learning";
		break;
	}

	return out;
}

ostream & operator <<(ostream & out, const Lesson & lesson) {
	out << lesson.getDayOfWeek() << " - " << lesson.getModality() << " at "
			<< lesson.getTime() << " - " << lesson.getTeacher()->getName();
	return out;
}

bool Lesson::operator ==(const Lesson &lesson) const {
	return teacher == lesson.getTeacher() && modality == lesson.getModality()
			&& lessonTime.first == lesson.getDayOfWeek()
			&& lessonTime.second == lesson.getTime();
}
GivenLesson::GivenLesson(Lesson lesson, Date date) {
	this->ID = lastID + 1;
	this->lesson = lesson;
	this->date = date;
	lastID++;
}

GivenLesson::GivenLesson(Lesson lesson, Date date, unsigned int ID) {
	this->lesson = lesson;
	this->date = date;
	this->ID = ID;
	if (ID > lastID) {
		lastID = ID;
	}
}

void GivenLesson::addCustomer(Customer* customer) {
	if (find(customers.begin(), customers.end(), customer) == customers.end()) {
		customers.push_back(customer);
	}
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

vector<Customer*> GivenLesson::getCustomers() const {
	return customers;
}

void GivenLesson::removeCustomer(unsigned int ID) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i]->getID() == ID)
			customers.erase(customers.begin() + i);
	}
}

bool GivenLesson::operator ==(const GivenLesson &givenlesson) const {
	return (lesson == givenlesson.getLesson() && date == givenlesson.getDate());
}

bool Lesson::operator <(const Lesson& lesson) const {
	if (getDayOfWeek() < lesson.getDayOfWeek()) {
		return true;
	} else if (getDayOfWeek() > lesson.getDayOfWeek()) {
		return false;
	} else {
		if (getTime() < lesson.getTime()) {
			return true;
		} else {
			return false;
		}
	}
}
