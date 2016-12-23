#ifndef _POOL_H_
#define _POOL_H_

#include <string>
#include <vector>
#include <tr1/unordered_set>

#include "Date.h"
#include "Lesson.h"
#include "Person.h"
#include "PoolUse.h"
#include "Shop.h"


/* HASH TABLE */
struct hCustomer {

	int operator()(Customer* c1) const{
		int result;
		for(int i; i < c1->getName().size(); i++){
			result+= c1->getName()[i]*37;
		}
		return result;
	}

	bool operator()(Customer* c1, Customer* c2) const {
		return (c1->getName() == c2->getName()) && (c1->getID() == c2->getID());
	}
};

typedef tr1::unordered_set<Customer *, hCustomer, hCustomer> hashCustomer;

///////////////////////////////////

class OtherPool{
private:
	string name;///nome da piscina
	double distance; ///distancia da piscina secundaria em relacao a nossa piscina
	vector<Modality> modalityLessons;
public:
	OtherPool(string name, double distance);
	OtherPool(string name, double distance, vector<Modality> lessons);
	string getName() const;
	double getDistance() const;
	vector<Modality> getModalityLessons() const;
	bool haveModality(Modality modality);
	bool operator<(OtherPool & oP2)const;
};

class Pool {
public:
	static int inactivityPeriod; /// days to be considered inactive
	unsigned int getMaxCustomers() const;
	Lesson getNextLesson(DayOfWeek day, Time time, bool & currentlesson) const;
	vector<Lesson> getLessons(unsigned int ID); /// retorna vetor com as aulas dadas por um professor
	vector<Lesson> getLessons(Date date, Time time);
	vector<GivenLesson *> getGivenLessons(); /// dá o vetor givenLessons
	vector<GivenLesson *> getGivenLessons(unsigned int ID);
	GivenLesson * getGivenLesson(Lesson lesson, Date date); /// dá GivenLesson que tem uma certa Lesson e ocorreu num certo Date
	void addLesson(Lesson lesson); /// adiciona aula ao vetor schedule e atribui a mesma um professor
	unsigned int CustomersInLesson(GivenLesson lesson); /// dá o número de clientes numa certa aula
	unsigned int CustomersFreeUse(Date date, Time time); /// dá o número de clientes a usar a piscina numa certa data e tempo
	Lesson getLesson(DayOfWeek day, Time time) const; ///usa exceção: try{...} catch(InvalidLesson x){cout << "There's no lesson on " << x.day << " at " << x.time;
	vector<Customer *> getCustomers(); /// retorna vetor customers
	Customer * getCustomer(string name); ///usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer named " << x.name;
	Customer * getCustomer(unsigned int ID); ///usa exceção: try{...} catch(NonExistentCustomer x){cout << "There's no such customer with ID " << x.ID;
	void setName(string name); ///dá nome a piscina
	void setMaxCustomers(unsigned int n); /// define o numero maximo de pessoas na piscina
	string getName() const; ///dá nome da piscina
	vector<Lesson> getSchedule() const;
	vector<Teacher *> getTeachers() const;

	bool isCustomerInactive(Customer * c);///ver se cliente e inativo
	void activateCustomer(Customer * c);///torna cliente inativo em ativo
	hashCustomer getInactiveCustomer();

	vector<Item> getProviderItems();

	void distributeLessons();

	void setFileNames(vector<string> v);
	void addFreeUse(PoolUse * freeUse);

	void attendLesson(Lesson lesson, Customer * customer, Date date);
	void addFreeSwim(Customer * customer, Date date, Time time,
			unsigned int duration);

	void removeCustomer(unsigned int ID);
	void removeTeacher(unsigned int ID);
	void removeLesson(unsigned int position);

	void addCustomer(Customer * c);
	void addTeacher(Teacher * t);
	Teacher * getTeacher(unsigned int ID);

	Shop * getShop() const;

	void load();///le o que está nos ficheiros de texto
	void loadPoolInfo();
	void loadCustomers();
	void loadTeachers();
	void loadSchedule();
	void loadGivenLessons();
	void testInactiveCustomers();
	void loadShop();

	void write();///escreve para os ficheiros de texto
	void writePoolInfo();
	void writeCustomers();
	void writeTeachers();
	void writeSchedule();
	void writeGivenLessons();
	void writeShop();
private:
	vector<Customer *> customers;

	vector<Teacher *> teachers; ///Quando Pool é criado os vetores devem ser logo ordenados usando as funções sort;
	vector<Lesson> schedule; ///Se o número de elementos do vetor for inferior ou igual a 20 usar INSERTION SORT senão usar QUICK SORT
	vector<GivenLesson *> givenLessons;
	vector<PoolUse *> freeUses; ///sempre que alguem que usar a piscina em modo livre, o uso é guardado neste vetor; usar freeuses.insert(freeuses.begin(), PoolUse * objeto) e não freeuses.push_back(...) para termos sempre os objetos mais recentes no inicio

	vector<string> fileNames;
	// 0 poolinfo
	// 1 customers
	// 2 teachers
	// 3 schedule
	// 4 givenlessons
	// 5 shop
	// 6 provider

	Shop * shop;
	hashCustomer inactiveCustomers;
	priority_queue<OtherPool> otherPools;
	string name;
	unsigned int maxCustomers;
};

class NoMoreLessonsInDay {
public:
	NoMoreLessonsInDay();
};

class InvalidLesson {
public:
	InvalidLesson(DayOfWeek day, Time &t);
	DayOfWeek day;
	Time time;
};

class NonExistentCustomerName {
public:
	NonExistentCustomerName(string name);
	string name;
};

class NonExistentCustomerID {
public:
	NonExistentCustomerID(unsigned int ID);
	unsigned int ID;
};

class NonExistentTeacherID {
public:
	NonExistentTeacherID(unsigned int ID);
	unsigned int ID;
};

class NotSameDayAsDate {
public:
	NotSameDayAsDate();
};

class NonExistentGivenLesson {
public:
	NonExistentGivenLesson(Lesson lesson, Date date);
	Lesson lesson;
	Date date;
};

class CustomerAlreadyAttendedLesson {

};

#else

class Pool;

#endif
