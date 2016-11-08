#include "Pool.h"
#include <algorithm>

static unsigned int Pool::maxCustomers = 20;

vector<Lesson *> Pool::getTeacherLessons(string name){
	vector<Lesson *> result;
	for(Lesson * x : schedule){
		if(x->getTeacher()->getName() == name){
			result.push_back(x);
		}
	}

	return result;
}

void Pool::addLesson(Lesson * lesson){
	lesson->setTeacher(teachers[0]); //estamos a retornar o professor com menos aulas dadas porque o vetor teachers já está ordenado
	schedule.push_back(lesson);
	teachers[0]->setLesson();

	sort(teachers.begin(),teachers.end(),[](Teacher * a, Teacher * b){return a->getNumberLessons() < b->getNumberLessons();});
}

int Pool::numberCostumerLesson(Lesson * lesson){
	int result = 0;
	for(Customer * x : customers){
		if(x->attendedLesson(lesson)){
			result++;
		}
	}

	return result;
}

int Pool::numberCostumerFree(Date day, Time startTime, Time endTime){
	int result = 0;
	for(const FreeSwimUse & x : freeuse){
		if(x.getDate() == day){
			if(x.getTime() > startTime && endTime > x.getTime()){  //TODO: ver se
				result++;                                         //o uso livre da
				break;                                            //piscina ocorreu
			}                                                    // no intervalo dado [startTime, endTime]
			else{
				if(startTime > x.getTime() && x.getTime())
			}
		}
	}
}

Lesson * Pool::getLesson(DayOfWeek day, Time time) const{
	for(Lesson * x : schedule){
		if(x->getDayOfWeek() == day && x->getTime() == time){
			return x;
		}
	}
	throw InvalidLesson(day, time);

}

/* EXCEÇÕES */

InvalidLesson::InvalidLesson(DayOfWeek day,Time time){
	this->day = day;
	this->time = time;
}
