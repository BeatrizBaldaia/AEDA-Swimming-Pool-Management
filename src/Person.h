#ifndef _PERSON_H_
#define _PERSON_H_

#include <list>
#include <string>
#include <vector>

#include "Date.h"
#include "PoolUse.h"
#include "Shop.h"

using namespace std;

/**
 * \brief Classe que representa a informacao do cliente relacionada com a morada e contacto de telemovel
 * */
class ContactInfo {
private:
	/**
	 * cidade em que vive a pessoa
	 * */
	string city;
	/**
	 * rua onde vive a pessoa
	 * */
	string street;
	/**
	 * numero da casa da pessoa
	 * */
	int number;
	/**codigo postal
	 * */
	string postalCode;
	/**numero de telemovel
	 * */
	long cellphoneNum;
public:
	/**
	 * Construtor default da classe ContactInfo.
	 */
	ContactInfo();
	/**
	 * Construtor da classe ContactInfo.
	 * @param city
	 * @param street
	 * @param number
	 * @param number
	 * @param postalCode
	 * @param cellphoneNum
	 */
	ContactInfo(string city, string street, int number, string postalCode,
			long cellphoneNum);
	/**
	 * retorna a cidade
	 * @return string
	 */
	string getCity() const;
	/**
	 * retorna a rua
	 * @return string
	 */
	string getStreet() const;
	/**
	 * retorna o numero da casa
	 * @return int
	 */
	int getNumber() const;
	/**
	 * retorna o codigo postal
	 * @return string
	 */
	string getPostalCode() const;
	/**
	 * altera a cidade
	 * @param city
	 */
	void setCity(string city);
	/**
	 * altera a rua
	 * @param street
	 */
	void setStreet(string street);
	/**
	 * altera o numero da casa
	 * @param number
	 */
	void setNumber(int number);
	/**
	 * altera o codigo postal
	 * @param code
	 */
	void setPostalCode(string code);
	/**
	 * retorna o contacto
	 * @return long
	 */
	long getCellphoneNum() const;
	/**
	 * altera o contacto
	 * @param cellphoneNum
	 */
	void setCellphoneNum(long cellphoneNum);
};

/**
 * \brief Classe que representa uma pessoa
 */
class Person {
public:
	/**
	 * Construtor da classe Person
	 * @param name
	 * @param birthDate
	 * @param contactInfo
	 */
	Person(string name, Date birthDate, ContactInfo contactInfo);
	/**
	 * Construtor da classe Person
	 * @param name
	 * @param birthDate
	 * @param ID
	 * @param contactInfo
	 */
	Person(string name, Date birthDate, unsigned int ID,
			ContactInfo contactInfo);
	/**
	 * retorna o nome da pessoa
	 * @return
	 */
	string getName() const;
	/**
	 * retorna o ID da pessoa
	 * @return
	 */
	unsigned int getID() const;
	/**
	 * retorna a data de aniversario da pessoa
	 * @return
	 */
	Date getBirthDate() const;
	/**
	 * retorna o numero de vezes que a pessoa frequentou a piscina
	 * @return
	 */
	virtual int getEntryNumber() const = 0;
	/**
	 * altera o nome da pessoa
	 * @param name
	 */
	void setName(string name);
	/**
	 * retorna a cidade
	 * @return
	 */
	string getCity() const;
	/**
	 * retorna a rua
	 * @return
	 */
	string getStreet() const;
	/**
	 * retorna o numero da casa
	 * @return
	 */
	int getNumber() const;
	/**
	 * retorna o codigo postal
	 * @return
	 */
	string getPostalCode() const;
	/**
	 * retorna o codigo postal
	 * @return
	 */
	long getCellphoneNum() const;
	/**
	 * altera a cidade em que vive
	 * @param city
	 */
	void setCity(string city);
	/**
	 * altera a rua em que vive
	 * @param street
	 */
	void setStreet(string street);
	/**
	 * retorna o numero da casa em que vive
	 * @return int
	 */
	void setNumber(int number);
	/**
	 * retorna o codigo postal
	 * @return string
	 */
	void setPostalCode(string code);
	/**
	 * altera o contacto
	 * @param cellphoneNum
	 */
	void setCellphoneNum(long cellphoneNum);
	/**
	 * ultimo ID atribuido a um utente da piscina
	 * */
	static unsigned int lastID;
private:
	const unsigned int ID;
	string name;
	Date birthDate;
	ContactInfo contactInfo;

};
/**
 * \brief Classe que representa uma pessoa que e utente da piscina
 */
class Customer: public Person {
public:
	/**
	 * Construtor da classe Customer
	 * @param name
	 * @param birthDate
	 * @param contactInfo
	 */
	Customer(string name, Date birthDate, ContactInfo contactInfo);
	/**
	 * Construtor da classe Customer
	 * @param name
	 * @param birthDate
	 * @param ID
	 * @param contactInfo
	 */
	Customer(string name, Date birthDate, unsigned int ID,
			ContactInfo contactInfo);
	/**
	 * retorna o que o cliente tem a pagar num determinado mes do ano
	 * @param month
	 * @param year
	 * @return
	 */
	float getMonthCost(unsigned int month, unsigned int year) const;
	/**
	 * retorna o numero de vezes que a pessoa frequentou a piscina
	 * @return
	 */
	int getEntryNumber() const; /// frequência com que os clientes vão á piscina
	/**
	 * retorna o vetor com os usos da piscina que o utente ja realizou
	 * @return
	 */
	vector<PoolUse *> getPoolUses();
	/**
	 * adiciona aula ao cliente
	 * @param lesson
	 * @param date
	 * @param time
	 * @param discount
	 */
	void attendLesson(GivenLesson * lesson, Date date, Time time,
			double discount); ///adicionar aula (cliente foi a aula)
	/**
	 * regista uso livre da piscina ao cliente
	 * @param startTime
	 * @param date
	 * @param duration
	 * @param discount
	 */
	void freeSwim(Time startTime, Date date, unsigned int duration,
			double discount); ///adicionar uso em modo livre
	/**
	 * adiciona uso em modo livre ao cliente
	 * @param pooluse
	 */
	void addUse(PoolUse * pooluse); ///adicionar uso em modo livre
	/**
	 * verifica se o cliente ja participou numa determinada aula na piscina
	 * @param lesson
	 * @return
	 */
	bool attendedLesson(const GivenLesson * lesson);
	/**
	 * realiza uma compra (de um ou varios produtos) ao cliente, na loja da piscina
	 * @param items
	 * @return
	 */
	void buyItem(vector<Item> items);
private:
	/**
	 * vetor com todos os usos (aulas e usos livres da piscina) do cliente
	 * */
	vector<PoolUse *> uses;
	/**
	 * lista com todos os produtos ja comprados pelos clientes
	 * */
	list<Item> shopping;
};

class Teacher: public Person {
public:
	/**
	 * Construtor da classe Teacher
	 * @param name
	 * @param birthDate
	 * @param contactInfo
	 */
	Teacher(string name, Date birthDate, ContactInfo contactInfo);
	/**
	 * Construtor da classe Teacher
	 * @param name
	 * @param birthDate
	 * @param ID
	 * @param contactInfo
	 */
	Teacher(string name, Date birthDate, unsigned int ID,
			ContactInfo contactInfo);
	/**
	 * retorna o que o cliente tem a pagar num determinado mes do ano
	 * @param month
	 * @return
	 */
	float getMonthCost(unsigned int month) const; ///possivel implementação para a segunda parte do projeto
	/**
	 * retorna o numero de aulas que o professor esta a dar por semana
	 * @return
	 * */
	int getNumberLessons() const; ///numero de aulas por semana
	/**
	 * retorna o numero de vezes que a pessoa frequentou a piscina
	 * @return
	 */
	int getEntryNumber() const;
	/**
	 * atribuir aula ao professor, e atribuir o mesmo número de aulas aos professores(tenta equilibrar o numero de aulas atribuidas a todos os professores)
	 * */
	void setLesson(); ///atribuir aula ao professor, e atribuir o mesmo número de aulas aos professores
	/**
	 * operador menor. um professor e menor que outro quando tem menos aulas dadas por semana que o outro
	 * @param t2
	 * @return
	 * */
	bool operator <(const Teacher & t2) const;
private:
	/**
	 * numero de aulas dadas por semana pelo professor
	 * */
	int lessonsPerWeek;
};
#else

class Customer;
class Teacher;

#endif
