#pragma once
#include <iostream>
#include "c_nodo.h"
#include <wrl\wrappers\corewrappers.h>

using namespace std;

class c_list
{
public:
	c_nodo* head;


	c_list();
	virtual ~c_list();

	void insert(int);
	void print_list();
	void find(int);
};

c_list::c_list(){
	this->head = nullptr;
}


c_list::~c_list(){
}

void c_list::insert(int value_) {
	c_nodo* chariot = this->head;
	c_nodo* pre_chariot = nullptr;

	while (chariot and (chariot->value < value_)) {
		pre_chariot = chariot;
		chariot = chariot->next;
	}	

	if (chariot == this->head) {
		if (this->head == nullptr) {
			this->head = new c_nodo(value_);
		}
		else {
			chariot = new c_nodo(value_);
			chariot->next = this->head;
			this->head = chariot;
		}
	}
	else {
		if(!chariot){
			chariot = new c_nodo(value_);
			pre_chariot->next = chariot;
		}
		else {
			c_nodo* temp_n = new c_nodo(value_);
			temp_n->next = chariot;
			pre_chariot->next = temp_n;
		}
	}
}

void c_list::print_list() {
	c_nodo* chariot = this->head;
	while (chariot) {
		cout << chariot->value << " ";
		chariot = chariot->next;
	}
	cout << endl;
	return;
}

void c_list::find(int num_) {
	c_nodo* chariot = this->head;
	while (chariot) {
		if (chariot->value == num_) {
			cout << "El valor se ha encontrado" << endl;
			return;
		}
		chariot = chariot->next;
	}
	cout << "El valor no se ha encontrado" << endl;
	return;
}