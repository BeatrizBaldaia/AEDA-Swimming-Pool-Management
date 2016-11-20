
#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <iostream>
#include <string>

using namespace std;

/* INVALID INPUT */

class InvalidInput{
	int answer;
	int min, max;
public:
	InvalidInput(int answer, int min, int max);
	void what();
};

/* INVALID INPUT DATE */

class InvalidInputDate{
public:
	InvalidInputDate();
	void what();
};



#endif /* SRC_EXCEPTIONS_H_ */
