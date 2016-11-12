#ifndef SRC_POOLMENU_H_
#define SRC_POOLMENU_H_

#include "Menu.h"
#include "Pool.h"

class PoolMenu : public Menu {
public:
	PoolMenu(Pool & pool);

private:
	Pool & pool;
};

class AddCustomer : public MenuHandler {
public:
	AddCustomer(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};



#endif /* SRC_POOLMENU_H_ */
