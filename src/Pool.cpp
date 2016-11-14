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
	poolInfoFile.close();
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
	customersFile.close();
}

void Pool::writeTeachers() {
	ofstream teachersFile(fileNames[2]);
	teachersFile << teachers.size() << endl;
	for(Teacher * i : teachers) {
		teachersFile << i->getID() << ";";
		teachersFile << i->getName() << ";";
		teachersFile << i->getBirthDate() << endl;
	}
	teachersFile.close();
}

void Pool::writeSchedule() {
	ofstream scheduleFile(fileNames[3]);
	scheduleFile << schedule.size() << endl;
	for(const Lesson & i : schedule) {
		scheduleFile << i.getTeacher()->getID() << ";";
		int mod = i.getModality();
		scheduleFile << mod << ";";
		int day = i.getDayOfWeek();
		scheduleFile << day << ";";
		scheduleFile << i.getTime() << endl;
	}
	scheduleFile.close();
}

void Pool::writeGivenLessons() {
	ofstream givenLessonsFile(fileNames[4]);
	givenLessonsFile << givenLessons.size() << endl;
	for(GivenLesson * i : givenLessons) {
		givenLessonsFile << i->getID() << ";";
		givenLessonsFile << i->getLesson().getTeacher()->getID() << ";";
		int mod = i->getLesson().getModality();
		givenLessonsFile << mod << ";";
		int day = i->getLesson().getDayOfWeek();
		givenLessonsFile << day << ";";
		givenLessonsFile << i->getLesson().getTime() << ";";
		givenLessonsFile << i->getDate() << ";";
		for(Customer * j : i->getCustomers()) {
			if(j == i->getCustomers().back()) {
				givenLessonsFile << j->getID();
			} else {
				givenLessonsFile << j->getID() << " ";
			}
		}
		givenLessonsFile << endl;
	}
	givenLessonsFile.close();
}

void Pool::writeFreeUses(){
	ofstream freeusesFile(fileNames[5]);
	freeusesFile << freeuses.size() << endl;
	for(PoolUse * i : freeuses) {
		freeusesFile << i->getDate() << ";";
		freeusesFile << i->getTime() << ";";
		freeusesFile << i->getDuration() << endl;
	}
	freeusesFile.close();
}

void Pool::write() {
	writePoolInfo();
	writeCustomers();
	writeTeachers();
	writeSchedule();
	writeGivenLessons();
}



vector<GivenLesson *> Pool::getGivenLessons(){
	return givenLessons;
}

Lesson Pool::getNextLesson(DayOfWeek day, Time time, bool & currentlesson) const{ //Ia usar esta função para o menu PoolOccupation para obter a aula que estava a ocorrer ou a próxima aula que ia começar
	unsigned int gap= 100000;
	bool excecao = true;
	Lesson next;
	for(Lesson x : schedule){
		if(x.getDayOfWeek() == day){
			if(x.getTime() < time){
				if(x.getTime().getTimeGap(time) < 60){ //aula que inda está a decorrer
					currentlesson = true;
					return x;
				}
			}
			else{
				if(x.getTime().getTimeGap(time) < gap){ //nao percebo porque que aqui dá erro visto que o overload do operador - da classe Time retorna um unsigned int
					gap = x.getTime().getTimeGap(time);
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

unsigned int Pool::CostumersFreeUse(Date date, Time time){
	unsigned int result = 0;
	for(PoolUse * x : freeuses){
		if(x->getDate() == date){
			if(x->getTime() < time){
				if(x->getTime().getTimeGap(time) < x->getDuration()){ //pessoa ainda a usar a piscina em modo livre
					result++;
				}
			}
		}
	}

	return result;
}

void Pool::addFreeUse(PoolUse * freeUse){
	freeuses.insert(freeuses.begin(), freeUse);
}

void Pool::showCurrentOcupation ()
{
	Moment moment = getCurrentMoment();
	WeekMoment weekMoment = getCurrentWeekMoment();
	GivenLesson * currentLesson = 0;
	for(GivenLesson * x : givenLessons)
	{
		if (weekMoment.first == x->getLesson().getDayOfWeek())
		{
			if(weekMoment.second >= x->getLesson().getTime() && weekMoment.second <= x->getLesson().getTime() + x->getLesson().duration)
			{
				// TODO currentLesson = * x;  //help
			}
		}
	}
	if (currentLesson != 0)
	{
		cout << "\nCustomers present in ";
		cout << currentLesson->getLesson().getModality();
		cout << " class:\n";
		for (Customer * x : currentLesson) //TODO help
		{
			cout << x->getName();
			cout << endl;
		}
	}
	int nocustomersflag = 1;
	cout << "\nCustomers in freeuse rigth now:\n\n";
	for (PoolUse * x : freeuses)
	{
		if (moment.first == x->getDate())
		{
			if (moment.second >= x->getTime() && moment.second<= x->getTime() + x->getDuration())
			{
				//TODO cout << x->getCustomer() << endl;  por desenvolver
				nocustomersflag = 0;
			}
		}
	}
	if (nocustomersflag)
	{
		cout << "There are no customers in freeuse rigth now";
	}


}
