#include "Exceptions.h"

/* INVALID INPUT */

InvalidInput::InvalidInput(int answer, int min, int max){
	this->answer = answer;
	this->min = min;
	this->max = max;
}

void InvalidInput::what(){
	cout << "Invalid Input. Insert an integer in the range [ " << min << ", " << max << " ]" << endl;
}

/* INVALID INPUT DATE */

InvalidInputDate::InvalidInputDate(){

}

void InvalidInputDate::what(){
	cout << "Invalid Input for date. Insert the date in the form 01 / 01 / 1999." << endl;
}


/* INVALID INPUT TIME */

InvalidInputTime::InvalidInputTime(){

}

void InvalidInputTime::what(){
	cout << "Invalid Input for time. Insert the time in the form 08 : 30." << endl;
}

/* INVALID INPUT DAY OF WEEK */

InvalidInputDayOfWeek::InvalidInputDayOfWeek(){

}

void InvalidInputDayOfWeek::what(){
	cout << "Invalid Input for day of the week. Insert one of the possible days of the week.";
}
