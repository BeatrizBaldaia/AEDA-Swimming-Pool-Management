#include "Shop.h"

/* Item */


Item::Item(string designation, unsigned int size, unsigned int stock){
	this->designation = designation;
	this->size = size;
	this->stock = stock;
}

string Item::getDesignation() const{
	return designation;
}

unsigned int Item::getSize() const{
	return size;
}

unsigned int Item::getStock() const{
	return stock;
}

void Item::setSize(unsigned int newSize){
	size = newSize;
}

void Item::setStock(unsigned int numberStock){
	stock = numberStock;
}

bool Item::operator< (Item &item2) const{
	if(designation == item2.getDesignation()){
		return size < item2.getSize();
	}
	return designation < item2.getDesignation();
}


/* Shop */


Shop::Shop(string name){
	shopItems(Item("",0,0));
}

void Shop::sellItem(Person *person, Item item){
	person->buyItem(item);
	string d = item.getDesignation();
	unsigned int s = item.getSize();
	 BSTItrIn<Item>it(shopItems);
	 while(!it.isAtEnd()){
		 if(it.retrieve().getDesignation() == d && it.retrieve().getSize() == s){
			 Item i = it.retrieve();
			 shopItems.remove(i);
			 unsigned int n = i.getStock()+1;
			 i.setStock(n);
			 shopItems.insert(i);
			 return;
		 }
	 }
	 throw InvalidItem(item.getDesignation(), item.getSize());
}

void Shop::sellItem(Person *person, vector<Item> items){
	bool exist = false;
	vector<Item>nonexistent;
	vector<Item>saveItems;

	for(const Item &x : items){
		string d = x.getDesignation();
		unsigned int s = x.getSize();
		BSTItrIn<Item>it(shopItems);
		while(!it.isAtEnd()){
			if(it.retrieve().getDesignation() == d && it.retrieve().getSize() == s){
				saveItems.push_back(it.retrieve());
				Item i = it.retrieve();
				shopItems.remove(i);
				unsigned int n = x.getStock()+i.getStock();
				i.setStock(n);
				shopItems.insert(i);
				exist = true;
				break;
			}
		}
		if(!exist){
			nonexistent.push_back(x);
		}
		exist = false;
	}
	person->buyItem(saveItems);

	if(nonexistent.size() != 0){
		throw InvalidItems(nonexistent);
	}
}

void Shop::buyItem(vector<Item> items){
	bool exist = false;
		vector<Item>nonexistent;
		vector<Item>overflowItems;

		for(const Item &x : items){
			string d = x.getDesignation();
			unsigned int s = x.getSize();
			BSTItrIn<Item>it(shopItems);
			while(!it.isAtEnd()){
				if(it.retrieve().getDesignation() == d && it.retrieve().getSize() == s){
					Item i = it.retrieve();
					unsigned int n = i.getStock() - x.getStock();
					shopItems.remove(i);
					if(n > 0){
					i.setStock(n);
					shopItems.insert(i);
					exist = true;
					break;
					}
					if(n < 0){
						overflowItems.push_back(x);
						exist = true;
						break;
					}
				}
			}
			if(!exist){
				nonexistent.push_back(x);
			}
			exist = false;
		}
		if(nonexistent.size() != 0 && overflowItems.size() != 0){
			throw InvalidRemoveItem(nonexistent,overflowItems);
		}
		if(nonexistent.size() != 0){
			throw InvalidItems(nonexistent);
		}
		if(overflowItems.size() != 0){
			throw InvalidStock(overflowItems);
		}
}
