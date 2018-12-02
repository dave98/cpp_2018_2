#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include <vector>
#include <string>
#include "SomeFunctions.h"

using namespace std;

class c_nodo
{
public:
	string key_word;//Indica el valor que toma especificamente este nodo
	int key_column;//En que columna se halla el atributo con este valor
	vector<int> where_to_checked;//Los puntos en donde buscamos
	bool is_leaf;
	vector<c_nodo*> hijos;

	c_nodo(string, int, vector<int>);
	~c_nodo();
	
	void print_nodo_data();
	void change_nodo_state();
};

c_nodo::c_nodo(string k_word, int k_column, vector<int> wt_checked) {
	this->key_word = k_word;
	this->key_column = k_column;
	this->where_to_checked = wt_checked;
	this->is_leaf = false; //By default
	this->hijos = vector<c_nodo*>(0, NULL);
}

void c_nodo::print_nodo_data() {
	cout << "Key word: " << this->key_word << endl;
	cout << "Key Column: " << this->key_column << endl;
	cout << "Is leaf: " << this->is_leaf << endl;
	print_vector(this->where_to_checked);
	if (this->hijos.size() != 0) {
		cout << "Imprimiendo datos de los hijos" << endl;
		for (unsigned int i = 0; i < this->hijos.size(); i++) {
			this->hijos[i]->print_nodo_data();
		}
	}
}

void c_nodo::change_nodo_state() {
	this->is_leaf = !this->is_leaf;
}

c_nodo::~c_nodo()
{
}

#endif // !C_NODO_H
