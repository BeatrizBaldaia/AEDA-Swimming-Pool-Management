#include "Exceptions.h"

/* Invalid input */

InvalidInputInt::InvalidInputInt(int answer, int min, int max) {
	this->answer = answer;
	this->min = min;
	this->max = max;
}

void InvalidInputInt::printError() {
	cout << endl << "Invalid input. Insert an integer in the range [" << min
			<< ", " << max << "]." << endl;
}

/* Invalid input DATE */

InvalidInputDate::InvalidInputDate() {

}

void InvalidInputDate::printError() {
	cout << endl
			<< "Invalid input format. Insert the date in the form DD/MM/YYYY."
			<< endl;
}

/* Invalid input TIME */

InvalidInputTime::InvalidInputTime() {

}

void InvalidInputTime::printError() {
	cout << endl << "Invalid input format. Insert the time in the form HH:MM."
			<< endl;
}

/* Invalid input DAY OF WEEK */

InvalidInputDayOfWeek::InvalidInputDayOfWeek() {

}

void InvalidInputDayOfWeek::printError() {
	cout << endl
			<< "Invalid input for day of the week. Insert one of the possible days of the week.";
}

/* INVALID ITEM */

InvalidItem::InvalidItem(string designation, string size){
	this->designation = designation;
	this->size = size;
}

void InvalidItem::printError(){
	cout << endl << "There's no such Item: " << designation << " of size " << size << endl;
}

InvalidItems::InvalidItems(vector<Item> v){
	items = v;
}

void InvalidItems::printError(){
	cout << endl << "There're no such Items: " << endl;
	for(const Item &x : items){
		cout << x.getDesignation() << " of size " << x.getSize() << endl;
	}
	cout << endl;
}

InvalidStock::InvalidStock(vector<Item> v){
	items = v;
}

void InvalidStock::printError(){
	cout << endl << "The stock is not enough for the following Items: " << endl;
	for(const Item &y : items){
		cout << y.getDesignation() << " of size " << y.getSize() << ": lack of "<< y.getStock() << " units" << endl;
	}
	cout << endl;
}

InvalidRemoveItem::InvalidRemoveItem(vector<Item> nonexistent, vector<Item> overflowItems){
	this->nonexistent = nonexistent;
	this->overflowItems = overflowItems;
}

void InvalidRemoveItem::printError(){
	cout << endl << "There're no such Items: " << endl;
	for(const Item &x : nonexistent){
		cout << x.getDesignation() << " of size " << x.getSize() << endl;
	}
	cout << endl << "The stock is not enough for the following Items: " << endl;
	for(const Item &y : overflowItems){
		cout << y.getDesignation() << " of size " << y.getSize()  << ": lack of "<< y.getStock() << " units" << endl;
	}
	cout << endl;
}
