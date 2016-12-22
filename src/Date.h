#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>
#include <string>

using namespace std;

/**
 * Day of week type.
 */
enum DayOfWeek {
	MON, TUE, WED, THU, FRI, SAT, SUN
};

/**
 * Date class.
 */
class Date {
public:
	/**
	 * Default constructor.
	 */
	Date();
	/**
	 * Constructor by string.
	 * @param input string in format DD/MM/YYYY;
	 */
	Date(string & input);
	/**
	 * Constructor by values.
	 * @param day
	 * @param month
	 * @param year
	 */
	Date(unsigned int day, unsigned int month, unsigned int year);

	unsigned int getDay() const;///retorna o dia
	unsigned int getMonth() const;///retorna o mes
	unsigned int getYear() const;///retorna o ano
	DayOfWeek getDayOfWeek() const;///retorna o dia da semana

	void setDay(const unsigned int &day);///muda o dia
	void setMonth(const unsigned int &month);///muda o mes
	void setYear(const unsigned int &year);///muda o ano

	bool valid() const;///ve se uma data é válida (se não temos o mes 13 por exemplo)
	const Date & operator=(const Date & d);
	bool operator <=(const Date &date) const;
	bool operator >=(const Date &date) const;
	bool operator <(const Date &date) const;
	bool operator >(const Date &date) const;
	bool operator ==(const Date &date) const;
	/**
	 * Returns difference between dates in days.
	 * @param date
	 * @return
	 */
	int operator -(const Date &date) const;

	bool between(const Date &min, const Date &max);///ve se uma data está entre duas datas

private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

class Time {
public:
	Time();
	Time(unsigned int h, unsigned int m);

	unsigned int getHour() const;///retorna hora
	unsigned int getMinute() const;///retorna minuto

	void setHour(unsigned int h);
	void setMinute(unsigned int m);

	bool operator <=(const Time &time) const;
	bool operator >=(const Time &time) const;
	bool operator <(const Time &time) const;
	bool operator >(const Time &time) const;
	bool operator ==(const Time &time) const;
	const Time & operator=(const Time & t);

	Time operator +(const Time &time) const;///somar dois Times
	Time operator +(unsigned int minutes) const;///somar um tempo com minutos

	unsigned int getTimeGap(const Time &time);///ver diferença de minutos entre dois tempos
private:
	unsigned int hour;
	unsigned int minute;
};

bool isLeapYear(const unsigned int &year);
unsigned int daysInMonth(const unsigned int &month, const unsigned int &year);

ostream & operator <<(ostream & out, const Time & t);
ostream & operator <<(ostream & out, const DayOfWeek & d);
ostream & operator <<(ostream & out, const Date & d);
istream & operator >>(istream & in, Date & d);
istream & operator >>(istream & in, Time & t);

Date getCurrentDate();
Time getCurrentTime();
DayOfWeek getCurrentDayOfWeek();

class InvalidDay {
public:
	InvalidDay();
};

class InvalidMonth {
public:
	InvalidMonth();
};

class InvalidTimeRange {
public:
	InvalidTimeRange();
};

#endif
