#include "Menu.h"

int main() {
	Menu menu("Main Menu");

	menu.entries.push_back(MenuEntry("Exit", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("This", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("Is", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("A", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("Menu", Menu::exitHandler));

	menu.handle();

	return 0;
}
