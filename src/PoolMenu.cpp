#include "PoolMenu.h"
#include "Person.h"
#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, localtime */


/* FUNÇÕES UTEIS */

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



PoolMenu::PoolMenu(Pool & pool) : pool(pool) {

}

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
