#pragma once
#include <iostream>
#include "c_nodo_2.h"
#include <wrl\wrappers\corewrappers.h>

using namespace std;

class c_list_2
{
public:
	c_nodo_2* head;


	c_list_2();
	virtual ~c_list_2();

	void insert(int);
	void print_list();
	void find(int);
};

c_list_2::c_list_2() {
	this->head = nullptr;
}


c_list_2::~c_list_2() {
}

void c_list_2::insert(int value_) {
	c_nodo_2* chariot = this->head;
	c_nodo_2* pre_chariot = nullptr;

	while (chariot and (chariot->value < value_)) {
		pre_chariot = chariot;
		chariot = chariot->next;
	}

	if (chariot == this->head) {
		if (this->head == nullptr) {
			this->head = new c_nodo_2(value_);
		}
		else {
			chariot = new c_nodo_2(value_);
			//chariot->next = this->head;
			chariot->change_pointer(this->head);
			this->head = chariot;
		}
	}
	else {
		if (!chariot) {
			chariot = new c_nodo_2(value_);
			//pre_chariot->next = chariot;
			pre_chariot->change_pointer(chariot);
		}
		else {
			c_nodo_2* temp_n = new c_nodo_2(value_);
			//temp_n->next = chariot;
			//pre_chariot->next = temp_n;
			temp_n->change_pointer(chariot);
			pre_chariot->change_pointer(temp_n);
		}
	}
}

void c_list_2::print_list() {
	c_nodo_2* chariot = this->head;
	while (chariot) {
		cout << chariot->value << " ";
		chariot = chariot->next;
	}
	cout << endl;
	return;
}

void c_list_2::find(int num_) {
	c_nodo_2* chariot = this->head;
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