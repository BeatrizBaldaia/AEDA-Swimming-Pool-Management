#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <iostream>
#include <string>
#include "Shop.h"

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
	InvalidItem(string designation, string size);
	void printError();
private:
	string designation;
	string size;
};

class InvalidItems{
public:
	InvalidItems(vector<Item> v);
	void printError();
private:
	vector<Item> items;
};

class InvalidRemoveItem{
public:
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
