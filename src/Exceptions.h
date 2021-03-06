#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <string>
#include <vector>

#include "Lesson.h"
#include "Shop.h"

using namespace std;

/**
 *  INVALID INPUT */

class InvalidInputInt {
	int answer;
	int min, max;
public:
	InvalidInputInt(int answer, int min, int max);
	void printError();
};

class InvalidInputDouble {
	double answer;
	double min, max;
public:
	InvalidInputDouble(double answer, double min, double max);
	void printError();
};

/**
 *  INVALID INPUT DATE */

class InvalidInputDate {
public:
	InvalidInputDate();
	void printError();
};

/**
 *  INVALID INPUT TIME */

class InvalidInputTime {
public:
	InvalidInputTime();
	void printError();
};

/**
 *  INVALID INPUT DAY OF WEEK */

class InvalidInputDayOfWeek {
public:
	InvalidInputDayOfWeek();
	void printError();
};

/**
 *  INVALID ITEM */

class InvalidItem {
public:
	InvalidItem(string designation, string size);
	void printError();
private:
	string designation;
	string size;
};

class InvalidItems {
public:
	InvalidItems(vector<Item> v);
	void printError();
private:
	vector<Item> items;
};

class InvalidRemoveItem {
public:
	InvalidRemoveItem(vector<Item> nonexistent, vector<Item> overflowItems);
	void printError();
private:
	vector<Item> nonexistent;
	vector<Item> overflowItems;
};

class InvalidStock {
public:
	InvalidStock(vector<Item> v);
	void printError();
private:
	vector<Item> items;
};

/** INVALID POOL */

class InvalidPool {
public:
	InvalidPool(string name);
	void printError();
private:
	string name;
};

/** INVALID MODALITY */

class InvalidModality {
public:
	InvalidModality(Modality modality);
	void printError();
private:
	Modality modality;
};

class NoModality {
public:
	NoModality(Modality modality);
	void printError();
private:
	Modality modality;
};

class NoCurrentCampaign {
public:
	NoCurrentCampaign() {
	}
};
#endif /* SRC_EXCEPTIONS_H_ */
