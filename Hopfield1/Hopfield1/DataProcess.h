#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <iostream>
#include <fstream>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <Windows.h>
#include "SomeFunctions.h"

using namespace std;

class DataProcess {
	int data_size;
	int data_number;
	int data_distribution;
	string ruta;
public:
	DataProcess(int, int, int, string );
	~DataProcess();

	vector< gsl_matrix_int* > read_data();
	gsl_matrix_int* get_element(string, bool); //Reconoce el primer patron acorde la patron de un documento
};

DataProcess::DataProcess(int data_number_, int data_size_, int data_distribution_,  string ruta_) {
	this->data_number = data_number_;
	this->data_size = data_size_;
	this->data_distribution = data_distribution_;
	this->ruta = ruta_;
}

vector< gsl_matrix_int* > DataProcess::read_data() {
	int digit_read = 0;
	char inner_ruta[20]; strcpy_s(inner_ruta, this->ruta.c_str());
	fstream reader;
	vector< gsl_matrix_int* > answer = vector<gsl_matrix_int*>(0, NULL);

	reader.open(inner_ruta, ios::in);

	if (!reader.is_open()) {
		cout << "No se pudo abrir el archivo de datos" << endl;
	}
	else {
		for (int i = 0; i < this->data_number; i++) {
			
			gsl_matrix_int* temp = gsl_matrix_int_alloc(1, this->data_size);
						
			for (int j = 0; j < this->data_size; j++) {
				reader >> digit_read;
				if (digit_read < 1) { digit_read = -1; }
				
				gsl_matrix_int_set(temp, 0, j, digit_read);

			}
			answer.push_back(temp);
		}
		
		reader.close();
		cout << "Lectura Finalizada" << endl;
		return answer;
	}
}

gsl_matrix_int* DataProcess::get_element(string ruta_, bool format) {
	gsl_matrix_int* answer = gsl_matrix_int_alloc(1, this->data_size);
	int digit_read = 0;
	fstream reader;
	char inner_ruta[20]; strcpy_s(inner_ruta, ruta_.c_str());
	
	reader.open(inner_ruta, ios::in);
	
	if (!reader.is_open()) {
		cout << "No se pudo leer el elemento señalado -- Data Corruption" << endl;
		return answer;
	}
	else {
		for (int i = 0; i < this->data_size; i++) {
			reader >> digit_read;
			if (format) {
				if (digit_read < 1) { digit_read = -1; } //--
			}
			gsl_matrix_int_set(answer, 0, i, digit_read);
		}
		reader.close();	
		return answer;
	}
}

DataProcess::~DataProcess() {}






#endif // !DATAPROCESS_H
