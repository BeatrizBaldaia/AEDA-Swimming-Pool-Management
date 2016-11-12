#include "PoolMenu.h"
#include "Person.h"

PoolMenu::PoolMenu(Pool & pool) : pool(pool) {

}

AddCustomer::AddCustomer(Pool & pool) : pool(pool) {

}

MenuResult AddCustomer::handle() {
	string name;
	cout << "Insert the customer's name: ";
	getline(cin, name); //POSSIVELMENTE SUBSTITUIR POR UM getName que verifique o formato do nome.
	cout << name;
	cout << "Insert the customer's birthdate: ";

	return EXIT;
}
