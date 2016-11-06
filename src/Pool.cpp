#include "Pool.h"

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

	if(teachers.size() > 20){
		quickSort(teachers);
	}
	else{
		insertionSort(teachers);
	}
}
