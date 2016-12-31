#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Menu.h"
#include "Pool.h"
#include "PoolMenu.h"

int main() {
	//cout << getInputDayOfWeek("help") << endl;
	//return 0;
	vector<string> fileNames;

	fileNames.push_back("poolinfo.txt");
	fileNames.push_back("customers.txt");
	fileNames.push_back("teachers.txt");
	fileNames.push_back("schedule.txt");
	fileNames.push_back("givenlessons.txt");
	fileNames.push_back("shop.txt");
	fileNames.push_back("provider.txt");
	fileNames.push_back("otherpools.txt");
	fileNames.push_back("promotions.txt");

	Pool pool;

	pool.setFileNames(fileNames);

	pool.load();

//	Teacher * teacher = new Teacher("Mariana Santos", Date(20, 04, 1980));
//	pool.addTeacher(teacher);
//	Lesson lesson(LessonTime(MON, Time(10, 0)), HydroGym);
//	lesson.setTeacher(teacher);
//	pool.addLesson(lesson);
//	Customer * c = new Customer("João Silva", Date(10, 12, 2005));
//	pool.addCustomer(c);
//	pool.attendLesson(lesson, c, Date(14, 11, 2016));
//	pool.attendLesson(lesson, pool.getCustomer(1), Date(14, 11, 2016));
//	pool.addFreeSwim(pool.getCustomer(3), Date(14, 11, 2016), Time(10, 10), 30);
//	pool.write();

	/*

	 Fazer:

	 Load da informação dos ficheiros para os vetores da classe Pool
	 Fazer sort de todos os vetores da classe Pool para que fiquem ordenados:
	 -> customers por ID;
	 -> teachers por número de aulas já dadas!!!;
	 -> schedule por dia da semana e para objetos com o mesmo dia da semana ordenar por hora de inicio da aula (Time) - primeiro aulas da manhã e depois as da tarde;
	 -> givenLesson da mais recente para a mais velha- ter as aulas mais recentemente dadas no inicio do vetor;
	 -> freeuses por data- ordenar dos usos em modo livre mais recentes para os mais antigos, ou seja, os que já ocorreram.

	 Não esquecer que nós queremos sempre é saber o que está a ocorrer de momento, daí quando ordenamos por datas devemos ordenar sempre da mais recente para a mais passada

	 */

	PoolMenu menu(pool),

	manage(pool),

	viewInfo(pool), viewTeachers(pool), viewCustomers(pool), viewCustomerInfo(
			pool),

	manageCustomers(pool), manageTeachers(pool), manageSchedule(pool),

	usePool(pool),

	viewTeacherInfo(pool),

	shop(pool),

	otherPools(pool), editOtherPool(pool);

	/* MANAGE POOL */

	AddCustomer addCustomer(pool);
	RemoveCustomer removeCustomer(pool);

	AddTeacher addTeacher(pool);
	RemoveTeacher removeTeacher(pool);

	AddLesson addLesson(pool);
	RemoveLesson removeLesson(pool);

	FreeSwimming freeSwimming(pool);
	AttendLesson attendLesson(pool);
	AttendToSpecificModality specificModality(pool);

	/* VIEW INFORMATIONS */

	CurrentOccupation occupation(pool);
	ViewSchedule viewSchedule(pool);
	ViewAttendance viewAttendance(pool);

	ViewTeachers viewTeachersByID(pool, ID);
	ViewTeachers viewTeachersByName(pool, NAME);
	ViewTeachers viewTeachersByGivenLessons(pool, GIVENLESSONS);
	ViewTeachers viewTeachersByLessons(pool, ASSLESSONS);

	ViewCustomers viewCustomersByID(pool, ID);
	ViewCustomers viewCustomersByName(pool, NAME);
	ViewCustomers viewCustomersByUses(pool, NUMUSES);

	ViewCustomersInformation viewCustomerInformation(pool);
	ViewCustomerUses viewCustomerUses(pool);
	CustomerMakeBill customerMakeBill(pool);
	CustomerMakeCurrentBill customerMakeCurrentBill(pool);

	ViewTeacherInformation viewTeacherInformation(pool);
	ViewTeacherSchedule viewTeacherSchedule(pool);
	ViewTeacherGivenLessons viewTeacherGivenLessons(pool);

	/* MANAGE SHOP */

	ShopSellItems shopSell(pool);
	ShopBuyItems shopBuy(pool);
	ViewShopInfo viewShop(pool);

	/* MANAGE OTHER POOLS */

	AddOtherPool addOtherPool(pool);
	AddModalityToPool addModality(pool);
	ViewOtherPools viewOtherPools(pool);

	/* MAIN MENU */

	menu.entries.push_back(MenuEntry("Exit", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("Manage", manage));
	menu.entries.push_back(MenuEntry("View information", viewInfo));
	menu.entries.push_back(MenuEntry("Shop", shop));
	menu.entries.push_back(MenuEntry("Other Pools nearby", otherPools));

	/* MANAGE OPTION and DERIVATES*/

	manage.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	manage.entries.push_back(MenuEntry("Manage customers", manageCustomers));
	manage.entries.push_back(MenuEntry("Manage teachers", manageTeachers));
	manage.entries.push_back(MenuEntry("Manage schedule", manageSchedule));
	manage.entries.push_back(MenuEntry("Use pool", usePool));

	manageCustomers.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	manageCustomers.entries.push_back(MenuEntry("Add customer", addCustomer));
	manageCustomers.entries.push_back(
			MenuEntry("Remove customer", removeCustomer));

	manageTeachers.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	manageTeachers.entries.push_back(MenuEntry("Add teacher", addTeacher));
	manageTeachers.entries.push_back(
			MenuEntry("Remove teacher", removeTeacher));

	manageSchedule.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	manageSchedule.entries.push_back(MenuEntry("Add lesson", addLesson));
	manageSchedule.entries.push_back(MenuEntry("Remove lesson", removeLesson));

	usePool.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	usePool.entries.push_back(MenuEntry("Free swimming", freeSwimming));
	usePool.entries.push_back(MenuEntry("Attend lesson", attendLesson));
	usePool.entries.push_back(
			MenuEntry("Attend to one specific Modality", specificModality));

	/* VIEW INFORMATION MENU */

	viewInfo.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewInfo.entries.push_back(MenuEntry("View attendances", viewAttendance));
	viewInfo.entries.push_back(
			MenuEntry("View current occupation", occupation));
	viewInfo.entries.push_back(MenuEntry("View schedule", viewSchedule));
	viewInfo.entries.push_back(MenuEntry("View teachers", viewTeachers));
	viewInfo.entries.push_back(MenuEntry("View customers", viewCustomers));

	viewTeachers.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewTeachers.entries.push_back(
			MenuEntry("View one teacher's info", viewTeacherInfo));
	viewTeachers.entries.push_back(
			MenuEntry("View all teachers sorted by ID", viewTeachersByID));
	viewTeachers.entries.push_back(
			MenuEntry("View all teachers sorted by name", viewTeachersByName));
	viewTeachers.entries.push_back(
			MenuEntry("View all teachers sorted by lessons given",
					viewTeachersByGivenLessons));
	viewTeachers.entries.push_back(
			MenuEntry("View all teachers sorted by number of lessons per week",
					viewTeachersByLessons));

	viewCustomers.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewCustomers.entries.push_back(
			MenuEntry("View one customer's info", viewCustomerInfo));
	viewCustomers.entries.push_back(
			MenuEntry("View all customers sorted by ID", viewCustomersByID));
	viewCustomers.entries.push_back(
			MenuEntry("View all customers sorted by name",
					viewCustomersByName));
	viewCustomers.entries.push_back(
			MenuEntry("View customers sorted by number of pool uses",
					viewCustomersByUses));

	viewTeacherInfo.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewTeacherInfo.entries.push_back(
			MenuEntry("View teacher's information", viewTeacherInformation));
	viewTeacherInfo.entries.push_back(
			MenuEntry("View teacher's schedule", viewTeacherSchedule));
	viewTeacherInfo.entries.push_back(
			MenuEntry("View teacher's given lessons", viewTeacherGivenLessons));

	viewCustomerInfo.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewCustomerInfo.entries.push_back(
			MenuEntry("View customer's information", viewCustomerInformation));
	viewCustomerInfo.entries.push_back(
			MenuEntry("View customer's pool uses", viewCustomerUses));
	viewCustomerInfo.entries.push_back(
			MenuEntry("Make customer's current month bill",
					customerMakeCurrentBill));
	viewCustomerInfo.entries.push_back(
			MenuEntry("Make customer's specific month bill", customerMakeBill));

	/* SHOP MENU */

	shop.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	shop.entries.push_back(MenuEntry("View Shop Information", viewShop));
	shop.entries.push_back(MenuEntry("Costumer -> Buy Products!", shopSell));
	shop.entries.push_back(MenuEntry("Increase Stock", shopBuy));

	/* OTHER POOLS MENU */

	otherPools.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	otherPools.entries.push_back(
			MenuEntry("View Pools nearby Info", viewOtherPools));
	otherPools.entries.push_back(
			MenuEntry("Add a new Pool nearby record", addOtherPool));
	otherPools.entries.push_back(
			MenuEntry("Edit Pools' nearby information", editOtherPool));

	editOtherPool.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	editOtherPool.entries.push_back(
			MenuEntry("Add one Modality to Pool nearby", addModality));

	cout << pool.getName() << endl;
	menu.handle();

	return 0;
}
