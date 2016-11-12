#include "PoolMenu.h"
#include "Pool.h"

int main() {

	vector <string> fileNames;

	fileNames.push_back("poolinfo.txt");
	fileNames.push_back("customers.txt");
	fileNames.push_back("teachers.txt");
	fileNames.push_back("schedule.txt");
	fileNames.push_back("givenlessons.txt");

	Pool pool;

	pool.setFileNames(fileNames);

	PoolMenu menu(pool), manage(pool), viewInfo(pool);
	AddCustomer addCustomer(pool);

	menu.entries.push_back(MenuEntry("Exit", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("Manage", manage));
	menu.entries.push_back(MenuEntry("View information", viewInfo));

	manage.entries.push_back(MenuEntry("Back", Menu::exitHandler));

	viewInfo.entries.push_back(MenuEntry("Back", Menu::exitHandler));

	menu.handle();

	return 0;
}
