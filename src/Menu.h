#ifndef _MENU_H_
#define _MENU_H_

#include <string>
#include <utility>
#include <vector>
#include "Date.h"


using namespace std;

enum MenuResult {
	EXIT, CONTINUE, ERROR
};

class MenuHandler {
public:
	/**
	 * manages menu options(treat inputs on menus)
	 * @return MenuResult
	 */
	virtual MenuResult handle() = 0;
	inline virtual ~MenuHandler() {
	}
	;
private:

};

typedef pair<string, MenuHandler&> MenuEntry;
/**
 * leaves menu
 * @return EXIT
 */
class ExitHandler: public MenuHandler {
public:
	virtual MenuResult handle();
};

class Menu: public MenuHandler {
public:
	virtual MenuResult handle();///trata de intrepretar os inputs postos no menu
	virtual void invalidOption(int opt);///manda uma mensagem de erro com o input inserido
	virtual void invalidOption(string opt);///manda uma mensagem de erro com o input inserido

protected:
	/**
	 * prints the menu (show the possible options)
	 * entries is defined in main
	 */
	void printMenu() const;

public:
	static ExitHandler exitHandler;
	vector<MenuEntry> entries;
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
