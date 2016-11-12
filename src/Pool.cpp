#include "Pool.h"
#include <algorithm>
#include <fstream>

vector<Lesson> Pool::getLessonsByTeacher(string name){
	vector<Lesson> result;
	for(Lesson & x : schedule){
		if(x.getTeacher()->getName() == name){
			result.push_back(x);
		}
	}

	return result;
}

void Pool::setName(string name){
	this->name = name;
}

void Pool::addLesson(Lesson lesson){
	lesson.setTeacher(teachers[0]); //estamos a retornar o professor com menos aulas dadas porque o vetor teachers já está ordenado
	schedule.push_back(lesson);
	teachers[0]->setLesson();

	sort(teachers.begin(),teachers.end(),[](Teacher * a, Teacher * b){return a->getNumberLessons() < b->getNumberLessons();});
}

unsigned int Pool::CostumersInLesson(GivenLesson lesson){
	return lesson.getCustomers().size();
}

Lesson Pool::getLesson(DayOfWeek day, Time time) const{
	for(const Lesson & x : schedule){
		if(x.getDayOfWeek() == day && x.getTime() == time){
			return x;
		}
	}
	throw InvalidLesson(day, time);

}


vector<Customer *> Pool::getAllCostumer() const{
	vector<Customer *> result;
	for(Customer * x : customers){
		result.push_back(x);
	}
	sort(result.begin(),result.end(),[](Customer * a, Customer * b){return a->getEntryNumber() < b->getEntryNumber();});

	return result;
}

Customer * Pool::getCostumer(string name) const{
	for(Customer * x : customers){
		if(x->getName() == name){
			return x;
		}
	}

	throw NonExistentCustomerName(name);

}

Customer * Pool::getCostumer(unsigned int ID) const{
	for(Customer * x : customers){
		if(x->getID() == ID){
			return x;
		}
	}

	throw NonExistentCustomerID(ID);
}

/* EXCEÇÕES */

NoMoreLesson::NoMoreLesson(){

}

InvalidLesson::InvalidLesson(DayOfWeek day,Time time){
	this->day = day;
	this->time = time;
}

NonExistentCustomerName::NonExistentCustomerName(string name){
	this->name = name;
}

NonExistentCustomerID::NonExistentCustomerID(unsigned int ID){
	this->ID = ID;
}

///////////////////////////////////////////////////////////////////////////

void Pool::setMaxCustomers(unsigned int n) {
	maxCustomers = n;
}

string Pool::getName() const {
	return name;
}

unsigned int Pool::getMaxCustomers() const {
	return maxCustomers;
}

void Pool::setFileNames(vector<string> v) {
	fileNames = v;
}

void Pool::writePoolInfo() {
	ofstream poolInfoFile(fileNames[0]);
	poolInfoFile << name;
	poolInfoFile << ";";
	poolInfoFile << maxCustomers;
}

void Pool::writeCustomers() {
	ofstream customersFile(fileNames[1]);
	customersFile << customers.size() << endl;
	for(Customer * i : customers) {
		customersFile << i->getID() << ";";
		customersFile << i->getName() << ";";
		customersFile << i->getBirthDate() << ";";
		vector <PoolUse *> FreeSwimUses;
		for(PoolUse * j : i->getPoolUses()) {
			if(j->getLesson() == NULL) {
				FreeSwimUses.push_back(j);
			}
		}
		customersFile << FreeSwimUses.size() << endl;
		for(PoolUse * j : FreeSwimUses) {
			customersFile << j->getDate() << ";";
			customersFile << j->getTime() << ";";
			customersFile << j->getDuration() << endl;
		}
	}
}

void Pool::writeTeachers() {
	ofstream teachersFile(fileNames[1]);
	teachersFile << teachers.size() << endl;
	for(Teacher * i : teachers) {
		teachersFile << i->getID() << ";";
		teachersFile << i->getName() << ";";
		teachersFile << i->getBirthDate() << endl;
	}
}

void Pool::writeSchedule() {
	ofstream scheduleFile(fileNames[1]);
	scheduleFile << schedule.size() << endl;
	for(const Lesson & i : schedule) {
		scheduleFile << i.getTeacher()->getID() << ";";
		int mod = i.getModality();
		scheduleFile << mod << ";";
		int day = i.getDayOfWeek();
		scheduleFile << day << ";";
		scheduleFile << i.getTime() << endl;
	}
}

void Pool::write() {
	writePoolInfo();
	writeCustomers();
	writeTeachers();
	writeSchedule();
	writeGivenLessons();
}

void Pool::writeGivenLessons() {
	ofstream givenLessonsFile(fileNames[1]);
	givenLessonsFile << givenLessons.size() << endl;
	for(GivenLesson & i : givenLessons) {
		givenLessonsFile << i.getID() << ";";
		givenLessonsFile << i.getLesson().getTeacher()->getID() << ";";
		int mod = i.getLesson().getModality();
		givenLessonsFile << mod << ";";
		int day = i.getLesson().getDayOfWeek();
		givenLessonsFile << day << ";";
		givenLessonsFile << i.getLesson().getTime() << ";";
		givenLessonsFile << i.getDate() << ";";
		for(Customer * j : i.getCustomers()) {
			if(j == i.getCustomers().back()) {
				givenLessonsFile << j->getID();
			} else {
				givenLessonsFile << j->getID() << " ";
			}
		}
		givenLessonsFile << endl;
	}
}

Lesson Pool::getNextLesson(DayOfWeek day, Time time) const{ //Ia usar esta função para o menu PoolOccupation para obter a aula que estava a ocorrer ou a próxima aula que ia começar
	unsigned int gap= 100000;
	bool excecao = true;
	Lesson next;
	for(Lesson x : schedule){
		if(x.getDayOfWeek() == day){
			if(x.getTime() < time){
				if((x.getTime() - time) < 60){ //aula que inda está a decorrer
					return x;
				}
			}
			else{
				if((x.getTime()-time) < gap){ //nao percebo porque que aqui dá erro visto que o overload do operador - da classe Time retorna um unsigned int
					gap = x.getTime()-time;
					next = x;
					excecao = false;
				}
			}
		}
	}
	if (excecao){ //neste dia não há mais aulas
		throw NoMoreLesson();
	}

	return next;
}
