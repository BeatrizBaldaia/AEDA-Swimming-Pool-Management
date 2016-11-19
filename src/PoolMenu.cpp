#include "PoolMenu.h"

#include <crtdefs.h>
#include <time.h>       /* time_t, struct tm, time, localtime */
#include <algorithm>    // std::unique, std::distance
#include <cctype>
#include <cwchar>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>

#include "Date.h"
#include "Lesson.h"
#include "Person.h"
#include "Pool.h"

//TODO ^^^ Não uses bibliotecas .h. Tenta usar as bibliotecas de cpp (por exemplo time.h é ctime)

/* FUNÇÕES UTEIS *///TODO \/\/\/ Passa o que trabalha sem Pool para o Date.
Date getCurrentDate() {  //retorna dia, mês e ano atual
	unsigned int day, month, year;
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	day = (unsigned int) timeinfo->tm_mday;
	month = (unsigned int) timeinfo->tm_mon + 1;
	year = (unsigned int) timeinfo->tm_year + 1900;

	Date date(day, month, year);
	return date;
}

Time getCurrentTime() {  //retorna tempo atual

	unsigned int hour, minute;
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	hour = (unsigned int) timeinfo->tm_hour;
	minute = (unsigned int) timeinfo->tm_min;

	Time time(hour, minute);
	return time;
}

DayOfWeek getCurrentDayOfWeek() {  //retorna atual dia da semana
	static const DayOfWeek wday_name[] = { MON, TUE, WED, THU, FRI, SAT, SUN };

	DayOfWeek dw;
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	dw = wday_name[timeinfo->tm_wday];
	return dw;
}

/* POOL MENU */

PoolMenu::PoolMenu(Pool & pool) :
		pool(pool) {

}

/* ADD CUSTOMER MENU */

AddCustomer::AddCustomer(Pool & pool) :
		pool(pool) {

}

MenuResult AddCustomer::handle() {
	bool again = true;
	string name;
	cout << "Insert the customer's name: ";
	getline(cin, name); //POSSIVELMENTE SUBSTITUIR POR UM getName que verifique o formato do nome.
	///////////////////////////////////////////
	///TIRAR ESPAÇOS A MAIS ENTRE OS NOMES////
	string::iterator it;
	it =
			unique(name.begin(), name.end(),
					[](char l, char r) {return isspace(l) && isspace(r) && l == r;}); ///remove os espaços a mais do nome, mas o tamanho da string nao se altera
	name.resize(distance(name.begin(), it)); ///ajustar o tamanho da string
	/////////////////////////////////////////
	while (again) {
		try {
			again = false;
			string Bdate;

			cout << "Insert the customer's birthdate (ex. 01/01/1999) : ";
			getline(cin, Bdate);

			Date date(Bdate);
			Customer * x = new Customer(name, date);
			pool.addCustomer(x);
		} catch (...) { ///apanha qualquer tipo de exceção
			cout << "Invalid Date. Please enter again.\n";
			again = true;
		}
	}

	return CONTINUE;

}

/* REMOVE CUSTOMER MENU */

RemoveCustomer::RemoveCustomer(Pool & pool) :
		pool(pool) {
}

MenuResult RemoveCustomer::handle() {
	unsigned int ID;
	cout << "Insert customer ID:";
	cin >> ID;
	Customer * c;
	try {
		c = pool.getCustomer(ID);
	} catch (NonExistentCustomerID &x) {
		cout << "\n\nCustomer doesn't belong to Pool or was already deleted";
		return CONTINUE;
	}
	for (GivenLesson * g : pool.getGivenLessons()) {
		g->removeCustomer(ID);
	}
	pool.removeCustomer(ID);
	cout << c->getName() << " removed!\n\n";
	pool.write();
	return CONTINUE;
}

/* CURRENT OCCUPATION MENU */

CurrentOccupation::CurrentOccupation(Pool & pool) :
		pool(pool) {

}

MenuResult CurrentOccupation::handle() {
	DayOfWeek day = getCurrentDayOfWeek();
	Time time = getCurrentTime();
	Date date = getCurrentDate();
	bool currentlesson = false; //condição para saber se está a ocorrer de momento uma aula na piscina
	try {
		Lesson lesson = pool.getNextLesson(day, time, currentlesson);

		if (currentlesson) {
			cout << lesson.getModality() << "ends in "
					<< lesson.getTime().getTimeGap(time) << "minutes" << endl;
			GivenLesson givenlesson(lesson, date);
			//vector<GivenLesson>::iterator it;
			//it = find(pool.getGivenLessons().begin(), pool.getGivenLessons().end(), givenlesson); //ALGORITMO DE PESQUISA!!!!
			//unsigned int numberCustomersLesson = it->getCustomers().size(); //número de pessoas que estão na aula atual
			unsigned int numberCustomersLesson = 0;
			for (GivenLesson * x : pool.getGivenLessons()) {
				if ((*x) == givenlesson) {
					numberCustomersLesson = x->getCustomers().size();
					break;
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// somar a numberCustomersLesson o número de clientes que também estão agora a usar a piscina, mas em modo livre//
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			numberCustomersLesson += pool.CustomersFreeUse(date, time);
			cout << "There are " << numberCustomersLesson
					<< " people in the pool." << endl;
			if (pool.getMaxCustomers() - numberCustomersLesson > 0) {
				cout << "Only "
						<< pool.getMaxCustomers() - numberCustomersLesson
						<< " more people can log in." << endl;
			} else {
				cout << "Nobody else can log in." << endl;
			}
		} else {
			cout << "Next lesson ( " << lesson.getModality() << " ) starts in "
					<< lesson.getTime().getTimeGap(time) << " minutes" << endl;
			unsigned int numberCustomersFree = pool.CustomersFreeUse(date,
					time); //número de clientes que estão a usar a piscina em modo livre
			if (numberCustomersFree == 0) {
				cout << "No one is in the pool at the moment." << endl
						<< pool.getMaxCustomers() << " people can log in."
						<< endl;
			} else {
				cout << "There are " << numberCustomersFree
						<< " people in the pool." << endl;
				if (pool.getMaxCustomers() - numberCustomersFree > 0) {
					cout << "Only "
							<< pool.getMaxCustomers() - numberCustomersFree
							<< " more people can log in." << endl;
				} else {
					cout << "Nobody else can log in." << endl;
				}
			}
		}
	} catch (NoMoreLessonsInDay &x) {
		cout << "There's no more lessons today." << endl;
		//dar o número de pessoas a usar a piscina em modo livre
		//fazer return/ acabar com a função
		unsigned int numberCustomersFree = pool.CustomersFreeUse(date, time); //número de clientes que estão a usar a piscina em modo livre
		if (numberCustomersFree == 0) {
			cout << "No one is in the pool at the moment." << endl
					<< pool.getMaxCustomers() << " people can log in." << endl;
		} else {
			cout << "There are " << numberCustomersFree
					<< " people in the pool." << endl;
			if (pool.getMaxCustomers() - numberCustomersFree > 0) {
				cout << "Only " << pool.getMaxCustomers() - numberCustomersFree
						<< " more people can log in." << endl;
			} else {
				cout << "Nobody else can log in." << endl;
			}
		}
	}

	return CONTINUE;

}

/* CUSTOMERS  ATTENDANCE MENU */

CustomerAttendanceAll::CustomerAttendanceAll(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerAttendanceAll::handle() {
	cout << "All Customers' number of attendances:" << endl << endl;
	for (Customer * x : pool.getCustomers()) {
		cout << "Customer n " << x->getID() << " - " << x->getName() << " : "
				<< x->getEntryNumber() << endl;
	}
	cout << "There are no customers." << endl;
	return CONTINUE;
}

CustomerAttendanceName::CustomerAttendanceName(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerAttendanceName::handle() {
	string name;
	bool again = true;
	int answer;
	string s;

	cout
			<< "See the number of attendances of a specific Customer.\n Enter the name: ";
	while (again) {
		getline(cin, name);
		///////////////////////////////////////////
		///TIRAR ESPAÇOS A MAIS ENTRE OS NOMES////
		string::iterator it;
		it =
				unique(name.begin(), name.end(),
						[](char l, char r) {return isspace(l) && isspace(r) && l == r;}); ///remove os espaços a mais do nome, mas o tamanho da string nao se altera
		name.resize(distance(name.begin(), it)); ///ajustar o tamanho da string
		/////////////////////////////////////////
		for (Customer * x : pool.getCustomers()) {
			if (x->getName() == name) {
				cout << "Customer n " << x->getID() << " - " << x->getName()
						<< " : " << x->getEntryNumber() << endl;
				return CONTINUE;
			}
		}
		cout << "There is no such customer." << endl;
		do {
			cout << "Do you want to try again?" << endl << endl
					<< "1- YES    2- NO" << endl;
			getline(cin, s);
			answer = stoi(s);
			cout << endl;
		} while (answer != 1 || answer != 2); ///inputs invalidos
		if (answer == 2) {
			again = false; ///ciclo acaba
		} else {
			cout << "Enter the name: "; ///again = true => repete
		}
	}
	return CONTINUE;

}

CustomerAttendanceID::CustomerAttendanceID(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerAttendanceID::handle() {
	string id_string;
	int id_int;
	bool again = true;
	int answer;
	string s;

	cout
			<< "See the number of attendances of a specific Customer.\n Enter the ID: ";
	while (again) {
		getline(cin, id_string);
		id_int = stoi(id_string);
		for (Customer * x : pool.getCustomers()) {
			if (x->getID() == id_int) {
				cout << "Customer n " << x->getID() << " - " << x->getName()
						<< " : " << x->getEntryNumber() << endl;
				return CONTINUE;
			}
		}
		cout << "There is no such customer." << endl;
		do {
			cout << "Do you want to try again?" << endl << endl
					<< "1- YES    2- NO" << endl;
			getline(cin, s);
			answer = stoi(s);
			cout << endl;
		} while (answer != 1 || answer != 2); ///inputs invalidos
		if (answer == 2) {
			again = false; ///ciclo acaba
		} else {
			cout << "Enter the ID: "; ///again = true => repete
		}
	}
	return CONTINUE;
}

/* Customer Make Bill MENU */

CustomerMakeCurrentBill::CustomerMakeCurrentBill(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerMakeCurrentBill::handle() {
	unsigned int customerID;
	unsigned int month = getCurrentDate().getMonth();
	unsigned int year = getCurrentDate().getYear();
	cout << "Insert Customer ID: ";
	cin >> customerID;
	vector<GivenLesson *> customerGivenLessons; //vetor que nos dá as given lessons do cliente nesse mes
	vector<PoolUse *> customerFreeSwimUses; //vetor que nos dá os usos da piscina (freeswimuses) do cliente nesse mes
	Customer * c;
	try {
		c = pool.getCustomer(customerID);
	} catch (NonExistentCustomerID &x) {
		printf("\nNon existing Customer");
		return CONTINUE;
	}
	for (PoolUse * p : c->getPoolUses()) {
		if (p->getDate().getMonth() == month && p->getDate().getYear() == year)
			customerFreeSwimUses.push_back(p);
	}
	for (GivenLesson * g : pool.getGivenLessons()) {
		if (g->getDate().getMonth() == month
				&& g->getDate().getYear() == year) {
			for (Customer * k : g->getCustomers()) {
				if (k->getID() == customerID)
					customerGivenLessons.push_back(g);
			}
		}
	}
	string billName = "Bill of ";
	billName += c->getName();
	billName += ".txt";
	ofstream bill;
	bill.open(billName.c_str());
	bill
			<< "*          **          **          Super Cool Pool          **          **          *\n"
			<< "-------------------------------------------------------------------------------------\n"
			<< "Customer: " << c->getName() << endl;
	bill << "ID: " << c->getID() << endl;
	bill
			<< "-------------------------------------------------------------------------------------\n"
			<< "                                   Bill of " << month << "/"
			<< year << endl << endl << endl;
	bill << "Lessons assisted: " << customerGivenLessons.size() << endl << endl;
	for (GivenLesson * g : customerGivenLessons) {
		bill << g->getLesson().getModality() << " (" << g->getDate()
				<< ").....................................€3.00" << endl;
	}
	bill << endl << endl << "Free swimming usage: "
			<< customerFreeSwimUses.size() << " times\n\n";
	for (PoolUse * p : customerFreeSwimUses) {
		if (p->getDuration() < 100)
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ")..........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
		else
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ").........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
	}
	bill << "\n\n                            Total:   €" << fixed
			<< setprecision(2)
			<< c->getMonthCost(month, year) + 3 * customerGivenLessons.size();
	return CONTINUE;
}

CustomerMakeBill::CustomerMakeBill(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerMakeBill::handle() {
	unsigned int customerID;
	string monthString;
	unsigned int month;
	unsigned int year;
	cout << "Insert Customer ID: ";
	cin >> customerID;
	cout << "\n\nInsert month and year (ex. 02/1995): ";
	cin >> monthString;
	if (monthString.size() != 7 || monthString[2] != '/')
		return CONTINUE;
	stringstream monthStream(monthString);
	monthStream >> month;
	monthStream.ignore();
	monthStream >> year;
	vector<GivenLesson *> customerGivenLessons; //vetor que nos dá as given lessons do cliente nesse mes
	vector<PoolUse *> customerFreeSwimUses; //vetor que nos dá os usos da piscina (freeswimuses) do cliente nesse mes
	Customer * c;
	try {
		c = pool.getCustomer(customerID);
	} catch (NonExistentCustomerID &x) {
		printf("\nNon existing Customer");
		return CONTINUE;
	}
	for (PoolUse * p : c->getPoolUses()) {
		if (p->getDate().getMonth() == month && p->getDate().getYear() == year)
			customerFreeSwimUses.push_back(p);
	}
	for (GivenLesson * g : pool.getGivenLessons()) {
		if (g->getDate().getMonth() == month
				&& g->getDate().getYear() == year) {
			for (Customer * k : g->getCustomers()) {
				if (k->getID() == customerID)
					customerGivenLessons.push_back(g);
			}
		}
	}
	string billName = "Bill of ";
	billName += c->getName();
	billName += ".txt";
	ofstream bill;
	bill.open(billName.c_str());
	bill
			<< "*          **          **          Super Cool Pool          **          **          *\n"
			<< "-------------------------------------------------------------------------------------\n"
			<< "Customer: " << c->getName() << endl;
	bill << "ID: " << c->getID() << endl;
	bill
			<< "-------------------------------------------------------------------------------------\n"
			<< "                                   Bill of " << monthString
			<< endl << endl << endl;
	bill << "Lessons assisted: " << customerGivenLessons.size() << endl << endl;
	for (GivenLesson * g : customerGivenLessons) {
		bill << g->getLesson().getModality() << " (" << g->getDate()
				<< ").....................................€3.00" << endl;
	}
	bill << endl << endl << "Free swimming usage: "
			<< customerFreeSwimUses.size() << " times\n\n";
	for (PoolUse * p : customerFreeSwimUses) {
		if (p->getDuration() < 100)
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ")..........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
		else
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ").........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
	}
	bill << "\n\n                            Total:   €" << fixed
			<< setprecision(2)
			<< c->getMonthCost(month, year) + 3 * customerGivenLessons.size();
	return CONTINUE;
}

/* ADD TEACHER MENU */

AddTeacher::AddTeacher(Pool& pool) :
		pool(pool) {
}

MenuResult AddTeacher::handle() {
	string teacherName;
	Date teacherBirthDate;
	cout << "\nInsert Teacher's name: ";
	getline(cin, teacherName);
	cout << "\nInsert Teacher's birthdate: ";
	cin >> teacherBirthDate;
	Teacher t(teacherName, teacherBirthDate);
	pool.addTeacher(&t);
	cout << endl << teacherName << " created!\n";
	pool.write();
	return CONTINUE;
}

/* REMOVE TEACHER MENU */

RemoveTeacher::RemoveTeacher(Pool& pool) :
	pool(pool){

}

MenuResult RemoveTeacher::handle() {
	unsigned int ID;
	cout << "\nInsert Teacher's ID: ";
	cin >> ID;
	int counter = 0;
	pool.removeTeacher(ID);
	for(Lesson & l : pool.getSchedule())
	{
		l.setTeacher(pool.getTeachers()[counter]);
		counter ++;
		if (counter == pool.getTeachers().size())
			counter = 0;
	}
	pool.write();
	return CONTINUE;
}

ViewTeachersLessons::ViewTeachersLessons(Pool& pool) :
		pool(pool) {

}

MenuResult ViewTeachersLessons::handle() {
}

ViewSchedule::ViewSchedule(Pool& pool) :
		pool(pool) {

}

MenuResult ViewSchedule::handle() {
	if (pool.getSchedule().size() == 0) {
		cout << "\nThere are no lessons scheduled.\n";
		return CONTINUE;
	}

	DayOfWeek d = pool.getSchedule()[0].getDayOfWeek();

	cout << "\n" << d << ":\n";

	for (const Lesson & i : pool.getSchedule()) {
		if (i.getDayOfWeek() != d) {
			d = i.getDayOfWeek();
			cout << "\n" << d << ":\n";
		}
		cout << i.getTime() << " - " << i.getModality() << endl
				<< i.getTeacher()->getName() << endl;

	}
	return CONTINUE;
}

AttendLesson::AttendLesson(Pool& pool) :
	pool(pool){

}

MenuResult AttendLesson::handle() {
	vector<Lesson &> lessons = pool.getLessons(getCurrentDate(),
			getCurrentTime());
	unsigned int choice;
	unsigned int customerID;
	cout << "\nInsert customer's ID: ";
	cin >> customerID;
	Customer * c = pool.getCustomer(customerID);
	if (lessons.size() == 0) {
		cout << "\nNo more lessons scheduled for today.\n";
		return CONTINUE;
	}
	cout << endl;
	for (int i = 0; i < lessons.size(); i++) {
		cout << i + 1 << " - " << lessons[i].getTime() << " ("
				<< lessons[i].getModality() << ")\n";
	}
	cout << "\n0 - Cancel";
	cout << "\nChoose one class to attend today: ";
	cin >> choice;
	if (choice == 0)
		return CONTINUE;
	int noGivenLessonFlag = 0;
	for (GivenLesson * g : pool.getGivenLessons()) {
		if (g->getDate() == getCurrentDate() && g->getLesson() == lessons[choice - 1]) {
			g->addCustomer(c);
			return CONTINUE;
		}
	}
	return CONTINUE;

}

AddLesson::AddLesson(Pool& pool) :
	pool(pool){
}

MenuResult AddLesson::handle() {
	DayOfWeek dayOfWeek;
	string weekDay;
	unsigned int modalityOpt;
	Modality modality;
	Time time;
	cout << "\nInsert day of week: ";
	cin >> weekDay;
	if(weekDay == "Monday")
		dayOfWeek = MON;
	else if (weekDay == "Tuesday")
		dayOfWeek = TUE;
	else if (weekDay == "Wednesday")
			dayOfWeek = WED;
	else if (weekDay == "Thursday")
			dayOfWeek = THU;
	else if (weekDay == "Friday")
			dayOfWeek = FRI;
	else if (weekDay == "Saturday")
			dayOfWeek = SAT;
	else if (weekDay == "Sunday")
			dayOfWeek = SUN;
	cout << "\nInsert lesson's time: ";
	cin >> time;
	cout << "\n\n0 - HydroGym\n1 - Zumba\n2 - AquaticPolo\n3 - ArtisticSwimming\n4 - CompetitiveSwimming\n5 - Learning\n";
	cout << "\nChoose lesson's modality: ";
	cin >> modalityOpt;
	modality = modalityOpt;
	LessonTime lessonTime;
	lessonTime.first = dayOfWeek;
	lessonTime.second = time;
	Lesson l(lessonTime, modality);
	pool.addLesson(l); //criar excepção de já existir uma aula a esta hora
	return CONTINUE;
}

RemoveLesson::RemoveLesson(Pool& pool) :
	pool(pool){

}

MenuResult RemoveLesson::handle() {
	unsigned int choice;
	cout << endl;
	int indice = 0;
	for (Lesson & i : pool.getSchedule())
	{
		indice++;
		cout << indice << " - " << i.getModality() << endl << i.getDayOfWeek() << " - " << i.getTime() << endl;
	}
	cout << "\n0 - Cancel\n";
	cout << "Choose lesson to be deleted: ";
	cin >> choice;
	if (choice == 0)
	{
		return CONTINUE;
	}
	pool.getSchedule().erase(pool.getSchedule().begin() + choice);
	return CONTINUE;
}
