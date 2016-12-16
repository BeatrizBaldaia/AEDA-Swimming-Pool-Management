#ifndef SRC_SHOP_H_
#define SRC_SHOP_H_

#include "BST.h"
#include "Exceptions.h"

class Item{
private:
	string designation;
	unsigned int size;
	unsigned int stock;
public:
	Item(string designation, unsigned int size, unsigned int stock);
	string getDesignation() const;
	unsigned int getSize() const;
	unsigned int getStock() const;
	void setSize(unsigned int newSize);
	void setStock(unsigned int numberStock);
	bool operator< (Item &item2) const;
};
class Shop{
private:
	string name;
	BST<Item> shopItems;
public:
	Shop(string name);
	int getNumberOfItems() const;
	void sellItem(Person *person, Item item); ///funcionario da loja vende artigo; numero do stock diminui
	void sellItem(Person *person, vector<Item> items);
	void buyItem(vector<Item> items); ///funcionario compra artigos ao fornecedor; numero de stock aumenta
};



#endif /* SRC_SHOP_H_ */
