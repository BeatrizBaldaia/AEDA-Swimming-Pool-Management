#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <iostream>
#include <string>

using namespace std;

/* INVALID INPUT */

class InvalidInputInt {
	int answer;
	int min, max;
public:
	InvalidInputInt(int answer, int min, int max);
	void printError();
};

/* INVALID INPUT DATE */

class InvalidInputDate {
public:
	InvalidInputDate();
	void printError();
};

/* INVALID INPUT TIME */

class InvalidInputTime {
public:
	InvalidInputTime();
	void printError();
};

/* INVALID INPUT DAY OF WEEK */

class InvalidInputDayOfWeek {
public:
	InvalidInputDayOfWeek();
	void printError();
};

/* INVALID ITEM */

class InvalidItem{
public:
	InvalidItem(string designation, unsigned int size);
	void printError();
private:
	string designation;
	unsigned int size;
};

class InvalidItems{
public:
	InvalidItems(vector<Item> v);
	void printError();
private:
	vector<Item> items;
};

class InvalidRemoveItem{
	InvalidRemoveItem(vector<Item> nonexistent, vector<Item> overflowItems);
	void printError();
private:
	vector<Item> nonexistent;
	vector<Item> overflowItems;
};

class InvalidStock{
public:
	InvalidStock(vector<Item> v);
	void printError();
private:
	vector<Item> items;
};

#endif /* SRC_EXCEPTIONS_H_ */
