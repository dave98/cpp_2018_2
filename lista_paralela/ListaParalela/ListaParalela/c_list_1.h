#pragma once
#include <iostream>
#include "c_nodo_1.h"
#include <mutex>

using namespace std;

class c_list_1
{
public:
	c_nodo_1* head;
	mutex list_mtx;

	c_list_1();
	virtual ~c_list_1();

	void insert(int);
	void print_list();
	void find(int);
};

c_list_1::c_list_1() {
	this->head = nullptr;
}


c_list_1::~c_list_1() {
}

void c_list_1::insert(int value_) {
	this->list_mtx.lock();
	
	c_nodo_1* chariot = this->head;
	c_nodo_1* pre_chariot = nullptr;

	while (chariot and (chariot->value < value_)) {
		pre_chariot = chariot;
		chariot = chariot->next;
	}

	if (chariot == this->head) {
		if (this->head == nullptr) {
			this->head = new c_nodo_1(value_);
		}
		else {
			chariot = new c_nodo_1(value_);
			chariot->next = this->head;
			this->head = chariot;
		}
	}
	else {
		if (!chariot) {
			chariot = new c_nodo_1(value_);
			pre_chariot->next = chariot;
		}
		else {
			c_nodo_1* temp_n = new c_nodo_1(value_);
			temp_n->next = chariot;
			pre_chariot->next = temp_n;
		}
	}

	this->list_mtx.unlock();
}

void c_list_1::print_list() {
	c_nodo_1* chariot = this->head;
	while (chariot) {
		cout << chariot->value << " ";
		chariot = chariot->next;
	}
	cout << endl;
	return;
}

void c_list_1::find(int num_) {
	c_nodo_1* chariot = this->head;
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