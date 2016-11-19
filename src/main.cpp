#include <string>
#include <utility>
#include <vector>

#include "Date.h"
#include "Lesson.h"
#include "Menu.h"
#include "Person.h"
#include "Pool.h"
#include "PoolMenu.h"

int main() {

	vector<string> fileNames;

	fileNames.push_back("poolinfo.txt");
	fileNames.push_back("customers.txt");
	fileNames.push_back("teachers.txt");
	fileNames.push_back("schedule.txt");
	fileNames.push_back("givenlessons.txt");

	Pool pool;

	pool.setFileNames(fileNames);

	pool.load();

	/*Teacher * teacher = new Teacher("Mariana Santos", Date(20, 04, 1980));
	pool.addTeacher(teacher);
	Lesson lesson(LessonTime(MON, Time(10, 0)), HydroGym);
	lesson.setTeacher(teacher);
	pool.addLesson(lesson);
	Customer * c = new Customer("Jo�o Silva", Date(10, 12, 2005));
	pool.addCustomer(c);
	pool.attendLesson(lesson, c, Date(14, 11, 2016));
	pool.attendLesson(lesson, pool.getCustomer(1), Date(14, 11, 2016));
	pool.addFreeSwim(pool.getCustomer(3), Date(14, 11, 2016), Time(10, 10), 30);
	pool.write();*/

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

	PoolMenu menu(pool),

	manage(pool),

	viewInfo(pool), viewAttendance(pool),

	manageCustomers(pool), manageTeachers(pool), manageSchedule(pool),

	usePool(pool),

	viewTeacherInfo(pool);

	ViewSchedule viewSchedule(pool);

	AddCustomer addCustomer(pool);
	RemoveCustomer removeCustomer(pool);

	AddTeacher addTeacher(pool);
	RemoveTeacher removeTeacher(pool);

	AddLesson addLesson(pool);
	RemoveLesson removeLesson(pool);

	PoolMenu freeSwimming(pool);
	AttendLesson attendLesson(pool);

	CurrentOccupation occupation(pool);

	CustomerAttendanceAll attendanceall(pool);
	CustomerAttendanceName attendancename(pool);
	CustomerAttendanceID attendanceid(pool);

	PoolMenu viewTeachers(pool);
	PoolMenu viewCustomers(pool);

	ViewTeacherSchedule viewTeacherSchedule(pool);
	ViewTeacherGivenLessons viewTeacherGivenLessons(pool);

	/* MAIN MENU */
	menu.entries.push_back(MenuEntry("Exit", Menu::exitHandler));
	menu.entries.push_back(MenuEntry("Manage", manage));
	menu.entries.push_back(MenuEntry("View information", viewInfo));

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

	/*---------------------------*/

	viewAttendance.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewAttendance.entries.push_back(
			MenuEntry("All customers' attendance", attendanceall));
	viewAttendance.entries.push_back(
			MenuEntry("Attendances of a specific customer (by name)",
					attendancename));
	viewAttendance.entries.push_back(
			MenuEntry("Attendances of a specific customer (by ID)",
					attendanceid));

	/*-----------------------------*/

	viewInfo.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewInfo.entries.push_back(MenuEntry("View attendances", viewAttendance));
	viewInfo.entries.push_back(
			MenuEntry("View current occupation", occupation));
	viewInfo.entries.push_back(MenuEntry("View schedule", viewSchedule));
	viewInfo.entries.push_back(MenuEntry("View teachers", viewTeachers));
	viewInfo.entries.push_back(MenuEntry("View customers", viewCustomers));
	viewInfo.entries.push_back(MenuEntry("View teacher info", viewTeacherInfo));

	viewTeacherInfo.entries.push_back(MenuEntry("Back", Menu::exitHandler));
	viewTeacherInfo.entries.push_back(MenuEntry("View teacher's schedule", viewTeacherSchedule));
	viewTeacherInfo.entries.push_back(MenuEntry("View teacher's given lessons", viewTeacherGivenLessons));

	menu.handle();

	return 0;
}
