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
