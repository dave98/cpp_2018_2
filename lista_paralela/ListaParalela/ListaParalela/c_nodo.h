#pragma once
class c_nodo
{
public:
public:
	int value;
	c_nodo* next;
	
	c_nodo(int);
	virtual ~c_nodo();
};



c_nodo::c_nodo(int value_){
	this->value = value_;
	this->next = nullptr;
}


c_nodo::~c_nodo()
{
}
