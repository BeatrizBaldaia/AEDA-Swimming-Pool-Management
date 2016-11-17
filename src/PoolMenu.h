#ifndef SRC_POOLMENU_H_
#define SRC_POOLMENU_H_

#include "Menu.h"
#include "Pool.h"

/* POOL MENU */

class PoolMenu : public Menu {
public:
	PoolMenu(Pool & pool);

private:
	Pool & pool;
};

/* ADD CUSTOMER MENU */

class AddCustomer : public MenuHandler {
public:
	AddCustomer(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* CURRENT OCCUPATION MENU */

class CurrentOccupation : public MenuHandler{
public:
	CurrentOccupation(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* CUSTOMERS  ATTENDANCE */

class CustomerAttendanceAll : public MenuHandler{
public:
	CustomerAttendanceAll(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class CustomerAttendanceName : public MenuHandler{
public:
	CustomerAttendanceName(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class CustomerAttendanceID : public MenuHandler{
public:
	CustomerAttendanceID(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};
#endif /* SRC_POOLMENU_H_ */
