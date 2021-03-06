#include "pch.h"
#include <iostream>
#include <gsl/gsl_matrix.h>
#include "hopfield.h"
#include "SomeFunctions.h"
#include "DataProcess.h"


using namespace std;

int DATA_NUMBER = 10;
int DATA_SIZE = 25;
int DATA_DISTRIBUTION = 5; // Raiz cuadraada de Data_Size
int MAX_ITERACCIONES = 50;
string RUTA = "data55.txt";
string PRUEBA = "Prueba3.txt";

int main() {
	vector<gsl_matrix*> learned_data;
	hopfield red_a(DATA_SIZE, DATA_DISTRIBUTION ,MAX_ITERACCIONES);

	DataProcess lector(DATA_NUMBER, DATA_SIZE, DATA_DISTRIBUTION, RUTA);
	learned_data = lector.read_data();

	//Ingresamos el texto plano de las entradas 
	cout << "External: " << endl;
	for (unsigned int i = 0; i < learned_data.size(); i++) {
		//gsl_print_matrix(learned_data[i]);
		//gsl_print_matrix(gsl_set_matrix_with_format(learned_data[i], DATA_DISTRIBUTION, false)); cout << endl;
		//->red_a.set_data_element(learned_data[i]);
		red_a.set_data_element_inverse(learned_data[i]);
	}

	red_a.learn_inverse();
	//->red_a.learn();
	//red_a.set_energia();

	//for (unsigned int i = 0; i < learned_data.size(); i++) {
		//gsl_print_matrix_ascii(gsl_set_matrix_with_format(learned_data[i], DATA_DISTRIBUTION, true)); cout << endl;
		//->gsl_print_matrix_ascii(gsl_set_matrix_with_format(red_a.original[i], DATA_DISTRIBUTION, true)); cout << endl;
	//}

	//->cout << "Recibiendo nuevo elemento: " << endl;
	//gsl_print_matrix(lector.get_element(PRUEBA));
	//->red_a.recognize(lector.get_element(PRUEBA, false));
	//red_a.recognize_v2(lector.get_element(PRUEBA, true));
	return 0;
}