#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>      // std::stringstream
#include "Date.h"

using namespace std;

void getInputInt(int &answer, int min, int max, string msg);

Date getInputDate(string msg);

Time getInputTime(string msg);

DayOfWeek getInputDayOfWeek(string msg);

#endif /* SRC_UTILITIES_H_ */
