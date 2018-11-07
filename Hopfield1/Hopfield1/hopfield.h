#ifndef HOPFIELD_H
#define HOPFIELD_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <iostream>
#include <vector>
#include "SomeFunctions.h"
#include "DataProcess.h"

using namespace std;

class hopfield
{
public:
	vector<gsl_matrix_int*> data;
	vector<gsl_matrix_int*> original;
	vector<float> energia;
	gsl_matrix_int* f_data;
	int cant_data; 
	int data_size;
	int data_distribution;
	int max_iter;


	hopfield(int, int, int);
	~hopfield();

	void set_data_element(gsl_matrix_int*);
	void learn();
	void recognize(gsl_matrix_int*);
	void recognize_dev(gsl_matrix_int*, int); //Instead of a vector a matrix should be provided
	
	void recognize_v2(gsl_matrix_int*);
	void recognize_dev_v2(gsl_matrix_int*, int);
	void funcion_1_reconocimiento(gsl_matrix_int*);
	bool funcion_2_reconocimiento(gsl_matrix_int*, int, int);
	bool review(gsl_matrix_int*);
	void set_energia();

	void get_data();
	void print_data_vector();
};



hopfield::hopfield(int data_size_, int data_distribution_,int max_iter_) { 
	this->data_size = data_size_;
	this->data_distribution = data_distribution_;
	this->data = vector< gsl_matrix_int* >(0, NULL);
	this->original = vector<gsl_matrix_int*>(0, NULL);
	this->energia = vector<float>(0,0.0);
	this->cant_data = 0;
	this->f_data = gsl_matrix_int_alloc(this->data_size,this->data_size); // Inicializado a zero.
	gsl_matrix_int_set_zero(this->f_data);
	this->max_iter = max_iter_;
	
}


void hopfield::set_data_element(gsl_matrix_int* c_matrix) { // c_matrix = 1 x data_size
	gsl_matrix_int* transp = gsl_matrix_int_alloc(c_matrix->size2, c_matrix->size1); //transp = data_size x 1 
	gsl_matrix_int* f_matrix = gsl_matrix_int_alloc(c_matrix->size2, c_matrix->size2);
	
	gsl_matrix_int_transpose_memcpy(transp, c_matrix);

	gsl_matrix_multiplication(transp, c_matrix, f_matrix);
	this->data.push_back(f_matrix);
	this->cant_data++;
	this->original.push_back(c_matrix);//Unusable

	gsl_matrix_int_free(transp);
}

void hopfield::learn() {
	cout << "f_Data: " << this->f_data->size1 << " x " << this->f_data->size2 << "  data: " << data[0]->size1 << " x " << data[0]->size2 << endl;

	for (unsigned int i = 0; i < this->data.size(); i++) {
		gsl_matrix_int_add(this->f_data, this->data[i]);
		//gsl_my_matrix_addition(this->f_data, this->data[i]);
	}
	for (int i = 0; i < this->data_size; i++) {
		gsl_matrix_int_set(this->f_data, i, i, 0);
	}
	gsl_matrix_normalize(this->f_data);
	cout << "Learned Phase Complete" << endl;
}

void hopfield::recognize_v2(gsl_matrix_int* incoming) {
	cout << "Recognize v2" << endl;
	gsl_print_matrix_ascii(gsl_set_matrix_with_format(incoming, this->data_distribution, true));
	this->recognize_dev_v2(incoming, 0);
}

void hopfield::recognize_dev_v2(gsl_matrix_int* incoming, int keeper) {
	if (keeper < this->max_iter) {
		//cout << "RECOGNIZE_DEV_V2_FLAG" << endl;
		int alter = get_random_integer_in_range(this->data_size);//Obtenemos la columna a actualizar

		gsl_matrix_int* w_row = gsl_matrix_int_alloc(1, this->f_data->size2);
		gsl_matrix_int_set_zero(w_row);
		gsl_my_matrix_int_get_row(w_row, this->f_data, alter);
		int result = gsl_matrix_int_point_product(incoming, w_row);

		gsl_matrix_int_free(w_row);

		//cout << "Reconocimiento" << endl;
		if (this->funcion_2_reconocimiento(incoming, result, alter)) {
			this->recognize_dev_v2(incoming, keeper+1);
		}
		else {
			this->recognize_dev_v2(incoming, 0);
		}
	}
	else {
		cout << "Resultado Final: " << endl; gsl_print_matrix_ascii(gsl_set_matrix_with_format(incoming, this->data_distribution, true));
		gsl_matrix_int_free(incoming);
	}
}

void hopfield::recognize(gsl_matrix_int* incoming) {

	cout << "Elemento a reconocer: " << endl;
	gsl_print_matrix(gsl_set_matrix_with_format(incoming, this->data_distribution, true));

	this->recognize_dev(incoming, 0);
}

void hopfield::recognize_dev(gsl_matrix_int* incoming, int current_iter) {
	if (current_iter < this->max_iter) {
		//Matrix of 1 x this->data_size dimensions.

		gsl_matrix_int* r_matrix = gsl_matrix_int_alloc(incoming->size1, incoming->size2);
		gsl_matrix_int_set_zero(r_matrix);

		gsl_matrix_multiplication(incoming, this->f_data, r_matrix);
		
		cout << "Incoming" << endl;
		gsl_print_matrix(incoming);

		cout << "Tras la multiplicacion (false): " << endl;
		gsl_print_matrix(gsl_set_matrix_with_format(r_matrix, this->data_distribution, false));
		cout << endl;


		this->funcion_1_reconocimiento(r_matrix);

		cout << "Incoming: " << endl;
		gsl_print_matrix(gsl_set_matrix_with_format(incoming, this->data_distribution, true));
		cout << endl;
		cout << "Tras la funcion de reconocimiento: " << endl;
		gsl_print_matrix(gsl_set_matrix_with_format(r_matrix, this->data_distribution, true));
		
		//cout << "Resultado neto: " << endl; gsl_print_matrix(r_matrix);
		if ( (gsl_matrix_int_equal(r_matrix, incoming) != 1) ) { //No son iguales 
			gsl_matrix_int_free(incoming);
			this->recognize_dev(r_matrix, current_iter + 1);
			//Free memory was here
			return;
		}
		else {
			cout << "Existen " << this->data.size() << " elementos." << endl;
			cout << "Resultado Final tras : " <<current_iter<<" iteracciones. "<< endl;
			gsl_print_matrix(r_matrix); cout << endl;
			gsl_print_matrix_ascii(gsl_set_matrix_with_format(r_matrix, this->data_distribution, true));
			gsl_matrix_int_free(r_matrix);
			gsl_matrix_int_free(incoming);
			return;
		}
	}
	else {
		cout << "Se ha superado el maximo de iteracciones" << endl;
		cout << "Resultado Final: " << endl; gsl_print_matrix_ascii(gsl_set_matrix_with_format(incoming, this->data_distribution, true));
		gsl_matrix_int_free(incoming);
	}
}

bool hopfield::review(gsl_matrix_int* incoming) {
	for (unsigned int i = 0; i < this->original.size(); i++) {
		if (gsl_matrix_int_equal(incoming, this->original[i]) == 1) {
			return true;
		}
	}
	return false;
}

void hopfield::funcion_1_reconocimiento(gsl_matrix_int* incoming) {
	//Must be a matrix of 1 x this->data_size dimensions. But in case we do it for general matrix.
	for (int i = 0; i < incoming->size1; i++) {
		for (int j = 0; j < incoming->size2; j++) {
			if (gsl_matrix_int_get(incoming, i, j) >= 0) {
				gsl_matrix_int_set(incoming, i, j, 1);
			}
			else {
				gsl_matrix_int_set(incoming, i, j, -1);
			}
		}
	}

}

bool hopfield::funcion_2_reconocimiento(gsl_matrix_int* incoming, int obtained, int pos) {
	if (obtained > -5) {
		obtained = 1;
		if (gsl_matrix_int_get(incoming, 0, pos) == obtained) {
			return true;
		}
		else {
			gsl_matrix_int_set(incoming, 0, pos, obtained);
			return false;
		}
	}
	else{
		obtained = -1;
		if (gsl_matrix_int_get(incoming, 0, pos) == obtained) {
			return true;
		}
		else {
			gsl_matrix_int_set(incoming, 0, pos, obtained);
			return false;
		}
	}
}

//This function should be executed after learn() function
void hopfield::set_energia() {
	int answer = 0;
	for (unsigned int x = 0; x < this->original.size(); x++) {
		for (int i = 0; i < this->f_data->size1; i++) {
			for (int j = 0; j < this->f_data->size2; j++) {
				answer += gsl_matrix_int_get(this->f_data, i, j) * gsl_matrix_int_get(this->original[x], 0, i) * gsl_matrix_int_get(this->original[x], 0, j);
			}
		}
		answer = (- 1 / 2)*answer;
		this->energia.push_back(answer);
		answer = 0;
	}

	cout << "Energia" << endl;
	for (unsigned int i = 0; i < this->energia.size(); i++) {
		cout << i << " -> " << energia[i] << " ";
	}
	return;
}

void hopfield::get_data() {
	cout << "------------------HOPFIELD EXPANDED DATA---------------------------" << endl;
	cout << "Elementos aprendidos: " << this->cant_data << endl;
	cout << "Longitud de los Datos: " << this->data_size << endl;
	cout << "Vector Size: " << this->data.size() << endl;
	this->print_data_vector();
	cout << "Conocimiento acumulado: " << endl;
	gsl_print_matrix(this->f_data);
}

void hopfield::print_data_vector() {
	for (unsigned int i = 0; i < this->data.size(); i++) {
		gsl_print_matrix(this->data[i]);
		cout << endl << endl;
	}
}

hopfield::~hopfield()
{
}

#endif // !HOPFIELD_H