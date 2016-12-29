#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>      // std::stringstream
#include "Date.h"
#include "Pool.h"

using namespace std;

void getInputInt(int &answer, int min, int max, string msg);///testa input de inteiros

void getInputDouble(double &answer, double min, double max, string msg);///testa input de doubles

Date getInputDate(string msg);///testa input de datas

Time getInputTime(string msg);///testa input de tempos

DayOfWeek getInputDayOfWeek(string msg);///testa inputs de dias de semana

bool poolIsFull(Pool & pool); ///ve se a piscina está cheia

#endif /* SRC_UTILITIES_H_ */
