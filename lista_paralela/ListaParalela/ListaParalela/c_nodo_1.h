#pragma once
class c_nodo_1
{
public:
public:
	int value;
	c_nodo_1* next;

	c_nodo_1(int);
	virtual ~c_nodo_1();
};



c_nodo_1::c_nodo_1(int value_) {
	this->value = value_;
	this->next = nullptr;
}


c_nodo_1::~c_nodo_1()
{
}
