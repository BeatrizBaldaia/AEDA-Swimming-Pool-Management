#include "Pool.h"
#include <algorithm>
#include <fstream>
#include <sstream>

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
	lesson.setTeacher(teachers[0]); //estamos a retornar o professor com menos aulas dadas porque o vetor teachers j� est� ordenado
	schedule.push_back(lesson);
	teachers[0]->setLesson();

	sort(teachers.begin(),teachers.end(),[](Teacher * a, Teacher * b){return a->getNumberLessons() < b->getNumberLessons();});
}

unsigned int Pool::CustomersInLesson(GivenLesson lesson){
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


vector<Customer *> Pool::getAllCustomer() {
	vector<Customer *> result;
	for(Customer * x : customers){
		result.push_back(x);
	}
	sort(result.begin(),result.end(),[](Customer * a, Customer * b){return a->getEntryNumber() < b->getEntryNumber();});

	return result;
}

Customer * Pool::getCustomer(string name) {
	for(Customer * x : customers){
		if(x->getName() == name){
			return x;
		}
	}

	throw NonExistentCustomerName(name);

}

Customer * Pool::getCustomer(unsigned int ID) {
	for(Customer * x : customers){
		if(x->getID() == ID){
			return x;
		}
	}

	throw NonExistentCustomerID(ID);
}

/* EXCE��ES */

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

void Pool::addTeacher(Teacher* t) {
	teachers.push_back(t);
}

void Pool::attendLesson(Lesson lesson, Customer* customer, Date date) {
	if(lesson.getDayOfWeek() != date.getDayOfWeek()) {
		throw string("wtf dude. that ain't the same day, dumbass"); //TODO
	}
	GivenLesson * givenLesson;
	try {
		givenLesson = getGivenLesson(lesson, date);
	} catch (string x) {
		if(x == "given lesson not found") {
			givenLesson = new GivenLesson(lesson, date);
			givenLessons.push_back(givenLesson);
		}
	}
	givenLesson->addCustomer(customer);
	customer->attendLesson(givenLesson, date, lesson.getTime());
}

GivenLesson* Pool::getGivenLesson(Lesson lesson, Date date) {
	if(lesson.getDayOfWeek() != date.getDayOfWeek()) {
		throw string("wtf dude. that ain't the same day, dumbass"); //TODO
	}
	for(GivenLesson * x : givenLessons) {
		if(x->getLesson() == lesson && x->getDate() == date) {
			return x;
		}
	}
	throw string("given lesson not found");
}

void Pool::addFreeSwim(Customer* customer, Date date, Time time, unsigned int duration) {
	PoolUse * poolUse = new FreeSwimUse(date,time,duration);
	customer->addUse(poolUse);
	freeUses.push_back(poolUse);
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

void Pool::loadPoolInfo() {
	ifstream poolInfoFile(fileNames[0]);
	string name;
	getline(poolInfoFile, name, ';');
	setName(name);
	unsigned int maxCustomers;
	poolInfoFile >> maxCustomers;
	setMaxCustomers(maxCustomers);
}

void Pool::loadCustomers() {
	ifstream customersFile(fileNames[1]);
	unsigned int n;
	customersFile >> n;
	for(size_t i = 0; i < n; i++) {
		unsigned int ID;
		customersFile >> ID;
		customersFile.ignore();
		string name;
		getline(customersFile, name, ';');
		Date birthDate;
		customersFile >> birthDate;
		customersFile.ignore();
		Customer * c = new Customer(name, birthDate, ID);
		unsigned int m;
		customersFile >> m;
		for(size_t j = 0; j < m; j++){
			Date useDate;
			customersFile >> useDate;
			customersFile.ignore();
			Time useTime;
			customersFile >> useTime;
			customersFile.ignore();
			unsigned int duration;
			customersFile >> duration;
			PoolUse * p = new FreeSwimUse(useDate, useTime, duration);
			c->addUse(p);
			freeUses.push_back(p);
		}
		customers.push_back(c);
	}
}

void Pool::loadTeachers() {
	ifstream teachersFile(fileNames[2]);
	unsigned int n;
	teachersFile >> n;
	for(size_t i = 0; i < n; i++) {
		unsigned int ID;
		teachersFile >> ID;
		teachersFile.ignore();
		string name;
		getline(teachersFile, name, ';');
		Date birthDate;
		teachersFile >> birthDate;
		teachersFile.ignore();
		Teacher * t = new Teacher(name, birthDate, ID);
		teachers.push_back(t);
	}
}

void Pool::loadSchedule() {
	ifstream scheduleFile(fileNames[3]);
	unsigned int n;
	scheduleFile >> n;
	for(size_t i = 0; i < n; i++) {
		unsigned int teacherID;
		scheduleFile >> teacherID;
		Teacher * t = getTeacher(teacherID);
		scheduleFile.ignore();
		unsigned int modValue;
		scheduleFile >> modValue;
		Modality mod = static_cast<Modality>(modValue);
		scheduleFile.ignore();
		unsigned int dowValue;
		scheduleFile >> dowValue;
		DayOfWeek dow = static_cast<DayOfWeek>(dowValue);
		scheduleFile.ignore();
		Time time;
		scheduleFile >> time;
		Lesson lesson(LessonTime(dow, time), mod);
		lesson.setTeacher(t);
		schedule.push_back(lesson);
	}
}

void Pool::loadGivenLessons() {
	ifstream givenLessonsFile(fileNames[4]);
	unsigned int n;
	givenLessonsFile >> n;
	for(size_t i = 0; i < n; i++) {
		unsigned int ID;
		givenLessonsFile >> ID;
		givenLessonsFile.ignore();
		unsigned int teacherID;
		givenLessonsFile >> teacherID;
		Teacher * t = getTeacher(teacherID);
		givenLessonsFile.ignore();
		unsigned int modValue;
		givenLessonsFile >> modValue;
		Modality mod = static_cast<Modality>(modValue);
		givenLessonsFile.ignore();
		unsigned int dowValue;
		givenLessonsFile >> dowValue;
		DayOfWeek dow = static_cast<DayOfWeek>(dowValue);
		givenLessonsFile.ignore();
		Time time;
		givenLessonsFile >> time;
		Lesson lesson(LessonTime(dow, time), mod);
		lesson.setTeacher(t);
		givenLessonsFile.ignore();
		Date date;
		givenLessonsFile >> date;
		givenLessonsFile.ignore();
		GivenLesson * givenLesson = new GivenLesson(lesson,date,ID);
		givenLessons.push_back(givenLesson);
		t->setLesson();
		string customersString;
		getline(givenLessonsFile, customersString);
		stringstream customersSS(customersString);
		while(customersSS) {
			unsigned int customerID;
			customersSS >> customerID;
			Customer * customer = getCustomer(customerID);
			givenLesson->addCustomer(customer);
			PoolUse * poolUse = new LessonUse(date, time, givenLesson);
			customer->addUse(poolUse);
		}
	}
}

void Pool::addCustomer(Customer* c) {
	customers.push_back(c);
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

Lesson Pool::getNextLesson(DayOfWeek day, Time time, bool & currentlesson) const{ //Ia usar esta fun��o para o menu PoolOccupation para obter a aula que estava a ocorrer ou a pr�xima aula que ia come�ar
	unsigned int gap= 100000;
	bool excecao = true;
	Lesson next;
	for(Lesson x : schedule){
		if(x.getDayOfWeek() == day){
			if(x.getTime() < time){
				if(x.getTime().getTimeGap(time) < 60){ //aula que inda est� a decorrer
					currentlesson = true;
					return x;
				}
			}
			else{
				if(x.getTime().getTimeGap(time) < gap){ //nao percebo porque que aqui d� erro visto que o overload do operador - da classe Time retorna um unsigned int
					gap = x.getTime().getTimeGap(time);
					next = x;
					excecao = false;
				}
			}
		}
	}
	if (excecao){ //neste dia n�o h� mais aulas
		throw NoMoreLesson();
	}

	return next;
}

unsigned int Pool::CustomersFreeUse(Date date, Time time){
	unsigned int result = 0;
	for(PoolUse * x : freeUses){
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
	freeUses.insert(freeUses.begin(), freeUse);
}

Teacher* Pool::getTeacher(unsigned int ID) {
	for(Teacher * x : teachers) {
		if(x->getID() == ID) {
			return x;
		}
	}
	return NULL;
}

void Pool::load() {
	loadPoolInfo();
	loadCustomers();
	loadTeachers();
	loadSchedule();
	loadGivenLessons();
}
