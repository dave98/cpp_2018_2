#pragma once
class c_nodo_3
{
public:
public:
	int value;
	c_nodo_3* next;

	c_nodo_3(int);
	virtual ~c_nodo_3();
};



c_nodo_3::c_nodo_3(int value_) {
	this->value = value_;
	this->next = nullptr;
}


c_nodo_3::~c_nodo_3()
{
}
