#include <sstream>
#include <iostream>
#include "Date.h"

Date::Date(const unsigned int & day, const unsigned int & month, const unsigned int & year)
{
	if (month >= 1 && month <= 12)
	{
		if (day >= 1 && day <= daysInMonth(month, year))
		{
			this->day = day;
			this->month = month;
			this->year = year;
		}
		throw InvalidDay;
	}

	throw InvalidMonth;
}

Date::Date() {

}

Date::Date(string & input) {
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

bool isLeapYear(const unsigned int &year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned int daysInMonth(const unsigned int &month, const unsigned int &year)
{
	if ((month % 2 == 1 && month <= 7) || (month % 2 == 0 && month >= 8))
	{
		return 31;
	}
	else if (month == 2)
	{
		if (isLeapYear(year))
		{
			return 29;
		}
		else
		{
			return 28;
		}
	}
	else
	{
		return 30;
	}
}

bool Date::valid() const
{
	if (month >= 1 && month <= 12)
	{
		if (day >= 1 && day <= daysInMonth(month, year))
		{
			return true;
		}
	}
	return false;
}

bool Date::operator <= (const Date &date) const {
	if (year < date.getYear())
	{
		return true;
	}
	else if (year == date.getYear())
	{
		if (month < date.getMonth())
		{
			return true;
		}
		else if (month == date.getMonth())
		{
			if (day <= date.getDay())
			{
				return true;
			}
		}
	}
	return false;
}

bool Date::operator >= (const Date &date) const {
	if (year > date.getYear())
	{
		return true;
	}
	else if (year == date.getYear())
	{
		if (month > date.getMonth())
		{
			return true;
		}
		else if (month == date.getMonth())
		{
			if (day >= date.getDay())
			{
				return true;
			}
		}
	}
	return false;
}

bool Date::operator < (const Date &date) const {
	if (year < date.getYear())
	{
		return true;
	}
	else if (year == date.getYear())
	{
		if (month < date.getMonth())
		{
			return true;
		}
		else if (month == date.getMonth())
		{
			if (day < date.getDay())
			{
				return true;
			}
		}
	}
	return false;
}

bool Date::operator > (const Date &date) const {
	if (year > date.getYear())
	{
		return true;
	}
	else if (year == date.getYear())
	{
		if (month > date.getMonth())
		{
			return true;
		}
		else if (month == date.getMonth())
		{
			if (day > date.getDay())
			{
				return true;
			}
		}
	}
	return false;
}

bool Date::operator==(const Date & date) const {
	return this->day == date.day && this->month == date.month && this->year == date.year;
}

bool Date::between(const Date &min, const Date &max) {
	if (*this >= min && *this <= max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream & operator << (ostream & out, const Date & d) {
	if (d.getDay() < 10)
	{
		out << '0';
	}
	out << d.getDay();

	out << '/';

	if (d.getMonth() < 10)
	{
		out << '0';
	}
	out << d.getMonth();

	out << '/';

	out << d.getYear();

	return out;
}

istream & operator >> (istream & in, Date & date) {
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

DayOfWeek calcDayOfWeek(Date date) {
	int d = date.getDay(), m = date.getMonth(), y = date.getYear();
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	int result = ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
	switch (result){
	case 1: return MON;
	case 2: return TUE;
	case 3: return WED;
	case 4: return THU;
	case 5: return FRI;
	case 6: return SAT;
	case 7: return SUN;
	}
}

ostream & operator << (ostream & out, const DayOfWeek & d) {
	switch (d){
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
	if(hour <= time.getHour()) {
		if(minute <= time.getMinute()) {
			return true;
		}
		return false;
	}
	return false;
}

bool Time::operator >=(const Time& time) const {
	if(hour >= time.getHour()) {
		if(minute >= time.getMinute()) {
			return true;
		}
		return false;
	}
	return false;
}

#include <cmath>

bool Time::operator <(const Time& time) const {
	return hour*60+minute < time.getHour()*60+time.getMinute();
}

bool Time::operator >(const Time& time) const {
	return hour*60+minute > time.getHour()*60+time.getMinute();
}

unsigned int Time::operator -(const Time &time){
	return abs(hour*60+minute - time.getHour()*60+time.getMinute());
}

bool Time::operator ==(const Time& time) const {
	if(hour == time.getHour() && minute == time.getMinute()) {
		return true;
	}
	return false;
}

