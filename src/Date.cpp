#include "Date.h"

#include <crtdefs.h>
#include <cmath>
#include <ctime>
#include <cwchar>
#include <sstream>

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	if (month >= 1 && month <= 12) {
		if (day >= 1 && day <= daysInMonth(month, year)) {
			this->day = day;
			this->month = month;
			this->year = year;
			return;
		}
		throw InvalidDay();
	}

	throw InvalidMonth();
}

Date::Date() {

}

Date::Date(string & input) {
	/*string aux;
	 unsigned int d, m, y;
	 size_t found_not = input.find_first_not_of("0123456789"); ///procurar o 1º elemento que nao é um número que separa o dia do mÊs
	 aux = input.substr(0, found_not);
	 d = stoi(aux);
	 size_t found = input.find_first_of("0123456789", found_not + 1); ///procura numero; primeiro digito para o mês
	 input = input.substr(found, input.size() - found); ///para ficar so com o resto da string; elimina a parte do dia
	 found_not = input.find_first_not_of("0123456789"); ///procura elemento que nao é digito e separa o mês do ano
	 aux = input.substr(0, found_not);
	 m = stoi(aux);
	 found = input.find_first_of("0123456789", found_not + 1); ///posição do primeiro digito para o ano
	 input = input.substr(found, input.size() - found);
	 found_not = input.find_first_not_of("0123456789"); ///posição até a onde vamos extrair o velor para o ano
	 aux = input.substr(0, found_not);
	 y = stoi(aux);

	 Date(d, m, y);
	 */
	stringstream date;
	date.str(input);
	date >> day;
	date.ignore();
	date >> month;
	date.ignore();
	date >> year;
}

unsigned int Date::getDay() const {
	return day;
}

unsigned int Date::getMonth() const {
	return month;
}

unsigned int Date::getYear() const {
	return year;
}

void Date::setDay(const unsigned int &day) {
	this->day = day;
}

void Date::setMonth(const unsigned int &month) {
	this->month = month;
}

void Date::setYear(const unsigned int &year) {
	this->year = year;
}

bool isLeapYear(const unsigned int &year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return true;
	} else {
		return false;
	}
}

unsigned int daysInMonth(const unsigned int &month, const unsigned int &year) {
	if ((month % 2 == 1 && month <= 7) || (month % 2 == 0 && month >= 8)) {
		return 31;
	} else if (month == 2) {
		if (isLeapYear(year)) {
			return 29;
		} else {
			return 28;
		}
	} else {
		return 30;
	}
}

bool Date::valid() const {
	if (month >= 1 && month <= 12) {
		if (day >= 1 && day <= daysInMonth(month, year)) {
			return true;
		}
	}
	return false;
}

bool Date::operator <=(const Date &date) const {
	if (year < date.getYear()) {
		return true;
	} else if (year == date.getYear()) {
		if (month < date.getMonth()) {
			return true;
		} else if (month == date.getMonth()) {
			if (day <= date.getDay()) {
				return true;
			}
		}
	}
	return false;
}

bool Date::operator >=(const Date &date) const {
	if (year > date.getYear()) {
		return true;
	} else if (year == date.getYear()) {
		if (month > date.getMonth()) {
			return true;
		} else if (month == date.getMonth()) {
			if (day >= date.getDay()) {
				return true;
			}
		}
	}
	return false;
}

bool Date::operator <(const Date &date) const {
	if (year < date.getYear()) {
		return true;
	} else if (year == date.getYear()) {
		if (month < date.getMonth()) {
			return true;
		} else if (month == date.getMonth()) {
			if (day < date.getDay()) {
				return true;
			}
		}
	}
	return false;
}

bool Date::operator >(const Date &date) const {
	if (year > date.getYear()) {
		return true;
	} else if (year == date.getYear()) {
		if (month > date.getMonth()) {
			return true;
		} else if (month == date.getMonth()) {
			if (day > date.getDay()) {
				return true;
			}
		}
	}
	return false;
}

bool Date::operator==(const Date & date) const {
	return this->day == date.day && this->month == date.month
			&& this->year == date.year;
}

bool Date::between(const Date &min, const Date &max) {
	if (*this >= min && *this <= max) {
		return true;
	} else {
		return false;
	}
}

const Date & Date::operator=(const Date & d) {
	day = d.getDay();
	month = d.getMonth();
	year = d.getYear();
	return *this;
}
ostream & operator <<(ostream & out, const Date & d) {
	if (d.getDay() < 10) {
		out << '0';
	}
	out << d.getDay();

	out << '/';

	if (d.getMonth() < 10) {
		out << '0';
	}
	out << d.getMonth();

	out << '/';

	out << d.getYear();

	return out;
}

istream & operator >>(istream & in, Date & date) {
	int d, m, y;
	in >> d;
	in.ignore();
	in >> m;
	in.ignore();
	in >> y;
	date.setDay(d);
	date.setMonth(m);
	date.setYear(y);

	return in;
}

DayOfWeek Date::getDayOfWeek() const {
	int y = year;
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= month < 3;
	int result = (y + y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7;
	switch (result) {
	case 0:
		return SUN;
	case 1:
		return MON;
	case 2:
		return TUE;
	case 3:
		return WED;
	case 4:
		return THU;
	case 5:
		return FRI;
	case 6:
		return SAT;
	}
}

ostream & operator <<(ostream & out, const DayOfWeek & d) {
	switch (d) {
	case MON:
		out << "Monday";
		break;
	case TUE:
		out << "Tuesday";
		break;
	case WED:
		out << "Wednesday";
		break;
	case THU:
		out << "Thursday";
		break;
	case FRI:
		out << "Friday";
		break;
	case SAT:
		out << "Saturday";
		break;
	case SUN:
		out << "Sunday";
		break;

	}

	return out;
}

Time::Time(unsigned int h, unsigned int m) {
	if (h >= 24 || m >= 60) {
		throw InvalidTimeRange();
	}

	hour = h;
	minute = m;

}

Time::Time() {
}

unsigned int Time::getMinute() const {
	return minute;
}

unsigned int Time::getHour() const {
	return hour;
}

ostream& operator <<(ostream& out, const Time& t) {
	if (t.getHour() < 10) {
		out << 0;
	}

	out << t.getHour() << ":";

	if (t.getMinute() < 10) {
		out << 0;
	}
	out << t.getMinute();

	return out;
}

bool Time::operator <=(const Time& time) const {
	if (hour < time.getHour()) {
		return true;
	} else if (hour == time.getHour()) {
		if (minute <= time.getMinute()) {
			return true;
		}
	}
	return false;
}

bool Time::operator >=(const Time& time) const {
	if (hour > time.getHour()) {
		return true;
	} else if (hour == time.getHour()) {
		if (minute >= time.getMinute()) {
			return true;
		}
	}
	return false;
}

bool Time::operator <(const Time& time) const {
	if (hour < time.getHour()) {
		return true;
	} else if (hour == time.getHour()) {
		if (minute < time.getMinute()) {
			return true;
		}
	}
	return false;
}

bool Time::operator >(const Time& time) const {
	if (hour > time.getHour()) {
		return true;
	} else if (hour == time.getHour()) {
		if (minute > time.getMinute()) {
			return true;
		}
	}
	return false;
}

void Time::setHour(unsigned int h) {
	hour = h;
}

void Time::setMinute(unsigned int m) {
	minute = m;
}

unsigned int Time::getTimeGap(const Time &time) {
	if((hour * 60 + minute) >= (time.getHour() * 60 + time.getMinute()))
		return (hour * 60 + minute) - (time.getHour() * 60 + time.getMinute());
	else
		return (time.getHour() * 60 + time.getMinute()) - (hour * 60 + minute);
}

bool Time::operator ==(const Time& time) const {
	if (hour == time.getHour() && minute == time.getMinute()) {
		return true;
	}
	return false;
}

const Time & Time::operator=(const Time & t) {
	hour = t.getHour();
	minute = t.getMinute();
	return *this;
}

istream& operator >>(istream& in, Time& t) {
	unsigned int h, m;
	in >> h;
	in.ignore();
	in >> m;
	t.setHour(h);
	t.setMinute(m);
	return in;
}

InvalidDay::InvalidDay() {

}

InvalidMonth::InvalidMonth() {

}

Time Time::operator +(const Time& time) const {
	unsigned int hourRes, minRes;
	minRes = (minute + time.getMinute()) % 60;
	hourRes = (hour + time.getHour() + (minute + time.getMinute()) / 60) % 24;
	Time result(hourRes, minRes);
	return result;
}

Time Time::operator +(unsigned int minutes) const {
	unsigned int hourRes, minRes;
	minRes = (minute + minutes) % 60;
	hourRes = (hour + (minute + minutes) / 60) % 24;
	Time result(hourRes, minRes);
	return result;
}

InvalidTimeRange::InvalidTimeRange() {

}

Date getCurrentDate() {  ///retorna dia, mês e ano atual
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
	static const DayOfWeek wday_name[] = { SUN, MON, TUE, WED, THU, FRI, SAT};

	DayOfWeek dw;
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	dw = wday_name[timeinfo->tm_wday];
	return dw;
}
