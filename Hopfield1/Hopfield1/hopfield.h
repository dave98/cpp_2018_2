#ifndef HOPFIELD_H
#define HOPFIELD_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <iostream>
#include <vector>
#include "SomeFunctions.h"
#include "DataProcess.h"

using namespace std;

class hopfield
{
public:
	vector<gsl_matrix*> data;
	vector<gsl_matrix*> original;
	vector<float> energia;
	gsl_matrix* f_data;
	int cant_data; 
	int data_size;
	int data_distribution;
	int max_iter;


	hopfield(int, int, int);
	~hopfield();

	void set_data_element(gsl_matrix*);
	void set_data_element_inverse(gsl_matrix*);
	void learn();
	void learn_inverse();
	void recognize(gsl_matrix*);
	void recognize_dev(gsl_matrix*, int, int); //Instead of a vector a matrix should be provided
	
	void recognize_v2(gsl_matrix*);
	void recognize_dev_v2(gsl_matrix*, int);
	void funcion_1_reconocimiento(gsl_matrix*);
	bool funcion_2_reconocimiento(gsl_matrix*, int, int);
	bool review(gsl_matrix*);
	int set_energia(gsl_matrix*);

	void get_data();
	void print_data_vector();
};



hopfield::hopfield(int data_size_, int data_distribution_,int max_iter_) { 
	this->data_size = data_size_;
	this->data_distribution = data_distribution_;
	this->data = vector< gsl_matrix* >(0, NULL);
	this->original = vector<gsl_matrix*>(0, NULL);
	this->energia = vector<float>(0,0.0);
	this->cant_data = 0;
	this->f_data = gsl_matrix_alloc(this->data_size,this->data_size); // Inicializado a zero.
	gsl_matrix_set_zero(this->f_data);
	this->max_iter = max_iter_;
	
}


void hopfield::set_data_element(gsl_matrix* c_matrix) { // c_matrix = 1 x data_size
	gsl_matrix* transp = gsl_matrix_alloc(c_matrix->size2, c_matrix->size1); //transp = data_size x 1 
	gsl_matrix* f_matrix = gsl_matrix_alloc(c_matrix->size2, c_matrix->size2);
	
	gsl_matrix_transpose_memcpy(transp, c_matrix);

	gsl_matrix_multiplication(transp, c_matrix, f_matrix);
	this->data.push_back(f_matrix);
	this->cant_data++;
	this->original.push_back(c_matrix);//Unusable

	gsl_matrix_free(transp);
}

void hopfield::set_data_element_inverse(gsl_matrix* c_matrix) { // c_matrix = 1  x data_size
	//gsl_matrix* transp = gsl_matrix_alloc(c_matrix->size2, c_matrix->size1); //transp = data_size x 1

	//gsl_matrix_transpose_memcpy(transp, c_matrix);
	//this->data.push_back(transp);
	this->data.push_back(c_matrix); //At the end we get a complete list of data 
}


void hopfield::learn() {
	cout << "f_Data: " << this->f_data->size1 << " x " << this->f_data->size2 << "  data: " << data[0]->size1 << " x " << data[0]->size2 << endl;

	for (unsigned int i = 0; i < this->data.size(); i++) {
		gsl_matrix_add(this->f_data, this->data[i]);
		//gsl_my_matrix_addition(this->f_data, this->data[i]);
	}
	for (int i = 0; i < this->data_size; i++) {
		gsl_matrix_set(this->f_data, i, i, 0);
	}
	gsl_matrix_normalize(this->f_data);
	cout << "Learned Phase Complete" << endl;
}

void hopfield::learn_inverse() {
	cout << "Matriz Recibida: " << endl;
	for (int i = 0; i < this->data.size(); i++) {
		gsl_print_matrix(this->data[i]);
	}

	gsl_matrix* data_inverse = gsl_matrix_alloc(this->data_size, this->data.size()); //Save and inverse matrix of our actual data matrix
	gsl_matrix* inverse_complete = gsl_matrix_alloc(data_inverse->size2, data_inverse->size1); // Esta será la tranpuesta
	gsl_matrix* data_multiplication = gsl_matrix_alloc(data_inverse->size1, inverse_complete->size2); //Aca almacenamos la multiplicacion de ambas, el orden importa (original por tranpuesta) en la disposicion de espacios
	
	gsl_matrix_set_zero(data_inverse);
	gsl_print_matrix_information(data_inverse);

	for (unsigned int i = 0; i < this->data.size(); i++) {
		for (int j = 0; j < this->data[i]->size2; j++) {
			gsl_matrix_set(data_inverse, j, i, gsl_matrix_get(this->data[i], 0, j));
		}
	}

	cout << " Matriz a trabajar" << endl; //<-
	gsl_print_matrix(data_inverse); //<-
	this->data.clear(); //Nos deshacemos de la data en formato vector
	
	gsl_matrix_transpose_memcpy(inverse_complete, data_inverse);
		
	cout << " Matriz a trabajar transpuesta" << endl; //<-
	gsl_print_matrix(inverse_complete); //<-

	gsl_matrix_multiplication(data_inverse, inverse_complete, data_multiplication);
	cout << " Matriz multiplicada" << endl; //<-
	gsl_print_matrix(data_multiplication); //<-

	gsl_matrix* inverse_final = gsl_matrix_get_inverse(data_multiplication);
	cout << " Matriz Invertida" << endl; //<-
	gsl_print_matrix(inverse_final); //<-

}

void hopfield::recognize_v2(gsl_matrix* incoming) {
	cout << "Recognize v2" << endl;
	gsl_print_matrix_ascii(gsl_set_matrix_with_format(incoming, this->data_distribution, true));
	this	->recognize_dev_v2(incoming, 0);
}

//Asynchronous Update
void hopfield::recognize_dev_v2(gsl_matrix* incoming, int keeper) {
	if (keeper < this->max_iter) {
		//cout << "RECOGNIZE_DEV_V2_FLAG" << endl;
		int alter = get_random_integer_in_range(this->data_size);//Obtenemos la columna a actualizar

		gsl_matrix* w_row = gsl_matrix_alloc(1, this->f_data->size2);
		gsl_matrix_set_zero(w_row);
		gsl_my_matrix_int_get_row(w_row, this->f_data, alter);
		int result = gsl_matrix_point_product(incoming, w_row);

		gsl_matrix_free(w_row);

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
		gsl_matrix_free(incoming);
	}
}

void hopfield::recognize(gsl_matrix* incoming) {

	cout << "Elemento a reconocer: " << endl;
	gsl_print_matrix(gsl_set_matrix_with_format(incoming, this->data_distribution, true));

	this->recognize_dev(incoming, 0, 100);
}

//Pseudo inver method
/*
	- Agrupar la entrada basados en su transpuesta;
	- Aplicar: P * P^t
	-> P^t = (P^T * P) ^ {-1} * P^T;
*/

//Synchronous Update
void hopfield::recognize_dev(gsl_matrix* incoming, int current_iter, int energia) {
	if (current_iter < this->max_iter) {
		//Matrix of 1 x this->data_size dimensions.
		int inner_energia = 0;
		gsl_matrix* r_matrix = gsl_matrix_alloc(incoming->size1, incoming->size2);
		gsl_matrix_set_zero(r_matrix);

		gsl_matrix_multiplication(incoming, this->f_data, r_matrix);
		
		inner_energia = this->set_energia(incoming);
		this->funcion_1_reconocimiento(r_matrix);


		cout << "Incoming energy: " << energia << "  - InnerEnergy: " << inner_energia << endl;

		if ( (gsl_matrix_equal(r_matrix, incoming) != 1) or (energia != inner_energia) ) { //No son iguales 
			gsl_matrix_free(incoming);
			this->recognize_dev(r_matrix, current_iter + 1, inner_energia);
			//Free memory was here
			return;
		}
		else {
			cout << "Existen " << this->data.size() << " elementos." << endl;
			cout << "Resultado Final tras : " <<current_iter<<" iteracciones. "<< endl;
			gsl_print_matrix(r_matrix); cout << endl;
			gsl_print_matrix_ascii(gsl_set_matrix_with_format(r_matrix, this->data_distribution, true));
			gsl_matrix_free(r_matrix);
			gsl_matrix_free(incoming);
			return;
		}
	}
	else {
		cout << "Se ha superado el maximo de iteracciones" << endl;
		cout << "Resultado Final: " << endl; gsl_print_matrix_ascii(gsl_set_matrix_with_format(incoming, this->data_distribution, true));
		gsl_matrix_free(incoming);
	}
}

bool hopfield::review(gsl_matrix* incoming) {
	for (unsigned int i = 0; i < this->original.size(); i++) {
		if (gsl_matrix_equal(incoming, this->original[i]) == 1) {
			return true;
		}
	}
	return false;
}

void hopfield::funcion_1_reconocimiento(gsl_matrix* incoming) {
	//Must be a matrix of 1 x this->data_size dimensions. But in case we do it for general matrix.
	for (int i = 0; i < incoming->size1; i++) {
		for (int j = 0; j < incoming->size2; j++) {
			if (gsl_matrix_get(incoming, i, j) >= 0) {
				gsl_matrix_set(incoming, i, j, 1);
			}
			else {
				gsl_matrix_set(incoming, i, j, -1);
			}
		}
	}

}

bool hopfield::funcion_2_reconocimiento(gsl_matrix* incoming, int obtained, int pos) {
	if (obtained > -5) {
		obtained = 1;
		if (gsl_matrix_get(incoming, 0, pos) == obtained) {
			return true;
		}
		else {
			gsl_matrix_set(incoming, 0, pos, obtained);
			return false;
		}
	}
	else{
		obtained = -1;
		if (gsl_matrix_get(incoming, 0, pos) == obtained) {
			return true;
		}
		else {
			gsl_matrix_set(incoming, 0, pos, obtained);
			return false;
		}
	}
}

//This function should be executed after learn() function
int hopfield::set_energia(gsl_matrix* incoming) {
	//incoming 1xdata_size
	int answer = 0;
	for (int i = 0; i < this->f_data->size1; i++) {
		for (int j = 0; j < this->f_data->size2; j++) {
			answer += (gsl_matrix_get(this->f_data, i, j) + gsl_matrix_get(incoming, 0, i) + gsl_matrix_get(incoming, 0, j) );
		}
	}
	answer = -1 * (answer / 2);
	return answer;
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