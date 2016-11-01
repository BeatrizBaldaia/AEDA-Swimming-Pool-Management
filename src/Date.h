#ifndef _DATE_H_
#define _DATE_H_

#include <string>

using namespace std;

class Date
{
public:
	Date();
	Date(string & input);
	Date(const unsigned int & day, const unsigned int & month, const unsigned int & year);

	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;

	void setDay(const unsigned int &day);
	void setMonth(const unsigned int &month);
	void setYear(const unsigned int &year);

	bool valid() const;
	bool operator <= (const Date &date) const;
	bool operator >= (const Date &date) const;
	bool operator < (const Date &date) const;
	bool operator > (const Date &date) const;
	bool operator == (const Date &date) const;

	bool between(const Date &min, const Date &max);
	
	enum exception {InvalidMonth, InvalidDay};
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

class Time {
public:
	Time (unsigned int h, unsigned int m) : hour(h), minute(m) {} // TODO change to .cpp
	unsigned int getHour() const {return hour;} // TODO change to .cpp
	unsigned int getMinute() const {return minute;} // TODO change to .cpp
private:
	unsigned int hour;
	unsigned int minute;
};

enum DayOfWeek {
	MON, TUE, WED, THU, FRI, SAT, SUN
};

bool isLeapYear(const unsigned int &year);
unsigned int daysInMonth(const unsigned int &month, const unsigned int &year);

ostream & operator << (ostream & out, const Time & t);

ostream & operator << (ostream & out, const Date & d);
istream & operator >> (istream & in, Date & d);

#endif
