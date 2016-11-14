#include "PoolMenu.h"
#include "Person.h"
#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, localtime */
//TODO ^^^ Não uses bibliotecas .h. Tenta usar as bibliotecas de cpp (por exemplo time.h é ctime)

/* FUNÇÕES UTEIS */ //TODO \/\/\/ Passa o que trabalha sem Pool para o Date.

Date getCurrentDate(){  //retorna dia, mês e ano atual
	unsigned int day, month, year;
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	day = (unsigned int)timeinfo->tm_mday;
	month = (unsigned int)timeinfo->tm_mon + 1;
	year = (unsigned int)timeinfo->tm_year + 1900;

	Date date(day, month, year);
	return date;
}

Time getCurrentTime(){  //retorna tempo atual

	unsigned int hour, minute;
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	hour = (unsigned int)timeinfo->tm_hour;
	minute = (unsigned int)timeinfo->tm_min;

	Time time(hour, minute);
	return time;
}

DayOfWeek getCurrentDayOfWeek(){  //retorna atual dia da semana
	static const DayOfWeek wday_name[] = {
			MON, TUE, WED, THU, FRI, SAT, SUN
	};

	DayOfWeek dw;
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	dw = wday_name[timeinfo->tm_wday];
	return dw;
}

/* POOL MENU */

PoolMenu::PoolMenu(Pool & pool) : pool(pool) {

}

/* ADD CUSTOMER MENU */

AddCustomer::AddCustomer(Pool & pool) : pool(pool) {

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

CurrentOccupation::CurrentOccupation(Pool & pool) : pool(pool) {

}

MenuResult CurrentOccupation::handle(){
	DayOfWeek day = getCurrentDayOfWeek();
	Time time = getCurrentTime();
	Date date = getCurrentDate();
	bool currentlesson = false; //condição para saber se está a ocorrer de momento uma aula na piscina
	try{
		Lesson lesson = pool.getNextLesson(day, time, currentlesson);


		if(currentlesson){
			cout << lesson.getModality() << "ends in " << lesson.getTime().getTimeGap(time) << "minutes" << endl;
			GivenLesson givenlesson(lesson, date);
			//vector<GivenLesson>::iterator it;
			//it = find(pool.getGivenLessons().begin(), pool.getGivenLessons().end(), givenlesson); //ALGORITMO DE PESQUISA!!!!
			//unsigned int numberCustomersLesson = it->getCustomers().size(); //número de pessoas que estão na aula atual
			unsigned int numberCustomersLesson = 0;
			for( GivenLesson * x : pool.getGivenLessons()){
				if((*x) == givenlesson){
					numberCustomersLesson = x->getCustomers().size();
					break;
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// somar a numberCustomersLesson o número de clientes que também estão agora a usar a piscina, mas em modo livre//
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			numberCustomersLesson += pool.CostumersFreeUse(date, time);
			cout << "There are " << numberCustomersLesson << " people in the pool." << endl;
			if(pool.getMaxCustomers()-numberCustomersLesson > 0){
				cout << "Only " << pool.getMaxCustomers()-numberCustomersLesson << " more people can log in." << endl;
			}
			else{
				cout << "Nobody else can log in." << endl;
			}
		}
		else{
			cout << "Next lesson ( " << lesson.getModality() << " ) starts in " << lesson.getTime().getTimeGap(time) << " minutes" << endl;
			unsigned int numberCustomersFree = pool.CostumersFreeUse(date, time); //número de clientes que estão a usar a piscina em modo livre
			if(numberCustomersFree == 0){
				cout << "No one is in the pool at the moment." << endl
						<< pool.getMaxCustomers() << " people can log in." << endl;
			}
			else{
				cout << "There are " << numberCustomersFree << " people in the pool." << endl;
				if(pool.getMaxCustomers()-numberCustomersFree > 0){
					cout << "Only " << pool.getMaxCustomers()-numberCustomersFree << " more people can log in." << endl;
				}
				else{
					cout << "Nobody else can log in." << endl;
				}
			}
		}
	}catch(NoMoreLesson x){
		cout << "There's no more lessons today." << endl;
		//dar o número de pessoas a usar a piscina em modo livre
		//fazer return/ acabar com a função
		unsigned int numberCustomersFree = pool.CostumersFreeUse(date, time); //número de clientes que estão a usar a piscina em modo livre
		if(numberCustomersFree == 0){
			cout << "No one is in the pool at the moment." << endl
					<< pool.getMaxCustomers() << " people can log in." << endl;
		}
		else{
			cout << "There are " << numberCustomersFree << " people in the pool." << endl;
			if(pool.getMaxCustomers()-numberCustomersFree > 0){
				cout << "Only " << pool.getMaxCustomers()-numberCustomersFree << " more people can log in." << endl;
			}
			else{
				cout << "Nobody else can log in." << endl;
			}
		}
	}

	return EXIT;

}
