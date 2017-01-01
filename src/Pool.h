#ifndef _POOL_H_
#define _POOL_H_

#include <queue>
#include <string>
#include <tr1/unordered_set>
#include <vector>

#include "Date.h"
#include "Lesson.h"
#include "Person.h"
#include "PoolUse.h"
#include "Shop.h"

/* HASH TABLE */
struct hCustomer {

	int operator()(Customer* c1) const {
		int result;
		string s = c1->getName();
		for (int i; i < s.size(); i++) {
			result += c1->getName()[i] * 37;
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
 * \brief Classe que guarda a informa��o referente a uma campanha promocional.
 * Guarda a data de inicio e de fim data campanha, bem como o desconto. Contem fun��es que retornam os membros-dado e um operador de menor para fazer sort.
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
	 * Retorna a data de �nicio.
	 * @return Data
	 */
	Date getBeginDate() const;
	/**
	 * Retorna data de fim.
	 * @return Data
	 */
	Date getEndDate() const;
	/**
	 * Retorna o desconto da campanha.
	 * @return double
	 */
	double getDiscount() const;
	/**
	 * Operador de menor. Uma campanha � menor que a outra se for mais recente.
	 * @param promCamp
	 * @return bool
	 */
	bool operator<(PromotionalCampaign & promCamp) const;
};

/**
 * \brief Classe que contem a informa��o de uma piscina que n�o a nossa.
 * Contem a dist�ncia � nossa piscina, o nome da mesma e as modalidades que tem dispon�vel.
 */
class OtherPool {
private:
	/**
	 * Nome da piscina.
	 */
	string name;
	/**
	 * Distancia � nossa piscina.
	 */
	double distance;
	/**
	 * Vetor de modalidades dispon�veis na piscina.
	 */
	vector<Modality> modalityLessons;
public:
	/**
	 * Construtor da classe OtherPool sem modalidades.
	 * @param name
	 * @param distance
	 */
	OtherPool(string name, double distance);
	/**
	 * Construtor da classe OtherPool com modalidades.
	 * @param name
	 * @param distance
	 * @param lessons
	 */
	OtherPool(string name, double distance, vector<Modality> lessons);
	/**
	 * Retorna o nome da piscina.
	 * @return string
	 */
	string getName() const;
	/**
	 * Retorna a dist�ncia � nossa piscina.
	 * @return double
	 */
	double getDistance() const;
	/**
	 * Retorna as modalidades de que a piscina disp�e.
	 * @return vector<Modality>
	 */
	vector<Modality> getModalityLessons() const;
	/**
	 * Adiciona uma modalidade � piscina.
	 * @param modality
	 */
	void addModality(Modality modality);
	/**
	 * Retorna verdadeiro se a piscina tem a modalidade dispon�vel, caso contr�rio retorna falso.
	 * @param modality
	 * @return bool
	 */
	bool haveModality(Modality modality);
	/**
	 * Operador de menor para a lista de prioridade. A piscina � "maior" se a dist�ncia a nossa for menor (em caso de empate, � usada a ordem alfab�tica).
	 * @param oP2
	 * @return bool
	 */
	bool operator<(OtherPool & oP2) const;
};

/**
 * \brief Classe que representa as piscinas nas redondezas (proximas da nossa piscina)
 */
class ptrOtherPool {
private:
	/**
	 * \brief apontador para um objeto da classe OtherPool
	 */
	OtherPool * ptr;
public:
	/**
	 * Construtor da classe ptrOtherPool sem modalidades.
	 * @param *p (apontador para objeto da classe OtherPool)
	 */
	ptrOtherPool(OtherPool * p);
	/**
	 * Retorna o nome da OtherPool
	 * @return string
	 */
	string getName() const;
	/**
	 * Retorna a distancia a que a OtherPool se encontra de nos
	 * @return double
	 */
	double getDistance() const;
	/**
	 * Retorna as modalidades dadas pela OtherPool
	 * @return vector<Modality>
	 */
	vector<Modality> getModalityLessons() const;
	/**
	 * Adiciona uma modalidade a OtherPool
	 * @param modality
	 */
	void addModality(Modality modality);
	/**
	 * Retorna true se a modalidade (parametro modality) for dada na OtherPool
	 * @param modality
	 * @return bool
	 */
	bool haveModality(Modality modality);
	/**
	 * Operador de menor. E menor a piscina mais distante. Piscinas a mesma distancia sao comparadas pelo seu nome
	 * @param ptrOtherPool oP2
	 * @return bool
	 */
	bool operator<(ptrOtherPool oP2) const;
};

/**
 * \brief Mega classe que guarda toda a informa��o da piscina.
 * Contem um vetor de clientes, de professores, de aulas, de aulas dadas, de usos livres da piscina, e de promo��es.
 * Contem tamb�m uma lista de prioridade com outras piscinas (ordenadas por proximidade), um nome (string), o n�mero m�ximo de clientes, um apontador para uma loja, e uma tabela de dispers�o com clientes inativos.
 * � guardado na Pool o nome do ficheiros de texto a utilizar pelo programa.
 */
class Pool {
public:
	static int inactivityPeriod; ///Dias necess�rios para considerar um cliente inativo.
	/**
	 * Retorna o n�mero m�ximo de clientes da piscina
	 * @return unsigned int
	 */
	unsigned int getMaxCustomers() const;
	/**
	 * Retorna a pr�xima aula no hor�rio (em rela��o ao tempo atual), lan�a a exce��o NoMoreLessonsInDay se n�o existir nenhuma.
	 * @param day
	 * @param time
	 * @param currentlesson
	 * @return Lesson
	 */
	Lesson getNextLesson(DayOfWeek day, Time time, bool & currentlesson) const;
	/**
	 * Retorna vetor com as aulas marcadas para um professor.
	 * @param ID
	 * @return vector<Lesson>
	 */
	vector<Lesson> getLessons(unsigned int ID);
	/**
	 * Retorna as aulas marcadas para um dia.
	 * @param date
	 * @param time
	 * @return vector<Lesson>
	 */
	vector<Lesson> getLessons(Date date, Time time);
	/**
	 * Retorna todas as aulas dadas pela piscina.
	 * @return vector<GivenLesson *>
	 */
	vector<GivenLesson *> getGivenLessons();
	/**
	 * Retorna todas as aulas dadas por um professor.
	 * @param ID
	 * @return vector<GivenLesson *>
	 */
	vector<GivenLesson *> getGivenLessons(unsigned int ID);
	/**
	 * Retorna as aulas do hor�rio de uma determinada modalidade.
	 * @param modality
	 * @return vector<Lesson>
	 */
	vector<Lesson> getLessonByModality(Modality modality) const;
	/**
	 * \brief Retorna uma aula dada a partir de uma data e de uma aula marcada.
	 * Se o dia da semana da aula marcada e da data n�o corresponderem, lan�a a exce��o NotSameDayAsDate.
	 * Se a aula marcada n�o for uma aula dada (n�o apareceu ningu�m), retorna a exce��o NonExistentGivenLesson.
	 * @param lesson
	 * @param date
	 * @return GivenLesson *
	 */
	GivenLesson * getGivenLesson(Lesson lesson, Date date);
	/**
	 * Adiciona a aula marcada ao hor�rio, e redistribui os professores pelas aulas.
	 * @param lesson
	 */
	void addLesson(Lesson lesson);
	/**
	 * Retorna o n�mero de clientes numa aula dada ou a decorrer.
	 * @param lesson
	 * @return unsigned int
	 */
	unsigned int CustomersInLesson(GivenLesson lesson);
	/**
	 * Retorna o n�mero de clientes em uso livre numa determinada hora num determinado dia.
	 * @param date
	 * @param time
	 * @return unsigned int
	 */
	unsigned int CustomersFreeUse(Date date, Time time);
	/**
	 * \brief Retorna uma aula marcada num deteminado dia da semana numa determinada hora.
	 * Se n�o existir nenhuma aula marcada nesse instante, lan�a a exce��o InvalidLesson.
	 * @param day
	 * @param time
	 * @return Lesson
	 */
	Lesson getLesson(DayOfWeek day, Time time) const;
	/**
	 * Retorna todos os clientes da piscina.
	 * @return vector<Customer *>
	 */
	vector<Customer *> getCustomers();
	/**
	 * \brief Retorna o cliente com um determinado nome.
	 * Se n�o houver nenhum cliente com esse nome lan�a a exce��o NonExistentCustomerName.
	 * @param name
	 * @return Customer *
	 */
	Customer * getCustomer(string name);
	/**
	 * \brief Retorna o cliente com um determinado ID.
	 * Se n�o existir nenhum cliente com esse ID lan�a a exce��o NonExistentCustomerID.
	 * @param ID
	 * @return Customer *
	 */
	Customer * getCustomer(unsigned int ID);
	/**
	 * Altera o nome da piscina.
	 * @param name
	 */
	void setName(string name);
	/**
	 * Altera o n�mero m�ximo de clientes permitidos na piscina.
	 * @param n
	 */
	void setMaxCustomers(unsigned int n);
	/**
	 * Retorna o nome da piscina.
	 * @return string
	 */
	string getName() const;
	/**
	 * Retorna o hor�rio da piscina.
	 * @return vector<Lesson>
	 */
	vector<Lesson> getSchedule() const;
	/**
	 * Retorna todos os professores da piscina.
	 * @return vector<Teacher *>
	 */
	vector<Teacher *> getTeachers() const;
	void addCampaign(PromotionalCampaign campaign);
	/**
	 * \brief Retorna a campanha promocional em vigor no momento.
	 * Se n�o existir nenhuma campanha em vigor lan�a a exce��o NoCurrentCampaign.
	 * @return
	 */
	PromotionalCampaign getCurrentPromotion() const;
	/**
	 * Retorna todas as campanhas promocionais da piscina.
	 * @return vector<PromotionalCampaign>
	 */
	vector<PromotionalCampaign> getPromotionalCampaign() const;
	/**
	 * \brief Adiciona uma campanha promocional � piscina.
	 * Se esta campanha se sobrepor a outra, lan�a a exce��o OverlapingCampaign.
	 * @param campaign
	 */
	void addPromotionalCampaign(PromotionalCampaign campaign);
	/**
	 * Retorna o estado do cliente. Retorna verdade se ele estiver inativo, e falso se estiver ativo.
	 * @param c
	 * @return bool
	 */
	bool isCustomerInactive(Customer * c);
	/**
	 * Torna um cliente inativo em ativo
	 * @param c
	 */
	void activateCustomer(Customer * c);
	/**
	 * Retorna um cliente inativo.
	 * @return hashCustomer
	 */
	hashCustomer getInactiveCustomer() const;
	/**
	 * Elimina um customer inativo.
	 * @param customer
	 */
	void eraseInactive(Customer * customer);
	/**
	 * Torna um cliente ativo em inativo.
	 * @param customer
	 */
	void insertInactive(Customer * customer);
	/**
	 * Retorna os produtos vendidos pelo fornecedor.
	 * @return vector<Item>
	 */
	vector<Item> getProviderItems();
	/**
	 * Retorna a fila de prioridade com as outras piscinas.
	 * @return priority_queue<ptrOtherPool>
	 */
	priority_queue<ptrOtherPool> getOtherPools() const;
	/**
	 * Adiciona uma nova piscina � fila de prioridade.
	 * @param oP
	 */
	void addOtherPool(ptrOtherPool oP);
	/**
	 * Adiciona modalidades a uma piscina das redondezas.
	 * @param name
	 * @param vM
	 */
	void addModalityToPool(string name, vector<Modality> vM); //TODO exce��o de j� existirem modalidades
	/**
	 * \brief Retorna a piscina mais pr�xima com a modalidade requerida.
	 * Se nenhuma piscina tiver a modalidade, lan�a a exce��o NoModality.
	 * @param modality
	 * @return ptrOtherPool
	 */
	ptrOtherPool getNextPool(Modality modality);
	/**
	 * Distribui as aulas marcadas pelos professores da piscina, de forma a ficarem iguais em n�mero de aulas.
	 */
	void distributeLessons();
	/**
	 * Muda o nome dos ficheiros a ler.
	 * @param v
	 */
	void setFileNames(vector<string> v);
	/**
	 * Adiciona um uso � piscina.
	 * @param freeUse
	 */
	void addFreeUse(PoolUse * freeUse);
	/**
	 * \brief Atribui um cliente a um aula.
	 * Se o dia da semana da aula marcada e do dia n�o coincidirem lan�a a exce��o NotSameDayAsDate.
	 * @param lesson
	 * @param customer
	 * @param date
	 * @param discount
	 */
	void attendLesson(Lesson lesson, Customer * customer, Date date,
			double discount);
	/**
	 * Adiciona um uso livre a um cliente (e � piscina).
	 * @param customer
	 * @param date
	 * @param time
	 * @param duration
	 * @param discount
	 */
	void addFreeSwim(Customer * customer, Date date, Time time,
			unsigned int duration, double discount);
	/**
	 * Remove o cliente com determinado ID.
	 * @param ID
	 */
	void removeCustomer(unsigned int ID);
	/**
	 * Remove o professor com determinado ID.
	 * @param ID
	 */
	void removeTeacher(unsigned int ID);
	/**
	 * Remove uma aula do hor�rio de acordo com a sua posi��o no mesmo.
	 * @param position
	 */
	void removeLesson(unsigned int position);
	/**
	 * Adiciona um cliente � piscina.
	 * @param c
	 */
	void addCustomer(Customer * c);
	/**
	 * Adiciona um professor � piscina e redistribui as aulas novamente.
	 * @param t
	 */
	void addTeacher(Teacher * t);
	/**
	 * \brief Retorna o professor com o ID requerido.
	 * Se n�o existir nenhum professor com tal ID, lan�a a exce��o NonExistentTeacherID.
	 * @param ID
	 * @return Teacher *
	 */
	Teacher * getTeacher(unsigned int ID);
	/**
	 * Retorna a loja da piscina.
	 * @return
	 */
	Shop * getShop() const;

	/**
	 * \brief l� todos os ficheiros de texto.
	 * Corre todas as outras fun��es de load.
	 */
	void load();
	/**
	 * L� a informa��o da piscina.
	 */
	void loadPoolInfo();
	/**
	 * L� os clientes do ficheiro de texto.
	 */
	void loadCustomers();
	/**
	 * L� os professores do ficheiro de texto.
	 */
	void loadTeachers();
	/**
	 * L� o hor�rio do ficheiro de texto.
	 */
	void loadSchedule();
	/**
	 * L� as aulas dadas do ficheiro de texto.
	 */
	void loadGivenLessons();
	/**
	 * L� os clientes inativos do ficheiro de texto.
	 */
	void testInactiveCustomers();
	/**
	 * L� a loja do ficheiro de texto.
	 */
	void loadShop();
	/**
	 * L� as outras piscinas do ficheiro de texto.
	 */
	void loadOtherPools();
	/**
	 * L� as promo��es da piscina do ficheiro de texto.
	 */
	void loadPromotions();

	/**
	 * Escreve para os ficheiros de texto
	 */
	void write();
	/**
	 * Escreve a informa��o da piscina para um ficheiro de texto.
	 */
	void writePoolInfo();
	/**
	 * Escreve os clientes para um ficheiro de texto.
	 */
	void writeCustomers();
	/**
	 * Escreve os professores para um ficheiro de texto.
	 */
	void writeTeachers();
	/**
	 * Escreve o hor�rio da piscina para um ficheiro de texto.
	 */
	void writeSchedule();
	/**
	 * Escreve as aulas dadas para um ficheiro de texto.
	 */
	void writeGivenLessons();
	/**
	 * Escreve a loja para um ficheiro de texto.
	 */
	void writeShop();
	/**
	 * Escreve a informa��o das outras piscinas para um ficheiro de texto.
	 */
	void writeOtherPools();
	/**
	 * Escreve as promo��es para um ficheiro de texto.
	 */
	void writePromotions();
private:
	/**
	 * \brief Vetor que guarda a informa��o dos clientes da piscina.
	 * Est� ordenado por ID, mas podemos visualiz�-lo por diferente ordena��o no programa.
	 */
	vector<Customer *> customers;
	/**
	 * \brief Vetor que guarda a informa��o dos clientes da piscina.
	 * Est� ordenado por ID, mas podemos visualiz�-lo por diferente ordena��o no programa.
	 */
	vector<Teacher *> teachers;
	/**
	 * \brief Vetor que guarda o hor�rio.
	 * Est� ordenado por dia da semana e hora.
	 */
	vector<Lesson> schedule;
	/**
	 * Vetor de aulas dadas.
	 */
	vector<GivenLesson *> givenLessons;
	/**
	 * Vetor de usos livres da piscina.
	 */
	vector<PoolUse *> freeUses;
	/**
	 * Vetor com o nome dos ficheiros de texto.
	 */
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

	/**
	 * Loja.
	 */
	Shop * shop;
	/**
	 * Tabela de dispersao com os clientes inativos.
	 */
	hashCustomer inactiveCustomers;
	/**
	 * Fila de prioridade com as piscinas nas redondezas.
	 */
	priority_queue<ptrOtherPool> otherPools;
	/**
	 * Nome da nossa piscina
	 */
	string name;
	/**
	 * N�mero m�ximo de clientes que podem estar presentes na piscina.
	 */
	unsigned int maxCustomers;
	/**
	 * Vetor de campanhas promocionais.
	 */
	vector<PromotionalCampaign> promotions;
};

/**
 * Exce��o que aparece quando n�o h� mais aulas num certo dia.
 */
class NoMoreLessonsInDay {
public:
	/**
	 * Construtor da classe NoMoreLessonsInDay.
	 */
	NoMoreLessonsInDay();
};

/**
 * Exce��o que aparece quando invocamos a fun��o getLesson(Date,Time) e n�o existe nenhuma aula.
 */
class InvalidLesson {
public:
	/**
	 * Construtor da classe NoMoreLessonsInDay.
	 * @param day
	 * @param t
	 */
	InvalidLesson(DayOfWeek day, Time &t);
	DayOfWeek day;
	Time time;
};

/**
 * Exce��o que aparece quando queremos um cliente a partir do nome, e n�o existe nenhum cliente com esse nome.
 */
class NonExistentCustomerName {
public:
	/**
	 * Construtor da classe NonExistentCustomerName.
	 * @param name
	 */
	NonExistentCustomerName(string name);
	string name;
};

/**
 * Exce��o que aparece quando queremos um cliente a partir do ID, e n�o existe nenhum cliente com esse ID.
 */
class NonExistentCustomerID {
public:
	/**
	 *  Construtor da classe NonExistentCustomerID.
	 * @param ID
	 */
	NonExistentCustomerID(unsigned int ID);
	unsigned int ID;
};

/**
 * Exce��o que aparece quando queremos um professor a partir do ID, e n�o existe nenhum professor com esse ID.
 */
class NonExistentTeacherID {
public:
	/**
	 * Construtor da classe NonExistentTeacherID
	 * @param ID
	 */
	NonExistentTeacherID(unsigned int ID);
	unsigned int ID;
};

/**
 * Exce��o que aparece quando comparamos o dia da semana de uma aula com o dia da semana da data e n�o coincidem.
 */
class NotSameDayAsDate {
public:
	/**
	 *  Construtor da classe NotSameDayAsDate.
	 */
	NotSameDayAsDate();
};

/**
 * Exce��o que aparece quando invocamos getGivenLesson(Lesson,Date) e n�o existe a GivenLesson dessa aula nessa data.
 */
class NonExistentGivenLesson {
public:
	/**
	 * Construtor da classe NonExistentGivenLesson.
	 * @param lesson
	 * @param date
	 */
	NonExistentGivenLesson(Lesson lesson, Date date);
	Lesson lesson;
	Date date;
};

/**
 * Exce��o que aparece quando adicionamos uma campanha promocional e ele se sobrep�e a outra.
 */
class OverlapingCampaign {
public:
	/**
	 * Construtor da classe OverlapingCampaign
	 */
	OverlapingCampaign();
};


class CustomerAlreadyAttendedLesson {

};

#else

class Pool;

#endif
