#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class c_nodo
{
public:
	string key_word;
	bool is_leaf;
	vector<c_nodo*> hijos;

	c_nodo(string);
	~c_nodo();
};

c_nodo::c_nodo(string k_word) {
	this->key_word = k_word;
	this->is_leaf = false; //By default
	this->hijos = vector<c_nodo*>(0, NULL);
}


c_nodo::~c_nodo()
{
}

#endif // !C_NODO_H
