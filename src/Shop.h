#ifndef SRC_SHOP_H_
#define SRC_SHOP_H_

#include <string>
#include <vector>

#include "BST.h"

class Customer;

/**
 * \brief Classe que representa um Item vendido na loja
 * */
class Item {
private:
	/**
	 * designacao do produto
	 * */
	string designation;
	/**
	 * tamanho do produto
	 * */
	string size;
	/**
	 * numero de stock do produto
	 * */
	unsigned int stock;
public:
	/**
	 * Construtor da classe Item.
	 * @param designation
	 * @param size
	 * @param stock
	 */
	Item(string designation, string size, unsigned int stock);
	/**
	 * retorna a designacao do produto
	 * @return string
	 */
	string getDesignation() const;
	/**
	 * retorna o tamanho do produto
	 * @return string
	 */
	string getSize() const;
	/**
	 * retorna o stock do produto
	 * @return unsigned int
	 */
	unsigned int getStock() const;
	/**
	 * altera o tamanho do produto
	 * @param newSize
	 */
	void setSize(string newSize);
	/**
	 * altera o stock do produto
	 * @param numberStock
	 * @return void
	 */
	void setStock(unsigned int numberStock);
	/**
	 * oprador menor. esta comparacao e feita a partir da designaca de cada produto
	 * @param item2
	 * @return
	 */
	bool operator<(Item item2) const;
	/**
	 * operador de igualdade. produtos iguais tem a mesma designacao e tamanho
	 * @param item2
	 * @return
	 */
	bool operator==(Item item2) const;
};


/**
 * \brief Classe que representa a loja da Piscina
 * */
class Shop {
private:
	/**
	 * nome da loja
	 * */
	string name;
	/**
	 * arvore binaria de pesquisa com todos os produtos da loja
	 * */
	BST<Item> shopItems;
public:
	/**
	 * Construtor da classe Shop.
	 * @param name
	 */

	Shop(string name);
	/**
	 * retorna o numero de itens existentes na loja
	 * @return int
	 */
	int getNumberOfItems() const;
	/**
	 * retorna o nome da loja
	 * @return
	 */
	string getName() const;
	/**
	 * funcionario da loja vende artigos a um utente; numero do stock diminui
	 * @param person
	 * @param items
	 */
	void sellItem(Customer *person, vector<Item> items); ///funcionario da loja vende artigo; numero do stock diminui
	/**
	 * funcionario compra artigos ao fornecedor; numero de stock aumenta
	 * @param items
	 */
	void buyItem(vector<Item> items); ///funcionario compra artigos ao fornecedor; numero de stock aumenta
	/**
	 * retorna um vetor com todos os itens da loja
	 * @return
	 */
	vector<Item> getItems() const;
	/**
	 * retorna a arvore binaria de pesquisa que contem todos os produtos da loja
	 * @return
	 */
	BST<Item> getTree() const;
};

#endif /* SRC_SHOP_H_ */
