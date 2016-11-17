#include "PoolMenu.h"

#include <crtdefs.h>
#include <time.h>       /* time_t, struct tm, time, localtime */
#include <algorithm>    // std::unique, std::distance
#include <cctype>
#include <cwchar>
#include <iostream>
#include <fstream>
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
	string name;
	cout << "Insert the customer's name: ";
	getline(cin, name); //POSSIVELMENTE SUBSTITUIR POR UM getName que verifique o formato do nome.
	cout << name;
	cout << "Insert the customer's birthdate: ";

	return EXIT;

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
	} catch (NoMoreLessonsInDay x) {
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

	return EXIT;

}

/* CUSTOMERS  ATTENDANCE MENU */

CustomerAttendanceAll::CustomerAttendanceAll(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerAttendanceAll::handle() {
	cout << "All Customers' number of attendances:" << endl << endl;
	for (Customer * x : pool.getAllCustomer()) {
		cout << "Customer n " << x->getID() << " - " << x->getName() << " : "
				<< x->getEntryNumber() << endl;
		return EXIT;
	}
	cout << "There are no customers." << endl;
	return EXIT;
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
		for (Customer * x : pool.getAllCustomer()) {
			if (x->getName() == name) {
				cout << "Customer n " << x->getID() << " - " << x->getName()
						<< " : " << x->getEntryNumber() << endl;
				return EXIT;
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
	return EXIT;

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
		for (Customer * x : pool.getAllCustomer()) {
			if (x->getID() == id_int) {
				cout << "Customer n " << x->getID() << " - " << x->getName()
						<< " : " << x->getEntryNumber() << endl;
				return EXIT;
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
	return EXIT;
}

CustomerMakeBill::CustomerMakeBill(Pool & pool) :
		pool(pool){

}

MenuResult CustomerMakeBill::handle() {
	unsigned int customerID;
	string monthStream;
	unsigned int month;
	unsigned int year;
	cout << "Insert Customer ID: ";
	cin >> customerID;
	cout << "\n\nInsert month and year (ex. 02/1995): ";
	cin >> monthStream;
	month = 10*monthStream[0] + monthStream[1]; //TODO usar fstream ou string stream se quiserem, se não, apagar o comentário
	year = 1000*monthStream[3] + 100*monthStream[4] + 10*monthStream[5] + monthStream[6];
	vector <GivenLesson *> customerGivenLessons; //vetor que nos dá as given lessons do cliente nesse mes
	vector <PoolUse *> customerFreeSwimUses; //vetor que nos dá os usos da piscina (freeswimuses) do cliente nesse mes
	Customer * c;
	try {
		c = pool.getCustomer(customerID);
	} catch (NonExistentCustomerID(ID)) {
		printf("\nNon existing Customer");
		return EXIT;
	}
	for(PoolUse * p : c->getPoolUses())
	{
		if(p->getDate().getMonth() == month && p->getDate().getYear() == year)
			customerFreeSwimUses.push_back(p);
	}
	for(GivenLesson * g : pool.getGivenLessons())
	{
		if(g->getDate().getMonth() == month && g->getDate().getYear() == year)
		{
			for (Customer * k : g->getCustomers())
			{
				if(k->getID() == customerID)
					customerGivenLessons.push_back(g);
			}
		}
	}
	string billName = "Bill of " + c->getName() + " - " + monthStream + ".txt"; //TODO corrigir para poder ter vários recibos
	ofstream bill;
	bill.open("test.txt");
	bill << "*          **          **          Super Cool Pool          **          **          *\n" <<
			"-------------------------------------------------------------------------------------\n" <<
			"Customer: " << c->getName() << endl;
	bill << "ID: " << c->getID() << endl;
	bill << "-------------------------------------------------------------------------------------\n" <<
			"                                   Bill of " << monthStream << endl << endl << endl;
	bill << "Lessons assisted: " << customerGivenLessons.size() << endl << endl;
	for (GivenLesson * g : customerGivenLessons)
	{
		bill << "  -> " << g->getDate() << " -- " << g->getLesson().getModality() << " -- " << g->getLesson().getTime() << endl;
	}
	bill << endl << "Pool usage (lessons not included): Pool used " << customerFreeSwimUses.size() << " times\n\n";
	for (PoolUse * p : customerFreeSwimUses)
	{
		bill << "  -> " << p->getDate() << " -- Started at: " << p->getTime() << " and had the duration of " << p->getDuration() << " minutes\n";
	}
	bill << "\n\nTotal cost to pay this month is: " << (c->getMonthCost(month,year) + 3*customerGivenLessons.size());
	return EXIT;
}
