#ifndef SRC_POOLMENU_H_
#define SRC_POOLMENU_H_

#include "Menu.h"

class Pool;

/* POOL MENU */

class PoolMenu: public Menu {
public:
	PoolMenu(Pool & pool);

private:
	Pool & pool;
};

/* ADD CUSTOMER MENU */

class AddCustomer: public MenuHandler {
public:
	AddCustomer(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* REMOVE CUSTOMER MENU */

class RemoveCustomer: public MenuHandler {
public:
	RemoveCustomer(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* ADD TEACHER MENU */

class AddTeacher: public MenuHandler {
public:
	AddTeacher(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};


/* CURRENT OCCUPATION MENU */

class CurrentOccupation: public MenuHandler {
public:
	CurrentOccupation(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* CUSTOMERS  ATTENDANCE */

class CustomerAttendanceAll: public MenuHandler {
public:
	CustomerAttendanceAll(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class CustomerAttendanceName: public MenuHandler {
public:
	CustomerAttendanceName(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class CustomerAttendanceID: public MenuHandler {
public:
	CustomerAttendanceID(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class CustomerMakeCurrentBill: public MenuHandler {
public:
	CustomerMakeCurrentBill(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class CustomerMakeBill: public MenuHandler {
public:
	CustomerMakeBill(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};
#endif /* SRC_POOLMENU_H_ */
