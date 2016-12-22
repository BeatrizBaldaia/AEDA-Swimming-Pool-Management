#include "Shop.h"

#include <cmath>

#include "Exceptions.h"
#include "Person.h"

/* Item */


Item::Item(string designation, string size, unsigned int stock){
	this->designation = designation;
	this->size = size;
	this->stock = stock;
}

string Item::getDesignation() const{
	return designation;
}

string Item::getSize() const{
	return size;
}

unsigned int Item::getStock() const{
	return stock;
}

void Item::setSize(string newSize){
	size = newSize;
}

void Item::setStock(unsigned int numberStock){
	stock = numberStock;
}

bool Item::operator< (Item item2) const{
	if(designation == item2.getDesignation()){
		return size < item2.getSize();
	}
	return designation < item2.getDesignation();
}

bool Item::operator== (Item item2) const{
	return ((designation == item2.getDesignation()) && (size == item2.getSize()));
}


/* Shop */


Shop::Shop(string name): shopItems(Item("","",0)), name(name){}

int Shop::getNumberOfItems() const{
	int size;
	size = getItems().size();
	return size;
}

string Shop::getName() const{
	return name;
}

void Shop::buyItem(vector<Item> items){
	bool exist = false;
	for(const Item &x : items){
		string d = x.getDesignation();
		string s = x.getSize();
		BSTItrIn<Item>it(shopItems);
		while(!it.isAtEnd()){
			if(it.retrieve().getDesignation() == d && it.retrieve().getSize() == s){
				Item i = it.retrieve();
				shopItems.remove(i);
				unsigned int n = x.getStock()+i.getStock();
				i.setStock(n);
				shopItems.insert(i);
				exist = true;
				break;
			}
			it.advance();
		}
		if(!exist){
			shopItems.insert(x);
		}
		exist = false;
	}
}

void Shop::sellItem(Customer *person, vector<Item> items){
	bool exist = false;
	vector<Item> nonexistent;
	vector<Item> overflowItems;
	vector<Item> saveItems;

	for (Item &x : items) {
		string d = x.getDesignation();
		string s = x.getSize();
		BSTItrIn<Item> it(shopItems);
		while (!it.isAtEnd()) {
			if (it.retrieve().getDesignation() == d
					&& it.retrieve().getSize() == s) {
				Item i = it.retrieve();
				unsigned int n = i.getStock() - x.getStock();
				shopItems.remove(i);
				saveItems.push_back(x);
				if (n >= 0) { ///ha intens suficientes para vender ao cliente
					i.setStock(n);
					shopItems.insert(i);
					exist = true;
					break;
				}
				if (n < 0) { ///faltam intens para vender ao cliente
					Item save = x; ///item a guardar no cliente
					save.setStock((x.getStock() + n)); ///numero de intens que foi possivel comprar
					saveItems.push_back(save);
					x.setStock(abs(n)); ///item com o numero de stock em falta para a venda ao cliente
					i.setStock(0); ///acabou-se o stock do item
					shopItems.insert(i);
					overflowItems.push_back(x); ///adicionar item com stock insuficiente
					exist = true;
					break;
				}
			}
			it.advance();
		}
		if (!exist) {
			nonexistent.push_back(x);
		}
		exist = false;
	}
	person->buyItem(saveItems);
	if (nonexistent.size() != 0 && overflowItems.size() != 0) {
		throw InvalidRemoveItem(nonexistent, overflowItems);
	}
	if (nonexistent.size() != 0) {
		throw InvalidItems(nonexistent);
	}
	if (overflowItems.size() != 0) {
		throw InvalidStock(overflowItems);
	}
}


vector<Item>Shop::getItems() const{
	vector<Item>result;
	BSTItrIn<Item>it(shopItems);
	while(!it.isAtEnd()){
		Item i = it.retrieve();
		result.push_back(i);
		it.advance();
	}
	return result;
}

BST<Item> Shop::getTree() const{
	return shopItems;
}
