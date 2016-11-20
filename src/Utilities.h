
#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>      // std::stringstream
#include "Date.h"


using namespace std;


void ValidInputInt(int &answer, int min, int max, string msg);

Date ValidDate(string msg);

Time ValidTime(string msg);

DayOfWeek ValidDayOfWeek(string msg);

#endif /* SRC_UTILITIES_H_ */
