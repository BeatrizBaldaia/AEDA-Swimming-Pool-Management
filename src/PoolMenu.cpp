#include "PoolMenu.h"

#include <algorithm>    // std::unique, std::distance
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>



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
	Date Bdate = ValidDate("Insert customer's birthday (ex. 01 / 01 / 1999)");
	Customer c(name,Bdate);
	pool.addCustomer(&c);
	cout << endl << name << " created!\n";
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
		cout << "\n\nCustomer doesn't belong to Pool or was already deleted";
		return CONTINUE;
	}
	for (GivenLesson * g : pool.getGivenLessons()) {
		g->removeCustomer(ID);
	}
	pool.removeCustomer(ID);
	cout << c->getName() << " removed!\n\n";
	pool.write();
	return CONTINUE;
}

/* CURRENT OCCUPATION MENU */

CurrentOccupation::CurrentOccupation(Pool & pool) :
		pool(pool) {

}

MenuResult CurrentOccupation::handle() {
	DayOfWeek day = getCurrentDayOfWeek();
	Time time = getCurrentTime();
	Date date = getCurrentDate();
	bool currentlesson = false; //condição para saber se está a ocorrer de momento uma aula na piscina
	try {
		Lesson lesson = pool.getNextLesson(day, time, currentlesson);

		if (currentlesson) {
			cout << lesson.getModality() << "ends in "
					<< lesson.getTime().getTimeGap(time) << "minutes" << endl;
			GivenLesson givenlesson(lesson, date);
			//vector<GivenLesson>::iterator it;
			//it = find(pool.getGivenLessons().begin(), pool.getGivenLessons().end(), givenlesson); //ALGORITMO DE PESQUISA!!!!
			//unsigned int numberCustomersLesson = it->getCustomers().size(); //número de pessoas que estão na aula atual
			unsigned int numberCustomersLesson = 0;
			for (GivenLesson * x : pool.getGivenLessons()) {
				if ((*x) == givenlesson) {
					numberCustomersLesson = x->getCustomers().size();
					break;
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// somar a numberCustomersLesson o número de clientes que também estão agora a usar a piscina, mas em modo livre//
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			numberCustomersLesson += pool.CustomersFreeUse(date, time);
			cout << "There are " << numberCustomersLesson
					<< " people in the pool." << endl;
			if (pool.getMaxCustomers() - numberCustomersLesson > 0) {
				cout << "Only "
						<< pool.getMaxCustomers() - numberCustomersLesson
						<< " more people can log in." << endl;
			} else {
				cout << "Nobody else can log in." << endl;
			}
		} else {
			cout << "Next lesson ( " << lesson.getModality() << " ) starts in "
					<< lesson.getTime().getTimeGap(time) << " minutes" << endl;
			unsigned int numberCustomersFree = pool.CustomersFreeUse(date,
					time); //número de clientes que estão a usar a piscina em modo livre
			if (numberCustomersFree == 0) {
				cout << "No one is in the pool at the moment." << endl
						<< pool.getMaxCustomers() << " people can log in."
						<< endl;
			} else {
				cout << "There are " << numberCustomersFree
						<< " people in the pool." << endl;
				if (pool.getMaxCustomers() - numberCustomersFree > 0) {
					cout << "Only "
							<< pool.getMaxCustomers() - numberCustomersFree
							<< " more people can log in." << endl;
				} else {
					cout << "Nobody else can log in." << endl;
				}
			}
		}
	} catch (NoMoreLessonsInDay &x) {
		cout << "There's no more lessons today." << endl;
		//dar o número de pessoas a usar a piscina em modo livre
		//fazer return/ acabar com a função
		unsigned int numberCustomersFree = pool.CustomersFreeUse(date, time); //número de clientes que estão a usar a piscina em modo livre
		if (numberCustomersFree == 0) {
			cout << "No one is in the pool at the moment." << endl
					<< pool.getMaxCustomers() << " people can log in." << endl;
		} else {
			cout << "There are " << numberCustomersFree
					<< " people in the pool." << endl;
			if (pool.getMaxCustomers() - numberCustomersFree > 0) {
				cout << "Only " << pool.getMaxCustomers() - numberCustomersFree
						<< " more people can log in." << endl;
			} else {
				cout << "Nobody else can log in." << endl;
			}
		}
	}

	return CONTINUE;

}

/* CUSTOMERS ATTENDANCE MENU */

ViewAttendance::ViewAttendance(Pool& pool) :
		pool(pool) {
}

MenuResult ViewAttendance::handle() {
	for (Customer * c : pool.getCustomers()) {
		cout << "\n\nUses of " << c->getName() << ":\n";
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
	cout << "Insert Customer ID: ";
	cin >> customerID;
	vector<GivenLesson *> customerGivenLessons; //vetor que nos dá as given lessons do cliente nesse mes
	vector<PoolUse *> customerFreeSwimUses; //vetor que nos dá os usos da piscina (freeswimuses) do cliente nesse mes
	Customer * c;
	try {
		c = pool.getCustomer(customerID);
	} catch (NonExistentCustomerID &x) {
		printf("\nNon existing Customer");
		return CONTINUE;
	}
	for (PoolUse * p : c->getPoolUses()) {
		if (p->getDate().getMonth() == month && p->getDate().getYear() == year)
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
		bill << g->getLesson().getModality() << " (" << g->getDate()
				<< ").....................................€3.00" << endl;
	}
	bill << endl << endl << "Free swimming usage: "
			<< customerFreeSwimUses.size() << " times\n\n";
	for (PoolUse * p : customerFreeSwimUses) {
		if (p->getDuration() < 100)
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ")..........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
		else
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ").........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
	}
	bill << "\n\n                            Total:   €" << fixed
			<< setprecision(2)
			<< c->getMonthCost(month, year) + 3 * customerGivenLessons.size();
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
	cout << "Insert Customer ID: ";
	cin >> customerID;
	Customer * c;
	try {
		c = pool.getCustomer(customerID);
	} catch (NonExistentCustomerID &x) {
		printf("\nNon existing Customer");
		return CONTINUE;
	}
	cout << "\n\nInsert month and year (ex. 02/1995): ";
	cin >> monthString;
	if (monthString.size() != 7 || monthString[2] != '/')
		return CONTINUE;
	stringstream monthStream(monthString);
	monthStream >> month;
	monthStream.ignore();
	monthStream >> year;
	vector<GivenLesson *> customerGivenLessons; //vetor que nos dá as given lessons do cliente nesse mes
	vector<PoolUse *> customerFreeSwimUses; //vetor que nos dá os usos da piscina (freeswimuses) do cliente nesse mes
	for (PoolUse * p : c->getPoolUses()) {
		if (p->getDate().getMonth() == month && p->getDate().getYear() == year)
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
		bill << g->getLesson().getModality() << " (" << g->getDate()
				<< ").....................................€3.00" << endl;
	}
	bill << endl << endl << "Free swimming usage: "
			<< customerFreeSwimUses.size() << " times\n\n";
	for (PoolUse * p : customerFreeSwimUses) {
		if (p->getDuration() < 100)
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ")..........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
		else
			bill << p->getDuration() << " minutes (" << p->getDate()
					<< ").........................................€" << fixed
					<< setprecision(2) << p->getCost() << endl;
	}
	bill << "\n\n                            Total:   €" << fixed
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

	Date Bdate = ValidDate("Insert teacher's birthday (ex. 01 / 01 / 1999)");
	Teacher t(teacherName, Bdate);

	pool.addTeacher(&t);
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
	int counter = 0;
	pool.removeTeacher(ID);
	for (Lesson & l : pool.getSchedule()) {
		l.setTeacher(pool.getTeachers()[counter]);
		counter++;
		if (counter == pool.getTeachers().size())
			counter = 0;
	}
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
	if (pool.getSchedule().size() == 0) {
		cout << "\nThere are no lessons scheduled.\n";
		return CONTINUE;
	}

	DayOfWeek d = pool.getSchedule()[0].getDayOfWeek();

	cout << "\n" << d << ":\n";

	for (const Lesson & i : pool.getSchedule()) {
		if (i.getDayOfWeek() != d) {
			d = i.getDayOfWeek();
			cout << "\n" << d << ":\n";
		}
		cout << i.getTime() << " - " << i.getModality() << "\nTeacher: "
				<< i.getTeacher()->getName() << endl;

	}
	return CONTINUE;
}

/* ATTEND LESSON MENU */

AttendLesson::AttendLesson(Pool & pool) :
		pool(pool) {

}

MenuResult AttendLesson::handle() {
	while(true){
		try{
			vector<Lesson> lessons = pool.getLessons(getCurrentDate(),getCurrentTime());
			int choice;
			unsigned int customerID;
			cout << "\nInsert customer's ID: ";
			cin >> customerID;
			Customer * c = pool.getCustomer(customerID);
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
			ValidInputInt(choice, 0, lessons.size(), "Choose one class to attend today");
			if (choice == 0) {
				return CONTINUE;
			}

			pool.attendLesson(lessons[0], c, getCurrentDate());
			pool.write();
			return CONTINUE;
		}catch(NonExistentCustomerID &x){
			cout << "There's no Customer with the ID " << x.ID << endl;
		}
	}
}

/* ADD LESSON MENU */

AddLesson::AddLesson(Pool & pool) :
		pool(pool) {
}

MenuResult AddLesson::handle() {
	int modalityOpt;
	Modality modality;

	cout << endl;
	DayOfWeek weekday = ValidDayOfWeek("Insert one of the possible days of the week:\n Monday\n Tuesday\n Wednesday\n Thursday\n Friday\n Saturday\n Sunday\n\n");

	cout << endl;
	Time time = ValidTime("Insert lesson's time (ex. 18 : 30)");

	ValidInputInt(modalityOpt, 0, 5, "\n\n0 - HydroGym\n1 - Zumba\n2 - AquaticPolo\n3 - ArtisticSwimming\n4 - CompetitiveSwimming\n5 - Learning\n Choose one Modality");
	modality = static_cast<Modality>(modalityOpt);
	LessonTime lessonTime;
	lessonTime.first = weekday;
	lessonTime.second = time;
	Lesson l(lessonTime, modality);
	pool.addLesson(l); //criar excepção de já existir uma aula a esta hora
	pool.write();
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

	ValidInputInt(choice, 0, indice, "Choose lesson to be deleted");
	if (choice == 0) {
		return CONTINUE;
	}
	pool.removeLesson(choice);
	pool.write();
	return CONTINUE;
}

/* VIEW TEACHER GIVEN LESSON */

ViewTeacherGivenLessons::ViewTeacherGivenLessons(Pool & pool) :
		pool(pool) {
}

MenuResult ViewTeacherGivenLessons::handle() {
	while(true){
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
				cout << i->getDate() << " - " << i->getLesson().getTime() << "\n"
						<< i->getLesson().getModality() << "\n"
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
	unsigned int ID;
	unsigned int duration = 0;
	bool existe = false;
	cout << "\nInsert customer's ID: ";
	cin >> ID;
	for(Customer * x : pool.getCustomers()){
		if(x->getID() == ID){
			existe = true;
			break;
		}
	}
	if(!existe){
		cout << "There's no customer with that ID.\n\n";
		return CONTINUE;
	}

	while (true) {
		cout << "\nInsert pretended duration: ";
		cin >> duration;
		if (duration > 120 && duration < 0) {
			cout << "\nInvalid duration (can't surpass 120 minutes)\n";
			continue;
		}
		break;
	}
	pool.addFreeSwim(pool.getCustomer(ID), getCurrentDate(), getCurrentTime(),
			duration);
	pool.write();
	return CONTINUE;
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
		cout << "ID: " << c->getID() << "\nName: " << c->getName()
				<< "\nBirthdate: " << c->getBirthDate() << "\nPool uses: "
				<< c->getPoolUses().size() << "\nCost: "
				<< c->getMonthCost(getCurrentDate().getMonth(),
						getCurrentDate().getYear()) << endl;
	}
	return CONTINUE;
}

/* VIEW CUSTOMERS INFORMATION */

ViewCustomersInformation::ViewCustomersInformation(Pool & pool) :
		pool(pool) {
}

MenuResult ViewCustomersInformation::handle() {
	while(true){
		try{
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
		}catch(NonExistentCustomerID &x){
			cout << "There's no such customer with ID " << x.ID;
		}
	}
}

/* VIEW CUSTOMER USES MENU */

ViewCustomerUses::ViewCustomerUses(Pool & pool) :
		pool(pool) {
}

MenuResult ViewCustomerUses::handle() {
	while(true){
		try{
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
						<< "\nDuration: " << p->getDuration() << " minutes\nCost: "
						<< p->getCost() << endl;
			}
			return CONTINUE;

		}catch(NonExistentCustomerID &x){
			cout << "There's no such customer with ID " << x.ID;
		}
	}

}

/* VIEW TEACHER INFORMATION */

ViewTeacherInformation::ViewTeacherInformation(Pool & pool) :
		pool(pool) {
}

MenuResult ViewTeacherInformation::handle() {
	while(true){
		try{
			unsigned int ID;
			cout << "\nInsert teacher's ID: ";
			cin >> ID;
			Teacher * t = pool.getTeacher(ID);
			cout << "\nID: " << t->getID() << "\nName: " << t->getName()
					<< "\nBirthdate: " << t->getBirthDate() << "\nAssigned lessons: "
					<< pool.getLessons(t->getID()).size() << "\nGiven lessons: "
					<< pool.getGivenLessons(t->getID()).size() << endl << endl;
			return CONTINUE;
		}catch(NonExistentTeacherID &x){
			cout << "There's no such teacher with ID " << x.ID;
		}
	}
}

