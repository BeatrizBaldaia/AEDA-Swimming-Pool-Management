#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>      // std::stringstream
#include "Date.h"
#include "Pool.h"

using namespace std;
/**\brief verificacao do input de inteiros*/
void getInputInt(int &answer, int min, int max, string msg);///testa input de inteiros
/**\brief verificacao do input de doubles*/
void getInputDouble(double &answer, double min, double max, string msg);///testa input de doubles
/**\brief verificacao do input para objetos da classe Data*/
Date getInputDate(string msg);///testa input de datas
/**\brief verificacao do input para objetos da classe Time*/
Time getInputTime(string msg);///testa input de tempos
/**\brief verificacao do input para dia da semana (enum DayOfWeek)*/
DayOfWeek getInputDayOfWeek(string msg);///testa inputs de dias de semana
/**\brief verificacao da lotacao da piscina */
bool poolIsFull(Pool & pool); ///ve se a piscina está cheia

#endif /* SRC_UTILITIES_H_ */
