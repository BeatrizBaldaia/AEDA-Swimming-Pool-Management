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
#include "Exceptions.h"


/* HASH TABLE */
struct hCustomer {

	int operator()(Customer* c1) const{
		int result;
		string s = c1->getName();
		for(int i; i < s.size(); i++){
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


/**
 * \brief Classe que guarda a informação referente a uma campanha promocional.
 * Guarda a data de inicio e de fim data campanha, bem como o desconto. Contem funções que retornam os membros-dado e um operador de menor para fazer sort.
 */
class PromotionalCampaign {
private:
	/**
	 * Data de inicio.
	 */
	Date beginDate;
	/**
	 * Data de fim.
	 */
	Date endDate;
	/**
	 * Desconto na campanha
	 */
	double discount;
public:
	/**
	 * Construtor da classe PromotionalCampaign.
	 * @param beginDate
	 * @param endDate
	 * @param discount
	 */
	PromotionalCampaign(Date beginDate, Date endDate, double discount);
	/**
	 * Retorna a data de ínicio.
	 * @return
	 */
	Date getBeginDate() const;
	/**
	 * Retorna data de fim.
	 * @return
	 */
	Date getEndDate() const;
	/**
	 * Retorna o desconto da campanha.
	 * @return
	 */
	double getDiscount() const;
	/**
	 * Operador de menor. Uma campanha é menor que a outra se for mais recente.
	 * @param promCamp
	 * @return
	 */
	bool operator<(PromotionalCampaign & promCamp) const;
};

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
	void addModality(Modality modality);
	bool haveModality(Modality modality);
	bool operator<(OtherPool & oP2) const;
};

class ptrOtherPool{
private:
	OtherPool * ptr;
public:
	ptrOtherPool(OtherPool * p);
	string getName() const;
	double getDistance() const;
	vector<Modality> getModalityLessons() const;
	void addModality(Modality modality);
	bool haveModality(Modality modality);
	bool operator<(ptrOtherPool oP2) const;
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
	vector<Lesson> getLessonByModality(Modality modality)const;
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
	void addCampaign(PromotionalCampaign campaign);
	PromotionalCampaign getCurrentPromotion() const;

	vector<PromotionalCampaign> getPromotionalCampaign() const;
	void addPromotionalCampaign(PromotionalCampaign campaign);///retorna exceção se houver algum overlap de campanhas promocionais

	bool isCustomerInactive(Customer * c);///ver se cliente e inativo
	void activateCustomer(Customer * c);///torna cliente inativo em ativo
	hashCustomer getInactiveCustomer() const;
	void eraseInactive(Customer * customer);
	void insertInactive(Customer * customer);

	vector<Item> getProviderItems();

	priority_queue<ptrOtherPool> getOtherPools() const;
	void addOtherPool(ptrOtherPool oP);///adiciona a fila de prioridade uma piscina das redondezas
	void addModalityToPool(string name, vector<Modality> vM); ///adiciona modalidade a uma piscina das redondezas (de nome name)
	ptrOtherPool getNextPool(Modality modality);

	void distributeLessons();

	void setFileNames(vector<string> v);
	void addFreeUse(PoolUse * freeUse);

	void attendLesson(Lesson lesson, Customer * customer, Date date, double discount);
	void addFreeSwim(Customer * customer, Date date, Time time,unsigned int duration, double discount);

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
	void loadOtherPools();
	void loadPromotions();

	void write();///escreve para os ficheiros de texto
	void writePoolInfo();
	void writeCustomers();
	void writeTeachers();
	void writeSchedule();
	void writeGivenLessons();
	void writeShop();
	void writeOtherPools();
	void writePromotions();
private:
	vector<Customer *> customers;
	vector<Teacher *> teachers; ///Quando Pool é criado os vetores devem ser logo ordenados usando as funções sort;
	vector<Lesson> schedule;
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
	// 7 otherpools
	// 8 promotions

	Shop * shop;///apontador para a loja da piscina
	hashCustomer inactiveCustomers;///tabela de dispersao com os clientes inativos
	priority_queue<ptrOtherPool> otherPools;///fila de prioridade com as piscinas nas redondezas

	string name;///nome da nossa piscina
	unsigned int maxCustomers;///numero maximo de utentes que podem estar na piscina

	vector<PromotionalCampaign> promotions;
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

class OverlapingCampaign {
public:
	OverlapingCampaign();
};

class CustomerAlreadyAttendedLesson {

};


#else

class Pool;

#endif
