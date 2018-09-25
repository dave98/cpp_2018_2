#pragma once
#include <iostream>
#include "c_nodo_3.h"
#include <wrl\wrappers\corewrappers.h>

using namespace std;

class c_list_3
{
public:
	SRWLOCK srwlock;
	c_nodo_3* head;


	c_list_3();
	virtual ~c_list_3();

	void insert(int);
	void print_list();
	void find(int);
};

c_list_3::c_list_3() {
	this->head = nullptr;
}


c_list_3::~c_list_3() {
}

void c_list_3::insert(int value_) {
	AcquireSRWLockShared(&this->srwlock);

	c_nodo_3* chariot = this->head;
	c_nodo_3* pre_chariot = nullptr;

	while (chariot and (chariot->value < value_)) {
		pre_chariot = chariot;
		chariot = chariot->next;
	}

	if (chariot == this->head) {
		if (this->head == nullptr) {
			this->head = new c_nodo_3(value_);
		}
		else {
			chariot = new c_nodo_3(value_);
			chariot->next = this->head;
			this->head = chariot;
		}
	}
	else {
		if (!chariot) {
			chariot = new c_nodo_3(value_);
			pre_chariot->next = chariot;
		}
		else {
			c_nodo_3* temp_n = new c_nodo_3(value_);
			temp_n->next = chariot;
			pre_chariot->next = temp_n;
		}
	}

	ReleaseSRWLockShared(&this->srwlock);
}

void c_list_3::print_list() {
	c_nodo_3* chariot = this->head;
	while (chariot) {
		cout << chariot->value << " ";
		chariot = chariot->next;
	}
	cout << endl;
	return;
}

void c_list_3::find(int num_) {
	c_nodo_3* chariot = this->head;
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