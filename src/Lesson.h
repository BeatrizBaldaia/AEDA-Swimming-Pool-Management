#ifndef _LESSON_H_
#define _LESSON_H_

#include <iostream>
#include <utility>
#include <vector>

#include "Date.h"
#include "Person.h"

typedef pair<DayOfWeek, Time> LessonTime;
/**
 * enumeração com tipos de modalidade usadas na piscina
 */
enum Modality {
	HydroGym,           //!< HydroGym
	Zumba,              //!< Zumba
	AquaticPolo,        //!< AquaticPolo
	ArtisticSwimming,   //!< ArtisticSwimming
	CompetitiveSwimming,   //!< CompetitiveSwimming
	Learning            //!< Learning
};

class Lesson {
public:
	Lesson(LessonTime lessonTime, Modality modality);
	Lesson();
	static unsigned int duration;
	Teacher * getTeacher() const;        ///aceder ao professor atribuido a aula
	void setTeacher(Teacher * teacher);
	DayOfWeek getDayOfWeek() const; ///retorna o dia da semana em que a aula é dada
	Time getTime() const;            ///retorna hora da aula
	Modality getModality() const;            ///retorna modalidade da aula
	bool operator ==(const Lesson &lesson) const;
	bool operator <(const Lesson& lesson) const;
private:
	Teacher * teacher;
	Modality modality;
	LessonTime lessonTime;
};

class GivenLesson {
public:
	GivenLesson(Lesson lesson, Date date);
	GivenLesson(Lesson lesson, Date date, unsigned int ID);
	void addCustomer(Customer * customer); ///função usada no menu de adicionar aulas a clientes
	unsigned int getID() const;
	Lesson getLesson() const;
	Date getDate() const;
	void removeCustomer(unsigned int ID); ///remove um customer de uma givenLesson
	vector<Customer *> getCustomers() const; ///retorna todos os clientes que foram a aula
	bool operator ==(const GivenLesson &givenlesson) const;
	static unsigned int lastID; ///ultimo id atribuido a uma givenlesson
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
