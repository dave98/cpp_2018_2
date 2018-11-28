#ifndef DATASET_READER_H
#define DATASET_READER_H

#include <iostream>
#include <fstream>
#include <vector>	
#include <stdlib.h>
#include <string>

using namespace std;


template <int A, int B> // A representa las columnas (numero de atributos), B el numero de filas (numero de datos)
class Dataset_Reader
{
public:
	int cant_att;
	int cant_dat;
	string ruta;
	vector< vector< string > > data;

	Dataset_Reader(string);
	void read_data();
	void show_data();
	vector< vector <string> >& get_data();
	~Dataset_Reader();
};


template <int A, int B>
Dataset_Reader<A, B>::Dataset_Reader(string _ruta){
	this->cant_att = A;
	this->cant_dat = B;
	this->ruta = _ruta;
	
}

template <int A, int B>
Dataset_Reader<A, B>::~Dataset_Reader()
{
}


template <int A, int B>
void Dataset_Reader<A, B>::read_data() {
	char inner_data[20]; strcpy_s(inner_data, this->ruta.c_str());
	fstream reader;

	reader.open(inner_data, ios::in);

	if (!reader.is_open()) {
		cout << "No se pudo abrir el documento" << endl;
	}
	else {
		for (int i = 0; i < this->cant_dat; i++) {
			vector< string > t_vec;
			for (int j = 0; j < this->cant_att; j++) {	
				string temp_val;
				reader >> temp_val;
				t_vec.push_back(temp_val);
			}
			this->data.push_back(t_vec);
		}
	}

	cout << "Complete Lecture" << endl;	
}

template <int A, int B>
void Dataset_Reader<A, B>::show_data() {
	for (unsigned int i = 0; i < this->data.size(); i++) {
		cout << i << " -> ";
		for (unsigned int j = 0; j < this->data[0].size(); j++) {
			cout << this->data[i][j] << " ";
		}
		cout << endl;
	}
}

template <int A, int B>
vector< vector <string> >& Dataset_Reader<A, B>::get_data() {
	return this->data;
}


#endif // !
