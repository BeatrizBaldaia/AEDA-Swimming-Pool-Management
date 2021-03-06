#include "PoolMenu.h"

#include <crtdefs.h>
#include <algorithm>    // std::unique, std::distance
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <vector>

#include "Date.h"
#include "Exceptions.h"
#include "Lesson.h"
#include "Person.h"
#include "Pool.h"
#include "PoolUse.h"
#include "Shop.h"
#include "Utilities.h"

/* POOL MENU */

PoolMenu::PoolMenu(Pool & pool) :
		pool(pool) {

}

/* ADD CUSTOMER MENU */

AddCustomer::AddCustomer(Pool & pool) :
		pool(pool) {

}

MenuResult AddCustomer::handle() {
	string name;
	cout << "Insert customer's name: ";
	getline(cin, name);
	Date birthdate = getInputDate("Insert customer's birthday (DD/MM/YYYY)");
	cout << "\nInsert customer's address:\n";
	cout << "=> City: ";
	string city;
	getline(cin, city);
	cout << "=> Street: ";
	string street;
	getline(cin, street);
	cout << "=> Number of the door: ";
	int number;
	cin >> number;
	cin.ignore();
	cout << "=> Postal Code: ";
	string code;
	getline(cin, code);
	cout << "=> Cellphone number:";
	long cellphoneNum;
	cin >> cellphoneNum;
	cin.ignore();
	ContactInfo contactInfo(city, street, number, code, cellphoneNum);
	Customer * c = new Customer(name, birthdate, contactInfo);
	c->setCity(city);
	c->setStreet(street);
	c->setNumber(number);
	c->setPostalCode(code);
	pool.addCustomer(c);
	cout << endl << name << " created with ID " << c->getID() << "! \n";
	pool.write();
	return CONTINUE;
}

/* REMOVE CUSTOMER MENU */

RemoveCustomer::RemoveCustomer(Pool & pool) :
		pool(pool) {
}

MenuResult RemoveCustomer::handle() {
	unsigned int ID;
	cout << "Insert customer ID:";
	cin >> ID;
	Customer * c;
	try {
		c = pool.getCustomer(ID);
	} catch (NonExistentCustomerID &x) {
		cout << "\n \nCustomer doesn't belong to Pool or was already deleted";
		return CONTINUE;
	}
	for (GivenLesson * g : pool.getGivenLessons()) {
		g->removeCustomer(ID);
	}
	pool.removeCustomer(ID);
	if (pool.isCustomerInactive(c)) {
		pool.activateCustomer(c);
	}
	cout << c->getName() << " removed!\n \n";
	pool.write();
	return CONTINUE;
}

/* CURRENT OCCUPATION MENU */

CurrentOccupation::CurrentOccupation(Pool & pool) :
		pool(pool) {

}

MenuResult CurrentOccupation::handle() {
	DayOfWeek day = getCurrentDayOfWeek();
	cout << endl << day << endl;
	Time duration(1, 0);
	Time time = getCurrentTime();
//	Date date = getCurrentDate();
	bool existLessonsToday = true, currentlesson;
	Lesson lesson;
	try {
		lesson = pool.getNextLesson(day, time, currentlesson); //throw NoMoreLessons
	} catch (NoMoreLessonsInDay & x) {
		existLessonsToday = false;
	}

	if (existLessonsToday) {
		lesson = pool.getNextLesson(day, time, currentlesson);
		if (currentlesson) {
			cout << "\nLesson of " << lesson.getModality() << " ends in "
					<< (lesson.getTime() + duration).getTimeGap(time)
					<< " minutes";
		} else {
			cout << "\nLesson of " << lesson.getModality() << " starts in "
					<< lesson.getTime().getTimeGap(time) << " minutes";
		}
	} else {
		cout << "\nThere are no more lessons today";
	}
	unsigned int customersInPool = 0;
	for (Customer * c : pool.getCustomers()) {
		for (PoolUse * p : c->getPoolUses()) {
			if (p->getTime() + p->getDuration() >= time
					&& p->getTime() <= time) {
				customersInPool++;
				break;
			}
		}
	}
	if (customersInPool == 0) {
		cout << "\n \nThere is nobody in the pool\n";
	} else if (customersInPool == 1) {
		cout << "\n \nThere is 1 customer in the pool\n";
	} else {
		cout << "\n \nThere are " << customersInPool << " customers in pool\n";
	}
	cout << "\nVacancies: " << pool.getMaxCustomers() - customersInPool << endl
			<< endl;
	return CONTINUE;

}

/* CUSTOMERS ATTENDANCE MENU */

ViewAttendance::ViewAttendance(Pool& pool) :
		pool(pool) {
}

MenuResult ViewAttendance::handle() {
	for (Customer * c : pool.getCustomers()) {
		cout << "\n \nUses of " << c->getName() << ":\n";
		for (PoolUse * p : c->getPoolUses()) {
			if (p->getLesson() == NULL) {
				cout << "\nUse type: Free swim";
			} else {
				cout << "\nUse type: Lesson";
			}
			cout << "\nDate: " << p->getDate() << "\nTime: " << p->getTime()
					<< "\nDuration: " << p->getDuration() << " minutes\nCost: "
					<< p->getCost() << endl;
		}
	}
	return CONTINUE;
}

/* MAKE BILL MENU */

CustomerMakeCurrentBill::CustomerMakeCurrentBill(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerMakeCurrentBill::handle() {
	unsigned int customerID;
	unsigned int month = getCurrentDate().getMonth();
	unsigned int year = getCurrentDate().getYear();
	cout << "\nInsert Customer ID: ";
	cin >> customerID;
	Customer * c;
	try {
		c = pool.getCustomer(customerID);
	} catch (NonExistentCustomerID &x) {
		printf("\nNon existing Customer");
		return CONTINUE;
	}
	cout << "Printing bill...";
	vector<GivenLesson *> customerGivenLessons; //vetor que nos d� as given lessons do cliente nesse mes
	vector<PoolUse *> customerFreeSwimUses; //vetor que nos d� os usos da piscina (freeswimuses) do cliente nesse mes
	for (PoolUse * p : c->getPoolUses()) {
		if (p->getDate().getMonth()
				== month&& p->getDate().getYear() == year && p->getLesson() == NULL)
			customerFreeSwimUses.push_back(p);
	}
	for (GivenLesson * g : pool.getGivenLessons()) {
		if (g->getDate().getMonth() == month
				&& g->getDate().getYear() == year) {
			for (Customer * k : g->getCustomers()) {
				if (k->getID() == customerID)
					customerGivenLessons.push_back(g);
			}
		}
	}
	string billName = "Bill of ";
	billName += c->getName();
	billName += ".txt";
	ofstream bill;
	bill.open(billName.c_str());
	bill
			<< "*          **          **          Super Cool Pool          **          **          *\n"
			<< "-------------------------------------------------------------------------------------\n"
			<< "Customer: " << c->getName() << endl;
	bill << "ID: " << c->getID() << endl;
	bill
			<< "-------------------------------------------------------------------------------------\n"
			<< "                                   Bill of " << month << "/"
			<< year << endl << endl << endl;
	bill << "Lessons assisted: " << customerGivenLessons.size() << endl << endl;
	for (GivenLesson * g : customerGivenLessons) {
		double cost;
		for(PoolUse * p : c->getPoolUses())
		{
			if(p->getLesson() == g)
				cost = p->getCost();
		}
		bill << g->getLesson().getModality() << " (" << g->getDate()
				<< ").....................................�" << setprecision(3) << cost << endl;
	}
	bill << endl << endl << "Free swimming usage: "
			<< customerFreeSwimUses.size() << " times\n\n";
	for (PoolUse * p : customerFreeSwimUses) {
		if (p->getDuration() < 100)
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ")..........................................�" << fixed
					<< setprecision(2) << p->getCost() << endl;
		else
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ").........................................�" << fixed
					<< setprecision(2) << p->getCost() << endl;
	}
	bill << "\n\n                            Total:   �" << fixed
			<< setprecision(2) << c->getMonthCost(month, year);
	return CONTINUE;
}

CustomerMakeBill::CustomerMakeBill(Pool & pool) :
		pool(pool) {

}

MenuResult CustomerMakeBill::handle() {
	unsigned int customerID;
	string monthString;
	unsigned int month;
	unsigned int year;
	cout << "\nInsert Customer ID: ";
	cin >> customerID;
	Customer * c;
	try {
		c = pool.getCustomer(customerID);
	} catch (NonExistentCustomerID &x) {
		printf("\nNon existing Customer");
		return CONTINUE;
	}
	cout << "\n\nInsert month and year (ex. MM/YYYY): ";
	cin >> monthString;
	if (monthString.size() != 7 || monthString[2] != '/') {
		return CONTINUE;
	}
	cout << "Printing bill...";
	stringstream monthStream(monthString);
	monthStream >> month;
	monthStream.ignore();
	monthStream >> year;
	vector<GivenLesson *> customerGivenLessons; //vetor que nos d� as given lessons do cliente nesse mes
	vector<PoolUse *> customerFreeSwimUses; //vetor que nos d� os usos da piscina (freeswimuses) do cliente nesse mes
	for (PoolUse * p : c->getPoolUses()) {
		if (p->getDate().getMonth()
				== month&& p->getDate().getYear() == year && p->getLesson() == NULL)
			customerFreeSwimUses.push_back(p);
	}
	for (GivenLesson * g : pool.getGivenLessons()) {
		if (g->getDate().getMonth() == month
				&& g->getDate().getYear() == year) {
			for (Customer * k : g->getCustomers()) {
				if (k->getID() == customerID)
					customerGivenLessons.push_back(g);
			}
		}
	}
	string billName = "Bill of ";
	billName += c->getName();
	billName += ".txt";
	ofstream bill;
	bill.open(billName.c_str());
	bill
			<< "*          **          **          Super Cool Pool          **          **          *\n"
			<< "-------------------------------------------------------------------------------------\n"
			<< "Customer: " << c->getName() << endl;
	bill << "ID: " << c->getID() << endl;
	bill
			<< "-------------------------------------------------------------------------------------\n"
			<< "                                   Bill of " << monthString
			<< endl << endl << endl;
	bill << "Lessons assisted: " << customerGivenLessons.size() << endl << endl;
	for (GivenLesson * g : customerGivenLessons) {
		double cost;
		for(PoolUse * p : c->getPoolUses())
		{
			if(p->getLesson() == g)
				cost = p->getCost();
		}
		bill << g->getLesson().getModality() << " (" << g->getDate()
				<< ").....................................�" << setprecision(3) << cost << endl;
	}
	bill << endl << endl << "Free swimming usage: "
			<< customerFreeSwimUses.size() << " times\n\n";
	for (PoolUse * p : customerFreeSwimUses) {
		if (p->getDuration() < 100)
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ")..........................................�" << fixed
					<< setprecision(2) << p->getCost() << endl;
		else
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ").........................................�" << fixed
					<< setprecision(2) << p->getCost() << endl;
	}
	bill << "\n\n                            Total:   �" << fixed
			<< setprecision(2) << c->getMonthCost(month, year);
	return CONTINUE;
}

/* ADD TEACHER MENU */

AddTeacher::AddTeacher(Pool & pool) :
		pool(pool) {
}

MenuResult AddTeacher::handle() {
	string teacherName;
	cout << "\nInsert Teacher's name: ";
	getline(cin, teacherName);
	Date birthdate = getInputDate("Insert teacher's birthday (DD/MM/YYYY)");
	cout << "\nInsert customer's address:\n";
	cout << "=> City: ";
	string city;
	getline(cin, city);
	cout << "=> Street: ";
	string street;
	getline(cin, street);
	cout << "=> Number of the door: ";
	int number;
	cin >> number;
	cin.ignore();
	cout << "=> Postal Code: ";
	string code;
	getline(cin, code);
	cout << "=> Cellphone number:";
	long cellphoneNum;
	cin >> cellphoneNum;
	cin.ignore();
	ContactInfo contactInfo(city, street, number, code, cellphoneNum);
	Teacher * t = new Teacher(teacherName, birthdate, contactInfo);

	pool.addTeacher(t);
	cout << endl << teacherName << " created!\n";
	pool.write();
	return CONTINUE;
}

/* REMOVE TEACHER MENU */

RemoveTeacher::RemoveTeacher(Pool & pool) :
		pool(pool) {

}

MenuResult RemoveTeacher::handle() {
	unsigned int ID;
	cout << "\nInsert Teacher's ID: ";
	cin >> ID;
	pool.removeTeacher(ID);
	pool.write();
	return CONTINUE;
}

/* VIEW TEACHER SCHEDULE */

ViewTeacherSchedule::ViewTeacherSchedule(Pool & pool) :
		pool(pool) {

}

MenuResult ViewTeacherSchedule::handle() {
	unsigned int ID;
	cout << "\nInsert teacher's ID: ";
	cin >> ID;
	Teacher * t;
	try {
		t = pool.getTeacher(ID);
	} catch (NonExistentTeacherID &x) {
		cout << "\nThere is no teacher with that ID.\n";
		return CONTINUE;
	}
	cout << "\n" << t->getName() << "'s schedule:";

	if (pool.getLessons(t->getID()).size() == 0) {
		cout << "\nThere are no lessons scheduled.\n";
		return CONTINUE;
	}

	DayOfWeek d = pool.getLessons(t->getID())[0].getDayOfWeek();

	cout << "\n" << d << ":\n";

	for (const Lesson & i : pool.getLessons(t->getID())) {
		if (i.getDayOfWeek() != d) {
			d = i.getDayOfWeek();
			cout << "\n" << d << ":\n";
		}
		cout << i.getTime() << " - " << i.getModality() << endl;

	}
	return CONTINUE;
}

/* VIEW SCHEDULE MENU */

ViewSchedule::ViewSchedule(Pool & pool) :
		pool(pool) {

}

MenuResult ViewSchedule::handle() {
	vector<Lesson> schedule = pool.getSchedule();
	if (schedule.size() == 0) {
		cout << "\nThere are no lessons scheduled.\n";
		return CONTINUE;
	}
	sort(schedule.begin(), schedule.end(),
			[](Lesson & a, Lesson & b) {
				return (a.getDayOfWeek()*60*24 + a.getTime().getHour()*60 + a.getTime().getMinute() < b.getDayOfWeek()*60*24 + b.getTime().getHour()*60 + b.getTime().getMinute());
			});

	DayOfWeek d = schedule[0].getDayOfWeek();

	cout << "\n" << d << ":\n";

	for (const Lesson & i : schedule) {
		if (i.getDayOfWeek() != d) {
			d = i.getDayOfWeek();
			cout << "\n" << d << ":\n";
		}
		cout << i.getTime() << " - " << i.getModality() << "\nTeacher: "
				<< i.getTeacher()->getName() << endl << endl;

	}
	return CONTINUE;
}

/* ATTEND LESSON MENU */

AttendLesson::AttendLesson(Pool & pool) :
		pool(pool) {

}

MenuResult AttendLesson::handle() {

	vector<Lesson> lessons = pool.getLessons(getCurrentDate(),
			getCurrentTime());
	int choice;
	int customerID;

	Customer * c;
	bool noExistID = false;
	do {
		try {
			getInputInt(customerID, 0,500, "\nInsert customer's ID");
			c = pool.getCustomer(customerID);
			noExistID = false;
		} catch (NonExistentCustomerID & x) {
			cout << "\nNo customer with such ID";
			noExistID = true;
		}
	} while (noExistID);

	if (lessons.size() == 0) {
		cout << "\nNo more lessons scheduled for today.\n";
		return CONTINUE;
	}
	cout << endl;
	for (int i = 0; i < lessons.size(); i++) {
		cout << i + 1 << " - " << lessons[i].getTime() << " ("
				<< lessons[i].getModality() << ")\n";
	}
	cout << "\n0 - Cancel";
	getInputInt(choice, 0, lessons.size(), "Choose one class to attend today");
	if (choice == 0) {
		return CONTINUE;
	}

	double discount = 0;
	try {
		PromotionalCampaign promCamp = pool.getCurrentPromotion();
		discount = promCamp.getDiscount();
		cout
				<< "\nWe are in the middle of a promotional campaign. All lessons and free uses have a discount of "
				<< promCamp.getDiscount() << ".\n";
	} catch (NoCurrentCampaign & e) {

	}
	try {
		pool.attendLesson(lessons[choice - 1], c, getCurrentDate(), discount);
	} catch (CustomerAlreadyAttendedLesson & x) {
		cout << "\nThe customer is already in the lesson.\n";
		return CONTINUE;
	} catch (PoolIsFull & x) {
		cout << "\nLesson is full.\n";
		return CONTINUE;
	}
	if (pool.isCustomerInactive(c)) {
		pool.activateCustomer(c);
	}
	pool.write();
	return CONTINUE;
}

AttendToSpecificModality::AttendToSpecificModality(Pool & pool) :
		pool(pool) {
}

MenuResult AttendToSpecificModality::handle() {
	int customerID;
	Customer * c;

	bool noExistID = false;
	do {
		try {
			getInputInt(customerID, 0, 500, "\nInsert customer's ID");
			c = pool.getCustomer(customerID);
			noExistID = false;
		} catch (NonExistentCustomerID & x) {
			cout << "\nNo customer with such ID";
			noExistID = true;
		}
	} while (noExistID);

	cout << "\nList of Modalities: \n \n";
	cout << "1 -> " << static_cast<Modality>(0) << '\n';
	cout << "2 -> " << static_cast<Modality>(1) << '\n';
	cout << "3 -> " << static_cast<Modality>(2) << '\n';
	cout << "4 -> " << static_cast<Modality>(3) << '\n';
	cout << "5 -> " << static_cast<Modality>(4) << "\n\n";
	cout << "0 -> Cancel\n\n";
	int modN;
	getInputInt(modN, 0, 5, "Insert the Modality number");
	if (modN == 0) {
		return CONTINUE;
	}
	Modality mod = static_cast<Modality>((modN - 1));
	vector<Lesson> lessons;
	try {
		lessons = pool.getLessonByModality(mod);
	} catch (InvalidModality &x) {
		x.printError();
		try {
			ptrOtherPool oP(pool.getNextPool(mod));
			cout << "You can visit the nearest Pool ( " << oP.getName() << ", "
					<< oP.getDistance()
					<< " Km from here ) to have a lesson of " << mod;
		} catch (NoModality &y) {
			y.printError();
		}
		return CONTINUE;
	}

	for (int i = 0; i < lessons.size(); i++) {
		cout << i + 1 << " -> " << lessons[i].getDayOfWeek() << " at "
				<< lessons[i].getTime() << " with "
				<< lessons[i].getTeacher()->getName() << endl;
	}
	cout << endl << "0 -> Cancel \n\n";
	int choice;
	getInputInt(choice, 0, lessons.size(),
			"Choose the lesson you want to book/attend");
	if (choice == 0) {
		return CONTINUE;
	}
	Date today = getCurrentDate();
	choice--;
	DayOfWeek dayLesson = lessons[choice].getDayOfWeek();
	int dayOfWeekLesson = dayLesson;
	int dayOfWeekToday = getCurrentDayOfWeek();
	int diff;
	///obter o dia da aula escolhida partindo do dia atual
	if (dayOfWeekLesson >= dayOfWeekToday) {
		diff = dayOfWeekLesson - dayOfWeekToday;
	} else {
		diff = (7 - dayOfWeekToday) + dayOfWeekLesson;
	}
	while (diff > 0) {
		++today;
		diff--;
	}

	double discount = 0;
	try {
		PromotionalCampaign promCamp = pool.getCurrentPromotion();
		discount = promCamp.getDiscount();
		cout
				<< "\nWe are in the middle of a promotional campaign. All lessons and free uses have a discount of "
				<< promCamp.getDiscount() << ".\n";
	} catch (NoCurrentCampaign & e) {

	}
	try {
		pool.attendLesson(lessons[choice], c, today, discount);
	} catch (CustomerAlreadyAttendedLesson & x) {
		cout << "\nThe customer is already in the lesson.\n";
		return CONTINUE;
	} catch (PoolIsFull & x) {
		cout << "\nLesson is full.\n";
		try {
			ptrOtherPool oP(pool.getNextPool(mod));
			cout << "You can visit the nearest Pool ( " << oP.getName() << ", "
					<< oP.getDistance()
					<< " Km from here ) to have a lesson of " << mod;
		} catch (NoModality &y) {
			y.printError();
		}
		return CONTINUE;
	}
	if (pool.isCustomerInactive(c)) {
		pool.activateCustomer(c);
	}
	pool.write();
	return CONTINUE;
}

/* ADD LESSON MENU */

AddLesson::AddLesson(Pool & pool) :
		pool(pool) {
}

MenuResult AddLesson::handle() {
	int modalityOpt;
	Modality modality;
	Time time;
	DayOfWeek weekDay;
	cout << endl;
	bool existLesson;
	do {
		existLesson = false;
		weekDay = getInputDayOfWeek("Insert the day of the week");
		cout << endl;
		time = getInputTime("Insert lesson's time (HH:MM)");
		Time tf(23, 0);
		Time ti(6, 0);
		if (time >= tf || time <= ti) {
			cout << "Can't add lessons from 23:00 to 6:00.";
			return CONTINUE;
		}
		for (const Lesson & i : pool.getSchedule()) {
			if (i.getDayOfWeek() == weekDay) {
				if (i.getTime().getTimeGap(time) <= 60) {
					cout << "\nLessons are going to overlap...\n\n";
					existLesson = true;
					break;
				}
			}
		}
	} while (existLesson);
	for (size_t i = 0; i < 6; i++) {
		Modality mod = static_cast<Modality>(i);
		cout << i << " - " << mod << endl;
	}
	getInputInt(modalityOpt, 0, 5, "Choose one modality");
	modality = static_cast<Modality>(modalityOpt);
	LessonTime lessonTime;
	lessonTime.first = weekDay;
	lessonTime.second = time;
	Lesson l(lessonTime, modality);
	pool.addLesson(l); //TODO criar excep��o de j� existir uma aula a esta hora
	pool.write();
	cout << "\nLesson created.\n";
	return CONTINUE;
}

/* REMOVE LESSON MENU */

RemoveLesson::RemoveLesson(Pool & pool) :
		pool(pool) {

}

MenuResult RemoveLesson::handle() {
	int choice;
	cout << endl;
	int indice = 0;
	for (Lesson & i : pool.getSchedule()) {
		indice++;
		cout << indice << " - " << i.getModality() << endl << i.getDayOfWeek()
				<< " - " << i.getTime() << endl;
	}
	cout << "\n0 - Cancel\n";

	getInputInt(choice, 0, indice, "Choose lesson to be deleted");
	if (choice == 0) {
		return CONTINUE;
	}
	pool.removeLesson(choice - 1);
	pool.distributeLessons();
	pool.write();
	cout << "\nLesson deleted.\n";
	return CONTINUE;
}

/* VIEW TEACHER GIVEN LESSON */

ViewTeacherGivenLessons::ViewTeacherGivenLessons(Pool & pool) :
		pool(pool) {
}

MenuResult ViewTeacherGivenLessons::handle() {
	while (true) {
		try {

			int ID;
			cout << "\nInsert teacher's ID: ";
			cin >> ID;
			Teacher * t;

			t = pool.getTeacher(ID);

			vector<GivenLesson *> result = pool.getGivenLessons(ID);

			if (result.size() == 0) {
				cout << "\nThe teacher has no given lessons.\n";
				return CONTINUE;
			}

			cout << "\n" << t->getName() << "'s given lessons:\n\n";

			for (GivenLesson * i : result) {
				cout << i->getDate() << " - " << i->getLesson().getTime()
						<< "\n" << i->getLesson().getModality() << "\n"
						<< i->getCustomers().size() << " customers\n\n";
			}

			return CONTINUE;

		} catch (NonExistentTeacherID &x) {
			cout << "\nThere is no teacher with that ID.\n";
		}
	}
}

/* VIEW TEACHERS */

ViewTeachers::ViewTeachers(Pool& pool, OrderBy orderBy) :
		pool(pool), orderBy(orderBy) {
}

MenuResult ViewTeachers::handle() {
	cout << endl;
	vector<Teacher *> teachers = pool.getTeachers();
	switch (orderBy) {
	case (ID):
		sort(teachers.begin(), teachers.end(),
				[](Teacher * a, Teacher * b) {return a->getID() < b->getID();});
		break;
	case (NAME):
		sort(teachers.begin(), teachers.end(),
				[](Teacher * a, Teacher * b) {return a->getName() < b->getName();});
		break;
	case (GIVENLESSONS):
		sort(teachers.begin(), teachers.end(),
				[this](Teacher * a, Teacher * b) {return pool.getGivenLessons(a->getID()).size() < pool.getGivenLessons(b->getID()).size();});
		break;
	case (ASSLESSONS):
		sort(teachers.begin(), teachers.end(),
				[this](Teacher * a, Teacher * b) {return pool.getLessons(a->getID()).size() < pool.getLessons(b->getID()).size();});
		break;
	}
	for (Teacher * t : teachers) {
		cout << "ID: " << t->getID() << "\nName: " << t->getName()
				<< "\nBirthdate: " << t->getBirthDate()
				<< "\nAssigned lessons: " << pool.getLessons(t->getID()).size()
				<< "\nGiven lessons: "
				<< pool.getGivenLessons(t->getID()).size() << endl << endl;
	}
	return CONTINUE;
}

/* FREE SWIMMING */

FreeSwimming::FreeSwimming(Pool & pool) :
		pool(pool) {
}

MenuResult FreeSwimming::handle() {
	if (poolIsFull(pool)) {
		cout << "Pool is full, try again later\n";
		return CONTINUE;
	}
	int ID;
	unsigned int duration = 0;
	bool existe = false;
	getInputInt(ID, 0, 500, "\nInsert customer's ID");
	for (Customer * x : pool.getCustomers()) {
		if (x->getID() == ID) {
			existe = true;
			break;
		}
	}
	if (!existe) {
		cout << "There's no customer with that ID.\n\n";
		return CONTINUE;
	}
	Customer * c = pool.getCustomer(ID);
	for (PoolUse * p : c->getPoolUses()) {
		if (p->getTime().getTimeGap(getCurrentTime()) < p->getDuration()) {
			cout << "\nCustomer in lesson, try later\n";
			return CONTINUE;
		}
	}
	while (true) {
		cout << "\nInsert pretended duration: ";
		cin >> duration;
		if (duration > 120 || duration < 0) {
			cout << "\nInvalid duration (can't surpass 120 minutes)\n";
			continue;
		}
		break;
	}
	double discount = 0;
	try {
		PromotionalCampaign promCamp = pool.getCurrentPromotion();
		discount = promCamp.getDiscount();
		cout
				<< "\nWe are in the middle of a promotional campaign. All lessons and free uses have a discount of "
				<< promCamp.getDiscount() << ".\n";
		FreeSwimUse * f = new FreeSwimUse(getCurrentDate(), getCurrentTime(),
				duration, discount);
		pool.addFreeUse(f);
		c->addUse(f);
		if (pool.isCustomerInactive(c)) {
			pool.activateCustomer(c);
		}
		pool.write();
		return CONTINUE;
		if (pool.isCustomerInactive(c)) {
			pool.activateCustomer(c);
		}
		pool.write();
		return CONTINUE;
	} catch (NoCurrentCampaign & e) {
		cout << "\nNo campaign is currently running.\n";
		FreeSwimUse * f = new FreeSwimUse(getCurrentDate(), getCurrentTime(),
				duration, discount);
		pool.addFreeUse(f);
		c->addUse(f);
		if (pool.isCustomerInactive(c)) {
			pool.activateCustomer(c);
		}
		pool.write();
		return CONTINUE;
		if (pool.isCustomerInactive(c)) {
			pool.activateCustomer(c);
		}
		pool.write();
		return CONTINUE;
	}
}

/* VIEW CUSTOMERS */

ViewCustomers::ViewCustomers(Pool& pool, OrderBy orderBy) :
		pool(pool), orderBy(orderBy) {
}

MenuResult ViewCustomers::handle() {
	cout << endl;
	vector<Customer *> customers = pool.getCustomers();
	switch (orderBy) {
	case (ID):
		sort(customers.begin(), customers.end(),
				[](Customer * a, Customer * b) {return a->getID() < b->getID();});
		break;
	case (NAME):
		sort(customers.begin(), customers.end(),
				[](Customer * a, Customer * b) {return a->getName() < b->getName();});
		break;
	case (NUMUSES):
		sort(customers.begin(), customers.end(),
				[this](Customer * a, Customer * b) {return a->getPoolUses().size() < b->getPoolUses().size();});
		break;
	}
	for (Customer *c : customers) {
		cout << "\nID: " << c->getID() << "\nName: " << c->getName()
				<< "\nBirthdate: " << c->getBirthDate() << "\nPool uses: "
				<< c->getPoolUses().size() << "\nCost: "
				<< c->getMonthCost(getCurrentDate().getMonth(),
						getCurrentDate().getYear()) << endl;
	}
	cout << endl << endl << "Inactive Customers: \n \n";
	if (pool.getInactiveCustomer().size() == 0) {
		cout << "There're no Inactive Customers. \n \n";
	} else {
		hashCustomer table = pool.getInactiveCustomer();
		hashCustomer::iterator it;
		for (it = table.begin(); it != table.end(); it++) {
			cout << (*it)->getName() << endl;
		}
	}
	return CONTINUE;
}

/* VIEW CUSTOMERS INFORMATION */

ViewCustomersInformation::ViewCustomersInformation(Pool & pool) :
		pool(pool) {
}

MenuResult ViewCustomersInformation::handle() {
	while (true) {
		try {
			unsigned int ID;

			cout << "\nInsert customer's ID: ";
			cin >> ID;
			Customer * c = pool.getCustomer(ID);
			cout << "\nID: " << c->getID() << "\nName: " << c->getName()
					<< "\nBirthdate: " << c->getBirthDate() << "\nPool uses: "
					<< c->getPoolUses().size() << "\nCost: "
					<< c->getMonthCost(getCurrentDate().getMonth(),
							getCurrentDate().getYear()) << endl;
			return CONTINUE;
		} catch (NonExistentCustomerID &x) {
			cout << "There's no such customer with ID " << x.ID;
		}
	}
}

/* VIEW CUSTOMER USES MENU */

ViewCustomerUses::ViewCustomerUses(Pool & pool) :
		pool(pool) {
}

MenuResult ViewCustomerUses::handle() {
	while (true) {
		try {
			unsigned int ID;
			cout << "\nInsert customer's ID: ";
			cin >> ID;
			Customer * c = pool.getCustomer(ID);
			cout << endl;
			for (PoolUse * p : c->getPoolUses()) {
				if (p->getLesson() == NULL) {
					cout << "\nUse type: Free swim";
				} else {
					cout << "\nUse type: Lesson";
				}
				cout << "\nDate: " << p->getDate() << "\nTime: " << p->getTime()
						<< "\nDuration: " << p->getDuration()
						<< " minutes\nCost: " << p->getCost() << endl;
			}
			return CONTINUE;

		} catch (NonExistentCustomerID &x) {
			cout << "There's no such customer with ID " << x.ID;
		}
	}

}

/* VIEW TEACHER INFORMATION */

ViewTeacherInformation::ViewTeacherInformation(Pool & pool) :
		pool(pool) {
}

MenuResult ViewTeacherInformation::handle() {
	while (true) {
		try {
			unsigned int ID;
			cout << "\nInsert teacher's ID: ";
			cin >> ID;
			Teacher * t = pool.getTeacher(ID);
			cout << "\nID: " << t->getID() << "\nName: " << t->getName()
					<< "\nBirthdate: " << t->getBirthDate()
					<< "\nAssigned lessons: "
					<< pool.getLessons(t->getID()).size() << "\nGiven lessons: "
					<< pool.getGivenLessons(t->getID()).size() << endl << endl;
			return CONTINUE;
		} catch (NonExistentTeacherID &x) {
			cout << "There's no such teacher with ID " << x.ID;
		}
	}
}

/* SHOP MENU */

ShopSellItems::ShopSellItems(Pool & pool) :
		pool(pool) {
}

MenuResult ShopSellItems::handle() {
	string name;
	cout << "Insert customer's name: ";
	getline(cin, name);
	Customer * c = NULL;
	try {
		c = pool.getCustomer(name); ///cliente que vai realizar a compra
	} catch (NonExistentCustomerName &x) {
		cout << "There's no such customer. \n \n ";
		return CONTINUE;
	}
	cout << "\nList of our products: \n \n";
	vector<Item> v = pool.getShop()->getItems();
	for (int i = 0; i < v.size(); i++) {
		cout << (i + 1) << " -> " << v[i].getDesignation() << " (size "
				<< v[i].getSize() << ")" << endl;
	}
	cout << endl << "0 -> Stop adding products \n \n";
	cout << endl;
	vector<Item> items; ///itens que o utilizador vai comprar
	while (true) {
		int prodN;
		getInputInt(prodN, 0, v.size(), "Insert the product number");
		if (prodN == 0) {
			break;
		}
		int prodQ;
		getInputInt(prodQ, 0, 30000, "Insert the product quantity");
		if (prodN <= v.size()) {
			Item i(v[prodN - 1].getDesignation(), v[prodN - 1].getSize(),
					prodQ);
			items.push_back(i);
		}
	}
	if (items.empty()) {
		return CONTINUE;
	}
	Shop * s = pool.getShop();
	try {
		s->sellItem(c, items);
		pool.write();
		return CONTINUE;
	} catch (InvalidRemoveItem &x) {
		x.printError();
		pool.write();
	} catch (InvalidItems &x) {
		x.printError();
		pool.write();
	} catch (InvalidStock &x) {
		x.printError();
		pool.write();
	}
}

ShopBuyItems::ShopBuyItems(Pool & pool) :
		pool(pool) {
}

MenuResult ShopBuyItems::handle() {
	cout << "\nList of provider's Products: \n \n";
	vector<Item> v = pool.getProviderItems();
	vector<Item> items;
	for (int i = 0; i < v.size(); i++) {
		cout << (i + 1) << " -> " << v[i].getDesignation() << " (size "
				<< v[i].getSize() << ") \n";
	}
	cout << endl << "0 -> Stop adding products \n \n";
	while (true) {
		int prodN;
		getInputInt(prodN, 0, v.size(), "Insert the product number");
		if (prodN == 0) {
			break;
		}
		int prodQ;
		getInputInt(prodQ, 0, 30000, "Insert the product quantity");
		if (prodN <= v.size()) {
			Item i(v[prodN - 1].getDesignation(), v[prodN - 1].getSize(),
					prodQ);
			items.push_back(i);
		}
	}
	Shop * shop = pool.getShop();
	shop->buyItem(items);
	pool.writeShop();
	return CONTINUE;
}

ViewShopInfo::ViewShopInfo(Pool & pool) :
		pool(pool) {
}

MenuResult ViewShopInfo::handle() {
	vector<Item> v = pool.getShop()->getItems();
	cout << "\nShop << " << pool.getShop()->getName()
			<< " >> List of Products: \n \n";
	for (const Item & x : v) {
		cout << "Designation: " << x.getDesignation() << "\nSize: "
				<< x.getSize() << "\nCurrent Stock: " << x.getStock() << endl
				<< endl;
	}
	return CONTINUE;
}

/* OTHER POOLS MANAGE */

ViewOtherPools::ViewOtherPools(Pool & pool) :
		pool(pool) {
}

MenuResult ViewOtherPools::handle() {
	cout << "\nList of Pools Nearby: \n\n";
	priority_queue<ptrOtherPool> queue = pool.getOtherPools();
	while (!queue.empty()) {
		ptrOtherPool oP = queue.top();
		cout << "Name: " << oP.getName() << endl << "Distance: "
				<< oP.getDistance() << " Km\nModalities given: ";
		vector<Modality> vM = oP.getModalityLessons();
		for (int i = 0; i < vM.size(); i++) {
			cout << vM[i];
			if (i != (vM.size() - 1)) {
				cout << ", ";
			}
		}
		cout << endl << endl;
		queue.pop();
	}
	cout << endl;
	return CONTINUE;
}

AddOtherPool::AddOtherPool(Pool & pool) :
		pool(pool) {
}

MenuResult AddOtherPool::handle() {
	cout << "\nInsert Pool Name: ";
	string name;
	getline(cin, name);
	cout << "\nDistance: ";
	double distance;
	vector<Modality> vM;
	cin >> distance;
	cout << "\nList of Modalities: \n\n";
	cout << "1 -> " << static_cast<Modality>(0) << '\n';
	cout << "2 -> " << static_cast<Modality>(1) << '\n';
	cout << "3 -> " << static_cast<Modality>(2) << '\n';
	cout << "4 -> " << static_cast<Modality>(3) << '\n';
	cout << "5 -> " << static_cast<Modality>(4) << "\n \n";
	cout << "0 -> Stop adding Modalities \n \n";
	while (true) {
		int modN;
		getInputInt(modN, 0, 5, "Insert the Modality number");
		if (modN == 0) {
			break;
		}
		Modality mod = static_cast<Modality>((modN - 1));
		vM.push_back(mod);
	}
	ptrOtherPool oP(new OtherPool(name, distance, vector<Modality>()));
	for (const Modality & m : vM)
	{
		oP.addModality(m);
	}
	pool.addOtherPool(oP);
	pool.writeOtherPools();
	return CONTINUE;
}

AddModalityToPool::AddModalityToPool(Pool & pool) :
		pool(pool) {
}

MenuResult AddModalityToPool::handle() {
	cout << "\nInsert Pool Name: ";
	string name;
	getline(cin, name);
	cout << endl << name << endl << endl;
	vector<Modality> vM;
	cout << "\nList of Modalities: \n\n";
	cout << "1 -> " << static_cast<Modality>(0) << '\n';
	cout << "2 -> " << static_cast<Modality>(1) << '\n';
	cout << "3 -> " << static_cast<Modality>(2) << '\n';
	cout << "4 -> " << static_cast<Modality>(3) << '\n';
	cout << "5 -> " << static_cast<Modality>(4) << "\n \n";
	cout << "0 -> Stop adding Modalities\n \n";
	int modN;
	while (true) {
		getInputInt(modN, 0, 5, "Insert the Modality number");
		if (modN == 0) {
			break;
		}
		Modality mod = static_cast<Modality>((modN - 1));
		vM.push_back(mod);
	}
	try {
		pool.addModalityToPool(name, vM);
	} catch (InvalidPool &x) {
		x.printError();
		return CONTINUE;
	}
	pool.writeOtherPools();
	return CONTINUE;
}

/* PROMOTIONAL CAMPAIGN */

ViewCurrentCampaign::ViewCurrentCampaign(Pool & pool) :
		pool(pool) {
}

MenuResult ViewCurrentCampaign::handle() {
//	Date day = getCurrentDate();
	try {
		PromotionalCampaign promo = pool.getCurrentPromotion();
		cout << "\nThe promotional campaign has started on "
				<< promo.getBeginDate() << " and will end on "
				<< promo.getEndDate()
				<< ".\nAll lessons and free uses have a discount of "
				<< promo.getDiscount() << endl << endl;
		return CONTINUE;
	} catch (NoCurrentCampaign &e) {
		cout << "\nNo campaign is currently running.\n";
		return CONTINUE;
	}
}

UpdateCustomersInfo::UpdateCustomersInfo(Pool & pool) :
		pool(pool) {

}

MenuResult UpdateCustomersInfo::handle() {
//	Date day = getCurrentDate();
	try {
		PromotionalCampaign promo = pool.getCurrentPromotion();
		cout << "\nOne Promotional Campaign has started on "
				<< promo.getBeginDate() << " and will end on "
				<< promo.getEndDate()
				<< ".\nAll lessons and free uses have a discount of "
				<< promo.getDiscount() << endl;
	} catch (NoCurrentCampaign &e) {
		cout << "\nNo campaign is currently running, so  there's no need to update inactive customers' address.\n";
		return CONTINUE;
	}
	cout << "\nList of the current inactive Customers:\n\n";
	hashCustomer tab = pool.getInactiveCustomer();
	hashCustomer::const_iterator it = tab.begin();
	int i = 1;
	for (; it != tab.end(); it++) {
		cout << i << " - " << (*it)->getName() << " : " << (*it)->getStreet()
				<< ", " << (*it)->getNumber() << ", " << (*it)->getPostalCode()
				<< ", " << (*it)->getCity() << ", " << (*it)->getCellphoneNum()
				<< endl;
		int answer;
		getInputInt(answer, 0, 1,
				"Do you want to update the customer's address?\n\n---------   ----------\n|0 -> No|   |1 -> Yes|\n---------   ----------\n");
		if (answer == 1)
		{
			pool.eraseInactive((*it));
			cout << "=> City: ";
			string city;
			getline(cin, city);
			cout << "=> Street: ";
			string street;
			getline(cin, street);
			int number;
			getInputInt(number,0,999,"=> Number of the door");
			cout << "=> Postal Code: ";
			string code;
			getline(cin, code);
			cout << "=> Contact number: ";
			long phoneNumber;
			cin >> phoneNumber;
			cin.ignore();
			(*it)->setCity(city);
			(*it)->setStreet(street);
			(*it)->setNumber(number);
			(*it)->setPostalCode(code);
			(*it)->setCellphoneNum(phoneNumber);
			pool.insertInactive((*it));
		}
		cout << endl << endl;
		i++;
	}
	cout << "All inactive customers were updated!\n\n";
	pool.writeCustomers();
	return CONTINUE;


}

AddCampaign::AddCampaign(Pool & pool) :
		pool(pool) {
}

MenuResult AddCampaign::handle() {
	Date startDate = getInputDate("Insert the start date (DD/MM/YYYY)");
	Date endDate = getInputDate("Insert the end date (DD/MM/YYYY)");
	if (endDate - startDate < 0) {
		cout << "\nInvalid dates.\n";
		return CONTINUE;
	}
	double discount;
	getInputDouble(discount, 0, 1,
			"Insert the Promotional Campaign discount value");
	PromotionalCampaign promo(startDate, endDate, discount);
	try {
		pool.addPromotionalCampaign(promo);
		pool.writePromotions();
		return CONTINUE;
	} catch (OverlapingCampaign &e) {
		cout << "There's already one Promotional Campaign occurring\n";
		return CONTINUE;
	}

}

ViewInactiveCustomers::ViewInactiveCustomers(Pool & pool) :
		pool(pool) {
}

MenuResult ViewInactiveCustomers::handle() {
	cout << "List of the Inactive Customers:\n\n";
	hashCustomer tab = pool.getInactiveCustomer();
	hashCustomer::iterator it = tab.begin();
	for(it; it != tab.end(); it++) {
		cout << (*it)->getID() << " - " << (*it)->getName() << endl;
	}
	return CONTINUE;
}
