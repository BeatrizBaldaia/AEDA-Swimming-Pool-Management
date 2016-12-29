#ifndef SRC_POOLMENU_H_
#define SRC_POOLMENU_H_

#include "Menu.h"
#include "Date.h"
#include "Lesson.h"
#include "Person.h"
#include "Pool.h"
#include "PoolUse.h"
#include "Utilities.h"
#include "EXceptions.h"

enum OrderBy {
ID, NAME, NUMUSES, GIVENLESSONS, ASSLESSONS
};

class Pool;

/* POOL MENU */
/**
 * cria menus (é derivada da class Menu)
 */
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

/* REMOVE TEACHER MENU */

class RemoveTeacher: public MenuHandler {
public:
	RemoveTeacher(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* ATTEND LESSON */
/**
 * \brief associa um cliente a uma aula dada
 *
 * Prioridade daqueles que vão a uma aula está subjacente à maneira de como o cliente se inscreve na aula
 * Uma pessoa que use o modo livre vai frequentar a piscina na hora atual.
 * Uma pessoa que queira frequentar a aula, terá acesso a uma lista de aulas desse dia para escolher, sendo que marcará com antecedência, e impedirá
 * aquele que irá usar o modo livre de usar a piscina, no caso de esta estar cheia.
 */
class AttendLesson: public MenuHandler {
public:
	AttendLesson(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class AttendToSpecificModality: public MenuHandler{
public:
	AttendToSpecificModality(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* ADD LESSON */

class AddLesson: public MenuHandler {
public:
	AddLesson(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/* REMOVE LESSON */

class RemoveLesson: public MenuHandler {
public:
	RemoveLesson(Pool & pool);
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
/**
 * mostra todos os usos de um cliente
 */
class ViewAttendance: public MenuHandler {
public:
	ViewAttendance(Pool& pool);
	MenuResult handle();
private:
	Pool& pool;
};

/*-----------------------*/
/**
 * cria ficheiros de texto
 */
class CustomerMakeCurrentBill: public MenuHandler {
public:
	CustomerMakeCurrentBill(Pool& pool);
	MenuResult handle();
private:
	Pool& pool;
};
/**
 * cria ficheiros de texto
 */
class CustomerMakeBill: public MenuHandler {
public:
	CustomerMakeBill(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};
/**
 * ve aulas atribuidas a um professor
 */
class ViewTeacherSchedule: public MenuHandler {
public:
	ViewTeacherSchedule(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};
/**
 * ve aulas já dadas por um professor
 */
class ViewTeacherGivenLessons: public MenuHandler {
public:
	ViewTeacherGivenLessons(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class ViewSchedule: public MenuHandler {
public:
	ViewSchedule(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class ViewTeachers: public MenuHandler {
public:
	ViewTeachers(Pool & pool, OrderBy orderBy);
	MenuResult handle();
private:
	Pool & pool;
	OrderBy orderBy;
};

class ViewCustomers: public MenuHandler {
public:
	ViewCustomers(Pool & pool, OrderBy orderBy);
	MenuResult handle();
private:
	Pool & pool;
	OrderBy orderBy;
};
/**
 * adiciona uma uso livre a um cliente
 */
class FreeSwimming: public MenuHandler {
public:
	FreeSwimming(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class ViewCustomersInformation: public MenuHandler {
public:
	ViewCustomersInformation(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};
/**
 * mostra todos os usos de piscina livre de um cliente
 */
class ViewCustomerUses: public MenuHandler {
public:
	ViewCustomerUses(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class ViewTeacherInformation: public MenuHandler {
public:
	ViewTeacherInformation(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/*
 * trata da venda de produtos aos utentes e a compra de produtos ao fornecedor
 * */

class ShopSellItems: public MenuHandler{///vender produto aos utentes
public:
	ShopSellItems(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class ShopBuyItems: public MenuHandler{
public:
	ShopBuyItems(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class ViewShopInfo: public MenuHandler{
public:
	ViewShopInfo(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/*
 * ver informacoes e alterar iformacoes das piscinas proximas da nossa piscina
 * */

class ViewOtherPools: public MenuHandler{
public:
	ViewOtherPools(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class AddOtherPool: public MenuHandler{
public:
	AddOtherPool(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class AddModalityToPool: public MenuHandler{
public:
	AddModalityToPool(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

/*
 * Promotional Campaign Manage
 */

class ViewCurrentCampaign: public MenuHandler{
public:
	ViewCurrentCampaign(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class AddCampaign: public MenuHandler{
public:
	AddCampaign(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};

class UpdateCustomersInfo: public MenuHandler{
public:
	UpdateCustomersInfo(Pool & pool);
	MenuResult handle();
private:
	Pool & pool;
};
#endif /* SRC_POOLMENU_H_ */

