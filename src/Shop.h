#ifndef SRC_SHOP_H_
#define SRC_SHOP_H_

#include <string>
#include <vector>

#include "BST.h"

class Customer;

class Item {
private:
	string designation;
	string size;
	unsigned int stock;
public:
	Item(string designation, string size, unsigned int stock);
	string getDesignation() const;
	string getSize() const;
	unsigned int getStock() const;
	void setSize(string newSize);
	void setStock(unsigned int numberStock);
	bool operator<(Item item2) const;
	bool operator==(Item item2) const;
};
class Shop {
private:
	string name;
	BST<Item> shopItems;
public:
	Shop(string name);
	int getNumberOfItems() const;
	string getName() const;
	void sellItem(Customer *person, vector<Item> items); ///funcionario da loja vende artigo; numero do stock diminui
	void buyItem(vector<Item> items); ///funcionario compra artigos ao fornecedor; numero de stock aumenta
	vector<Item> getItems() const;
	BST<Item> getTree() const;
};

#endif /* SRC_SHOP_H_ */
