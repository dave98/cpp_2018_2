#pragma once

#include <mutex>

class c_nodo_2
{
public:
public:
	mutex nodo_mtx;
	int value;
	c_nodo_2* next;

	c_nodo_2(int);
	virtual ~c_nodo_2();

	void change_pointer(c_nodo_2*);
};



c_nodo_2::c_nodo_2(int value_) {
	this->nodo_mtx.lock();
	this->value = value_;
	this->next = nullptr;
	this->nodo_mtx.unlock();
}

c_nodo_2::~c_nodo_2(){
}

void c_nodo_2::change_pointer(c_nodo_2* next_) {
	this->nodo_mtx.lock();
	this->next = next_;
	this->nodo_mtx.unlock();
}