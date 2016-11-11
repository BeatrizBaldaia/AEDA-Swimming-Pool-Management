#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include <string>
#include "Date.h"

using namespace std;

enum MenuResult
{
	EXIT, CONTINUE, ERROR
};

class MenuHandler
{
public:
	virtual MenuResult handle() = 0;
	inline virtual ~MenuHandler() {};
private:

};

typedef pair <string, MenuHandler&> MenuEntry;

class ExitHandler : public MenuHandler
{
public:
	virtual MenuResult handle();
};

class Menu : public MenuHandler
{
public:
	Menu(string name);
	virtual MenuResult handle();
	virtual void invalidOption(int opt);
	virtual void invalidOption(string opt);

protected:
	void printMenu() const;

public:
	static ExitHandler exitHandler;
	vector <MenuEntry> entries;
	string name;
};

/*class OneDateProcessor : public MenuHandler {
public:
	OneDateProcessor(string prompt, string error);
	Date readDate(string prompt, string error);
	virtual MenuResult handle();

protected:
	virtual MenuResult handle(Date date) = 0;

	string error;
	string prompt1;
};

class TwoDateProcessor : public OneDateProcessor {
public:
	TwoDateProcessor(string prompt1, string prompt2, string error);

protected:
	virtual MenuResult handle(Date date1, Date date2) = 0;
	virtual MenuResult handle(Date date1);

	string prompt2;
};*/

Date readDate(string prompt);

string readFileName(const string & prompt);

#endif
