#ifndef C_TREE_H
#define C_TREE_H

#include <iostream>
#include <vector>
#include <math.h>
#include "c_nodo.h"
#include "SomeFunctions.h"

using namespace std;

class c_tree
{
public:
	vector< vector <string>> data;
	vector< vector< string > > extracted_atributes;
	vector< string > charateristic_atributes;
	vector< vector<int> > numeric_atributes;

	int analyze_column; // from 0 - data.size()-1;
	int start_column; //Must be diferent from analyze_column
	c_nodo* head;

	c_tree(vector< vector <string> >, int, int);
	void main_iteraction();
	void secondary_iteraction(vector<int>, c_nodo*);
		long double get_initial_entropia(int);
		long double get_initial_entropia_c(int, vector<int>);
		long double get_proporcion(string, int, vector<int>);
		long double get_general_entropia_c(string, int, int, vector<int>);
		vector<int> get_position_according_to_value(string, int, vector<int>);

	void main_iteraction_v2();
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

void c_tree::main_iteraction_v2() {
	this->extracted_atributes = vector<vector<string>>(this->data[0].size(), vector<string>(0, ""));
	this->numeric_atributes = vector<vector<int>>(this->data[0].size(), vector<int>(0, 0));

	for (unsigned int i = 0; i < this->data[0].size(); i++) {
		this->extracted_atributes[i].push_back(this->data[0][i]);
		this->numeric_atributes[i].push_back(0);//No es necesario  que sea 1 puesto que la iteraccion siguiente la hemos empezado con 0
	}//++

	for (unsigned int i = 0; i < this->data.size(); i++) {
		for (unsigned int j = 0; j < this->data[0].size(); j++) {
			bool change = false;

			for (unsigned int k = 0; k < this->extracted_atributes[j].size(); k++) {
				if (this->data[i][j] == this->extracted_atributes[j][k]) {
					change = true;
					this->numeric_atributes[j][k] += 1;
				}
				else {
				}
			}
			if (!change) {
				this->extracted_atributes[j].push_back(this->data[i][j]);
				this->numeric_atributes[j].push_back(1);
			}
		}
	}

	for (unsigned int i = 0; i < extracted_atributes.size(); i++) {
		cout << i << endl;
		for (unsigned int j = 0; j < extracted_atributes[i].size(); j++) {
			cout << extracted_atributes[i][j] << " -> " << numeric_atributes[i][j] << endl;
		}
	}
	//Hasta acá tenemos todos los datos clasificados en el arbol
	vector<int> for_work = vector<int>(this->data.size(), 0);
	for (unsigned int i = 0; i < this->data.size(); i++) {
		for_work[i] = i;
	}

	this->secondary_iteraction(for_work, this->head);
}

//data index indica los datos a trabajar a partir de este punto
//Secuencia iterativa

void c_tree::secondary_iteraction(vector<int> data_index, c_nodo* place_to_work) {
	if (this->head == NULL) {//Si no tenemos nada en la cabeza procedemos a insertar ela division inicial
		long double entropia_inicial = this->get_initial_entropia(this->analyze_column);
		vector<int> used_index = vector<int>(0, 0);
		vector<long double> used_index_data = vector<long double>(0, 0.0);
		//Obteniendo el restro de entropias:

		for (unsigned int i = 0; i < this->numeric_atributes.size(); i++) {
			if (i != this->analyze_column) {
				long double rest_operation = 0.0;
				//Empezamos a recorrer los ATRIBUTOS
				for (unsigned int j = 0; j < this->numeric_atributes[i].size(); j++) { //Iterando sobre los valores de cada atributo
					rest_operation += this->get_proporcion(this->extracted_atributes[i][j], i, data_index) * this->get_general_entropia_c(this->extracted_atributes[i][j], i, this->analyze_column, data_index);
				}
				rest_operation = entropia_inicial + rest_operation;
				used_index.push_back(i); used_index_data.push_back(rest_operation);
			}
		}

		int max_value_founded = get_max_value_position_in_vector(used_index_data);
		//print_vector(used_index); print_vector(used_index_data);
		//cout << "Mayor: " << used_index_data[get_max_value_position_in_vector(used_index_data)] << " Indice: "<< get_max_value_position_in_vector(used_index_data) << endl;

		for (unsigned int i = 0; i < this->extracted_atributes[max_value_founded].size(); i++) {
			cout << i << " - " << this->extracted_atributes[max_value_founded][i] << endl;
		}
		//crear cabeza.
		this->head = new c_nodo("__head__", -1, data_index); //Identificación unica de la cabeza.
		//Añadiendo hijos:
		for (unsigned int i = 0; i < this->extracted_atributes[max_value_founded].size(); i++) {
			//cout << extracted_atributes[max_value_founded][i] << endl;
			vector<int> values_to_checked = this->get_position_according_to_value(this->extracted_atributes[max_value_founded][i], i, data_index);
			c_nodo* temp = new c_nodo(this->extracted_atributes[max_value_founded][i], max_value_founded, values_to_checked);
			this->head->hijos.push_back(temp);
		}

		//this->head->print_nodo_data();
		//Ahora nos aseguramos de recorrer los hijos,

	}
}

//Creo que en lugar de buscar en toda la matriz, solo podría mandar un vector con las posibles ubicaciones
vector<int> c_tree::get_position_according_to_value(string word, int column, vector<int> checked_values) {
	//checked values just work for rows
	vector<int> answer;
	for (unsigned int i = 0; i < checked_values.size(); i++) {
		if (word == this->data[checked_values[i]][column]) {
			answer.push_back(i);
		}
	}
	return answer;
}


long double c_tree::get_initial_entropia(int column) {//Indica en base a que voy a sacar la entropia inicial
	long double answer = 0.0;
	//cout << "Entropy Main Column: " << endl;
	for (unsigned int i = 0; i < this->numeric_atributes[column].size(); i++) { //Utilizamos la clasificación hecha inicialmente (todos los datos)
		long double temp = -1.0* ((long double)this->numeric_atributes[column][i] / (long double)this->data.size());
		cout << i << ": " << temp << endl;
		if (temp == (long double)0) {
			//cout << "Returning intial entropy out of order in initial entropy" << endl;
			answer = (long double)0;
			return answer;
		}
		else {
			answer += (temp)* log2l(-temp);
		}
	}
	return answer;
}

long double c_tree::get_initial_entropia_c(int column, vector<int> checked_values) {//En base a que columnas y filas debo analizar la entropia
	long double answer = 0.0;
	vector<int> local_numeric_atributes = vector<int>(this->extracted_atributes[column].size(), 0);//Crea en base al numero de caracteristicas en la columna señalada
	for (unsigned int i = 0; i < checked_values.size(); i++) {
		for (unsigned int j = 0; j < local_numeric_atributes.size(); i++) {
			if (this->extracted_atributes[column][j] == this->data[checked_values[i]][column]) {
				local_numeric_atributes[j] += 1;
			}
		}
	}
	//Hasta obtenemos el universo en base a los datos cedidos por checked_Values
	//***
	//Primer dato de este vector es la primera caracteristica en base base a extracted_atribute[column]
	for (unsigned int i = 0; i < local_numeric_atributes.size(); i++) {
		//long double temp = -1.0* ((long double)this->numeric_atributes[column][i] / (long double)this->data.size());
		long double temp = -1.0 *  ((long double)local_numeric_atributes[i] / checked_values.size());
		cout << i << ": " << temp << endl;
		if (temp == (long double)0) {
			cout << "Returning intial entropy 2 out of order" << endl;
			answer = (long double)0;
			return answer;
		}
		else {
			answer += (temp)* log2l(-temp);
		}
	}
	return answer;
}

long double c_tree::get_proporcion(string word, int column, vector<int> checked_values) {
	long double answer = 0.0;
	for (unsigned int i = 0; i < checked_values.size(); i++) {
		if (word == this->data[checked_values[i]][column]) {
			answer += 1;
		}
	}
	answer = answer / checked_values.size();
	return answer;
}

long double c_tree::get_general_entropia_c(string word, int colum_reference, int column_result, vector<int> checked_values) {
	//Column result should be this->analyze column
	long double answer = 0.0;
	vector<int> local_numeric_main_atribute = vector<int>(this->numeric_atributes[column_result].size(), 0);
	for (unsigned int i = 0; i < checked_values.size(); i++) {
		if (word == this->data[checked_values[i]][colum_reference]) {
			for (unsigned int j = 0; j < local_numeric_main_atribute.size(); j++) {
				if (this->data[checked_values[i]][column_result] == this->extracted_atributes[column_result][j]) {
					local_numeric_main_atribute[j] += 1;
				}
			}
		}
	}
	//Hasta terminamos la clasificacion
	for (unsigned int j = 0; j < local_numeric_main_atribute.size(); j++) {
		long double  temp = -1.0 * ((long double)local_numeric_main_atribute[j] / (long double)checked_values.size());
		if (temp == (long double)0) {
			cout << "Returning general entropy out of order" << endl;
			answer = (long double)0;
			return answer;
		}
		else {
			answer += (temp)* log2l(-temp);
		}
	} 
	return answer;
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
	static int iter = 0;
	long double answer = 0.0;
	for (unsigned int i = 0; i < this->numeric_atributes[atributo].size(); i++) {
		long double proporcion = -1.0 * ((long double)this->numeric_atributes[atributo][i] / (long double)this->data.size());
		cout <<" Proporcion: "<<iter<<" - "<< i << " : " << proporcion << endl;
		proporcion = proporcion * this->get_entropia_dependent(this->extracted_atributes[atributo][i], this->numeric_atributes[atributo][i], atributo);
		answer += proporcion;
	}
	iter++;
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
	cout << "Entropy Main Column: " << endl;
	for (unsigned int i = 0; i < this->numeric_atributes[col].size(); i++) {
		long double temp = -1.0* ((long double)this->numeric_atributes[col][i] / (long double)this->data.size());
		cout << i << ": " << temp << endl;
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