#include "Pool.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>
#include <utility>

vector<Lesson> Pool::getLessons(unsigned int ID) {
	vector<Lesson> result;
	for (const Lesson & x : schedule) {
		if (x.getTeacher()->getID() == ID) {
			result.push_back(x);
		}
	}
	return result;
}

void Pool::setName(string name) {
	this->name = name;
}

void Pool::addLesson(Lesson lesson) {
	schedule.push_back(lesson);
	distributeLessons();
	sort(schedule.begin(), schedule.end());
}

unsigned int Pool::CustomersInLesson(GivenLesson lesson) {
	return lesson.getCustomers().size();
}

Lesson Pool::getLesson(DayOfWeek day, Time time) const {
	for (const Lesson & x : schedule) {
		if (x.getDayOfWeek() == day && x.getTime() == time) {
			return x;
		}
	}
	throw InvalidLesson(day, time);

}

vector<Customer *> Pool::getCustomers() {
	vector<Customer *> result = customers;
	sort(result.begin(), result.end(),
			[](Customer * a, Customer * b) {return a->getEntryNumber() < b->getEntryNumber();});

	return result;
}

Customer * Pool::getCustomer(string name) {
	for (Customer * x : customers) {
		if (x->getName() == name) {
			return x;
		}
	}

	throw NonExistentCustomerName(name);

}

Customer * Pool::getCustomer(unsigned int ID) {
	for (Customer * x : customers) {
		if (x->getID() == ID) {
			return x;
		}
	}

	throw NonExistentCustomerID(ID);
}

/* EXCEÇÕES */

NoMoreLessonsInDay::NoMoreLessonsInDay() {

}

InvalidLesson::InvalidLesson(DayOfWeek day, Time &t) {
	this->day = day;
	time = t;
}

NonExistentCustomerName::NonExistentCustomerName(string name) {
	this->name = name;
}

NonExistentCustomerID::NonExistentCustomerID(unsigned int ID) {
	this->ID = ID;
}

NonExistentTeacherID::NonExistentTeacherID(unsigned int ID) {
	this->ID = ID;
}

///////////////////////////////////////////////////////////////////////////

unsigned int Pool::getMaxCustomers() const {
	return maxCustomers;
}



void Pool::setMaxCustomers(unsigned int n) {
	maxCustomers = n;
}

string Pool::getName() const {
	return name;
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
	for (Customer * i : customers) {
		customersFile << i->getID() << ";";
		customersFile << i->getName() << ";";
		customersFile << i->getBirthDate() << ";";
		vector<PoolUse *> FreeSwimUses;
		for (PoolUse * j : i->getPoolUses()) {
			if (j->getLesson() == NULL) {
				FreeSwimUses.push_back(j);
			}
		}
		customersFile << FreeSwimUses.size() << endl;
		for (PoolUse * j : FreeSwimUses) {
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
	for (Teacher * i : teachers) {
		teachersFile << i->getID() << ";";
		teachersFile << i->getName() << ";";
		teachersFile << i->getBirthDate() << endl;
	}
	teachersFile.close();
}

void Pool::writeSchedule() {
	ofstream scheduleFile(fileNames[3]);
	scheduleFile << schedule.size() << endl;
	for (const Lesson & i : schedule) {
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
	distributeLessons();
}

void Pool::attendLesson(Lesson lesson, Customer* customer, Date date) {
	if (lesson.getDayOfWeek() != date.getDayOfWeek()) {
		throw NotSameDayAsDate();
	}
	GivenLesson * givenLesson;
	try {
		givenLesson = getGivenLesson(lesson, date);
	} catch (NonExistentGivenLesson &x) {
			givenLesson = new GivenLesson(lesson, date);
			givenLessons.push_back(givenLesson);
	}
	for (Customer * i : givenLesson->getCustomers()) {
		if (i == customer) {
			throw CustomerAlreadyAttendedLesson();
		}
	}
	givenLesson->addCustomer(customer);
	customer->attendLesson(givenLesson, date, lesson.getTime());
}

GivenLesson* Pool::getGivenLesson(Lesson lesson, Date date) {
	if (lesson.getDayOfWeek() != date.getDayOfWeek()) {
		throw NotSameDayAsDate();
	}
	for (GivenLesson * x : givenLessons) {
		if (x->getLesson() == lesson && x->getDate() == date) {
			return x;
		}
	}
	throw NonExistentGivenLesson(lesson, date);
}

void Pool::addFreeSwim(Customer* customer, Date date, Time time,
		unsigned int duration) {
	PoolUse * poolUse = new FreeSwimUse(date, time, duration);
	customer->addUse(poolUse);
	freeUses.push_back(poolUse);
}

void Pool::removeCustomer(unsigned int ID) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i]->getID() == ID) {
			customers.erase(customers.begin() + i);
			break;
		}
	}
}

void Pool::removeTeacher(unsigned int ID) {
	for(int i = 0; i < teachers.size(); i++) {
		if(teachers[i]->getID() == ID) {
			teachers.erase(teachers.begin() + i);
			break;
		}
	}
	distributeLessons();
}

vector<GivenLesson*> Pool::getGivenLessons(unsigned int ID) {
	vector<GivenLesson*> result;
	for (GivenLesson* i : givenLessons) {
		if (i->getLesson().getTeacher()->getID() == ID) {
			result.push_back(i);
		}
	}

	return result;
}

vector<Lesson> Pool::getLessons(Date date, Time time) {
	vector<Lesson> result;
	for (const Lesson i : schedule) {
		if (i.getDayOfWeek() == date.getDayOfWeek() && (i.getTime() >= time)) {
			result.push_back(i);
		}
	}
	return result;
}

vector<Lesson> Pool::getSchedule() const {
	return schedule;
}

vector<Teacher*> Pool::getTeachers() const {
	return teachers;
}

void Pool::distributeLessons() {
	size_t counter = 0;
	for (Lesson & l : schedule) {
		l.setTeacher(teachers[counter]);
		counter++;
		if (counter == teachers.size())
			counter = 0;
	}
}

void Pool::writeGivenLessons() {
	ofstream givenLessonsFile(fileNames[4]); //nº GivenLessons \n ID de GivenLessons;ID do professor;modalidade;dia da semana da GivenLesson; hora da aula;data da aula;ID dos clientes separados por um espaço
	givenLessonsFile << givenLessons.size() << endl;
	for (GivenLesson * i : givenLessons) {
		givenLessonsFile << i->getID() << ";";
		givenLessonsFile << i->getLesson().getTeacher()->getID() << ";";
		int mod = i->getLesson().getModality();
		givenLessonsFile << mod << ";";
		int day = i->getLesson().getDayOfWeek();
		givenLessonsFile << day << ";";
		givenLessonsFile << i->getLesson().getTime() << ";";
		givenLessonsFile << i->getDate() << ";";
		for (size_t j = 0; j < i->getCustomers().size(); j++) {
			if (j == i->getCustomers().size() - 1) {
				givenLessonsFile << i->getCustomers()[j]->getID();
			} else {
				givenLessonsFile << i->getCustomers()[j]->getID() << " ";
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
	for (size_t i = 0; i < n; i++) {
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
		for (size_t j = 0; j < m; j++) {
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
	for (size_t i = 0; i < n; i++) {
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
	for (size_t i = 0; i < n; i++) {
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
	distributeLessons();
	sort(schedule.begin(),schedule.end());
}

void Pool::loadGivenLessons() {
	ifstream givenLessonsFile(fileNames[4]);
	unsigned int n;
	givenLessonsFile >> n;
	for (size_t i = 0; i < n; i++) {
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
		GivenLesson * givenLesson = new GivenLesson(lesson, date, ID);
		givenLessons.push_back(givenLesson);
		t->setLesson();
		string customersString;
		getline(givenLessonsFile, customersString);
		stringstream customersSS(customersString);
		while (!customersSS.eof()) {
//			cout << customersSS.str() << endl;
			unsigned int customerID;
			customersSS >> customerID;
//			cout << customerID << endl;
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

vector<GivenLesson *> Pool::getGivenLessons() {
	return givenLessons;
}

Lesson Pool::getNextLesson(DayOfWeek day, Time time,
		bool & currentlesson) const { //Ia usar esta função para o menu PoolOccupation para obter a aula que estava a ocorrer ou a próxima aula que ia começar
	vector<Lesson> lessonsInDay;
	for (const Lesson & i : schedule) {
		if (day == i.getDayOfWeek()) {
			if (i.getTime() < time) {
				Time duration(1, 0);
				Time sum = i.getTime() + duration;
				if(sum > time) {
					currentlesson = true;
					return i;
				}

			} else {
				currentlesson = false;
				return i;
			}
		}
	}
	throw NoMoreLessonsInDay();
}

unsigned int Pool::CustomersFreeUse(Date date, Time time) {
	unsigned int result = 0;
	for (PoolUse * x : freeUses) {
		if (x->getDate() == date) {
			if (x->getTime() < time) {
				if (x->getTime().getTimeGap(time) < x->getDuration()) { //pessoa ainda a usar a piscina em modo livre
					result++;
				}
			}
		}
	}

	return result;
}

void Pool::addFreeUse(PoolUse * freeUse) {
	freeUses.push_back(freeUse);
}

Teacher* Pool::getTeacher(unsigned int ID) {
	for (Teacher * x : teachers) {
		if (x->getID() == ID) {
			return x;
		}
	}
	throw NonExistentTeacherID(ID);
}

void Pool::load() {
	loadPoolInfo();
	loadCustomers();
	loadTeachers();
	loadSchedule();
	loadGivenLessons();
}

NotSameDayAsDate::NotSameDayAsDate() {
}

NonExistentGivenLesson::NonExistentGivenLesson(Lesson lesson, Date date) {
	this->lesson = lesson;
	this->date = date;
}

void Pool::removeLesson(unsigned int position) {
	schedule.erase(schedule.begin() + position);
}
