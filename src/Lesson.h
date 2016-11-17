#ifndef _LESSON_H_
#define _LESSON_H_

#include <iostream>
#include <utility>
#include <vector>

#include "Date.h"
#include "Person.h"

typedef pair<DayOfWeek, Time> LessonTime;

enum Modality {
	HydroGym,
	Zumba,
	AquaticPolo,
	ArtisticSwimming,
	CompetitiveSwimming,
	Learning
};

class Lesson {
public:
	Lesson(LessonTime lessonTime, Modality modality);
	Lesson();
	static unsigned int duration;
	Teacher * getTeacher() const;
	void setTeacher(Teacher * teacher);
	DayOfWeek getDayOfWeek() const;
	Time getTime() const;
	Modality getModality() const;
	bool operator ==(const Lesson &lesson) const;

private:
	Teacher * teacher;
	Modality modality;
	LessonTime lessonTime;
};

class GivenLesson {
public:
	GivenLesson(Lesson lesson, Date date);
	GivenLesson(Lesson lesson, Date date, unsigned int ID);
	void addCustomer(Customer * customer); //função usada no menu de adicionar aulas a clientes
	unsigned int getID() const;
	Lesson getLesson() const;
	Date getDate() const;
	vector<Customer *> getCustomers() const;
	bool operator ==(const GivenLesson &givenlesson) const;
	static unsigned int lastID;
private:
	Lesson lesson;
	Date date;
	vector<Customer *> customers;
	unsigned int ID;
};

ostream & operator <<(ostream & out, const Modality & m);
ostream & operator <<(ostream & out, const Lesson & lesson);

#else
class Lesson;
class GivenLesson;
#endif
