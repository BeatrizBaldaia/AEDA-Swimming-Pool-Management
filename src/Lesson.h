#pragma once

#include "Date.h"
#include "Person.h"
#include "Class.h"

class Lesson {
public:
	Lesson(DayOfWeek d, Modality m); //na fun��o main pedimos para digitarem uma data (classe Date) e usamos a fun��o day_of_week para obtermos o dia da semana
	static unsigned int duration = 60;
	string getTeacher() const;
	void TimeDisplay() const;
	void DayDisplay() const; //usar switch case
	void ModalityDisplay() const; //usar switch case
private:
	Teacher * teacher;
	DayOfWeek day;
	Modality modality;
};
