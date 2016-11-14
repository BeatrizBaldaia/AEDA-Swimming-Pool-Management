#ifndef _DATE_H_
#define _DATE_H_

#include <string>

using namespace std;

enum DayOfWeek {
	MON, TUE, WED, THU, FRI, SAT, SUN
};

class Date
{
public:
	Date();
	Date(string & input);
	Date(const unsigned int & day, const unsigned int & month, const unsigned int & year);

	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	DayOfWeek getDayOfWeek() const;

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
	Time();
	Time(unsigned int h, unsigned int m);
	unsigned int getHour() const;
	unsigned int getMinute() const;
	void setHour(unsigned int h);
	void setMinute(unsigned int m);
	bool operator <= (const Time &time) const;
	bool operator >= (const Time &time) const;
	bool operator < (const Time &time) const;
	bool operator > (const Time &time) const;
	bool operator == (const Time &time) const;
	unsigned int getTimeGap(const Time &time);
private:
	unsigned int hour;
	unsigned int minute;
};

bool isLeapYear(const unsigned int &year);
unsigned int daysInMonth(const unsigned int &month, const unsigned int &year);

ostream & operator << (ostream & out, const Time & t);
ostream & operator << (ostream & out, const DayOfWeek & d);
ostream & operator << (ostream & out, const Date & d);
istream & operator >> (istream & in, Date & d);
istream & operator >> (istream & in, Time & t);

#endif
