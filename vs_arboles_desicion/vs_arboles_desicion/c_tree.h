#ifndef C_TREE_H
#define C_TREE_H

#include <iostream>
#include <vector>
#include <math.h>
#include "c_nodo.h"

using namespace std;

class c_tree
{
public:
	vector< vector <string>> data;
	vector< vector< string > > extracted_atributes;
	vector< vector<int> > numeric_atributes;

	int analyze_column; // from 0 - data.size()-1;
	int start_column; //Must be diferent from analyze_column
	c_nodo* head;

	c_tree(vector< vector <string> >, int, int);
	void main_iteraction();
	void print_data();
	float entropia_column(int); //Recibe una columna y bota su entropia
	float entropia_base_atribute(int, int);
	float get_entropia_dependent(string, int, int);

	~c_tree();
};



c_tree::c_tree(vector<vector <string> > _data, int a_column, int s_column){
	this->data = _data;
	this->analyze_column = a_column;
	this->start_column = s_column;
	this->head = NULL;

	this->extracted_atributes = vector<vector<string>>(0, vector<string>(0, ""));
	this->numeric_atributes = vector<vector<int>>(0, vector<int>(0, 0));
}

void c_tree::main_iteraction() {
	this->extracted_atributes = vector<vector<string>>(this->data[0].size(), vector<string>(0, ""));
	this->numeric_atributes = vector<vector<int>>(this->data[0].size(), vector<int>(0, 0));
	
	for (unsigned int i = 0; i < this->data[0].size(); i++) {
		this->extracted_atributes[i].push_back(this->data[0][i]);
		this->numeric_atributes[i].push_back(0);
	}//++
		
	for (unsigned int i = 0; i < this->data.size(); i++) {
		for (unsigned int j = 0; j < this->data[0].size(); j++) {
			bool change = false;

			for (unsigned int k = 0; k < this->extracted_atributes[j].size(); k++) {
				if (this->data[i][j] == this->extracted_atributes[j][k]) {
					change = true;
					this->numeric_atributes[j][k] += 1;
				}
				else{
				}
			}
			if (!change) {
				this->extracted_atributes[j].push_back(this->data[i][j]);
				this->numeric_atributes[j].push_back(1);
			}
		}
	}
	//++
	//Obtenemos los valores distinto por cada atributo	
	//A este punto la estructura de extracted_atributes es igual a la de numeric_atributes
	/*
	for (unsigned int i = 0; i < extracted_atributes.size(); i++) {
		cout << i << endl;
		for (unsigned int j = 0; j < extracted_atributes[i].size(); j++) {
			cout << extracted_atributes[i][j] << " -> " << numeric_atributes[i][j] << endl;
		}
	}
	*/
	float entropia_inicial = this->entropia_column(this->analyze_column);
	cout << "Entropia Inicial: " << entropia_inicial << endl;
	//BASE ITERACTION	
	
	vector<string> c_names;
	vector<float> c_dates;
	for (unsigned int i = 0; i < this->numeric_atributes.size(); i++) {
		if (i != this->analyze_column) {//Evitamos columna de resultados (usualment ultima)
			long double entropia_acumulada_primera = this->entropia_base_atribute(i, this->analyze_column);
			entropia_acumulada_primera = entropia_inicial + entropia_acumulada_primera;
			c_dates.push_back(entropia_acumulada_primera);
		}

	}

	cout << "Entropia Agrupada: " << endl;
	for (unsigned int i = 0; i < c_dates.size(); i++) {
		cout << c_dates[i] << " ";
	}

}

float c_tree::entropia_base_atribute(int atributo, int a_column) { //a_column == this->analyze_column
	long double answer = 0.0;
	for (unsigned int i = 0; i < this->numeric_atributes[atributo].size(); i++) {
		long double proporcion = -1.0 * ((long double)this->numeric_atributes[atributo][i] / (long double)this->data.size());
		proporcion = proporcion * this->get_entropia_dependent(this->extracted_atributes[atributo][i], this->numeric_atributes[atributo][i], atributo);
		answer += proporcion;
	}
	return (float)answer;
}

float c_tree::get_entropia_dependent(string caracter, int numeric_caracter, int column) {
	vector<int> temp_vect = vector<int>(this->numeric_atributes[this->analyze_column].size(), 0);
	for (unsigned int i = 0; i < this->data.size(); i++) {
		if (this->data[i][column] == caracter) {
			for (unsigned int j = 0; j < temp_vect.size(); j++) {
				if (this->data[j][this->analyze_column] == extracted_atributes[this->analyze_column][j]) {
					temp_vect[j] += 1;
				}
			}
		}
	}
	long double answer = 0.0;
	for (unsigned int i = 0; i < temp_vect.size(); i++) {
		long double temp = -1 * (temp_vect[i] / numeric_caracter);
		answer += (temp * log2l(-temp));
	}
	return (float)answer;
}

float c_tree::entropia_column(int col) {
	long double answer = 0.0;
	for (unsigned int i = 0; i < this->numeric_atributes[col].size(); i++) {
		long double temp = -1.0* ((long double)this->numeric_atributes[col][i] / (long double)this->data.size());
		answer += (temp) * log2l(-temp);
	}
	return (float)answer;
}

void c_tree::print_data() {
	for (unsigned int i = 0; i < this->data.size(); i++) {
		for (unsigned int j = 0; j < this->data[0].size(); j++) {
			cout << this->data[i][j] << " ";
		}
		cout << endl;
	}
}

c_tree::~c_tree(){
}


#endif