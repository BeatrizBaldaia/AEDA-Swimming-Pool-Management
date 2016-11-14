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
	pool.loadPoolInfo();
	pool.loadCustomers();

	Customer * c = new Customer("Jo�o Silva", Date(10,12,2005));
	pool.addCustomer(c);
	pool.writePoolInfo();
	pool.writeCustomers();

	return 0;

	//TODO: load and sort!
	/*

	 Fazer:

	 Load da informa��o dos ficheiros para os vetores da classe Pool
	 Fazer sort de todos os vetores da classe Pool para que fiquem ordenados:
	 	 -> customers por ID;
	 	 -> teachers por n�mero de aulas j� dadas!!!;
	 	 -> schedule por dia da semana e para objetos com o mesmo dia da semana ordenar por hora de inicio da aula (Time) - primeiro aulas da manh� e depois as da tarde;
	 	 -> givenLesson da mais recente para a mais velha- ter as aulas mais recentemente dadas no inicio do vetor;
	 	 -> freeuses por data- ordenar dos usos em modo livre mais recentes para os mais antigos, ou seja, os que j� ocorreram.

	 N�o esquecer que n�s queremos sempre � saber o que est� a ocorrer de momento, da� quando ordenamos por datas devemos ordenar sempre da mais recente para a mais passada

	 */

	PoolMenu menu(pool), manage(pool), viewInfo(pool);
	AddCustomer addCustomer(pool);
	CurrentOccupation occupation(pool);

	menu.entries.push_back(MenuEntry("Exit", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("Manage", manage));
	menu.entries.push_back(MenuEntry("View information", viewInfo));
	menu.entries.push_back(MenuEntry("See Current Occupation", occupation));

	manage.entries.push_back(MenuEntry("Back", Menu::exitHandler));

	viewInfo.entries.push_back(MenuEntry("Back", Menu::exitHandler));

	menu.handle();

	return 0;
}
