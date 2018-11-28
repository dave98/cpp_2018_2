#ifndef  SOMEFUNCTIONS_H
#define SOMEFUNCTIONS_H

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_linalg.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void gsl_print_matrix_information(gsl_matrix* incoming) {
	cout << "Size1: " << incoming->size1 << " - " << "Size2: "<< incoming->size2 << endl;
	cout << "Size1 se asocia con Y mientras que Size2 con X." << endl;
}

void gsl_print_matrix(gsl_matrix* incoming){
	for (int i = 0; i < incoming->size1; i++) {
		for (int j = 0; j < incoming->size2; j++) {
			//cout << incoming->data[i*incoming->size1 + j] << " ";
			cout << gsl_matrix_get(incoming, i, j) << " ";
		}
		cout << endl;
	}
}

void gsl_print_matrix_ascii(gsl_matrix* incoming) {
	for (int i = 0; i < incoming->size1; i++) {
		for (int j = 0; j < incoming->size2; j++) {
			//cout << incoming->data[i*incoming->size1 + j] << " ";
			if (gsl_matrix_get(incoming, i, j) == 0) {
				//cout << "  ";
				cout << " ";
			}
			else {
				//cout << (char)219<<(char)219;
				cout << (char)219;
			}
		}
		cout << endl;
	}
}


void gsl_set_random_values(gsl_matrix* incoming) {
	for (int i = 0; i < incoming->size1; i++) {
		for (int j = 0; j < incoming->size2; j++) {
			int generated_random = rand() % 2;
			if (generated_random == 0) { generated_random = -1; }
			gsl_matrix_set(incoming, i, j, generated_random);
		}
	}
}



int get_random_integer_in_range(int range) {
	int answer = rand() % range;
	//cout << "Generated Random: " << answer << endl;
	return answer;
}



void gsl_my_matrix_addition(gsl_matrix* a, gsl_matrix* b) {
	//Must have the same dimensions
	for (int i = 0; i < a->size1; i++) {
		for (int j = 0; j < a->size2; j++) {
			gsl_matrix_set(a, i, j, (( gsl_matrix_get(a, i, j) + gsl_matrix_get(b, i, j) )) );
		}
	}
	return;
}


void gsl_matrix_normalize(gsl_matrix* incoming) {
	//Normalize double values to int  constants.
	for (int i = 0; i < incoming->size1; i++){
		for (int j = 0; j < incoming->size2; j++) {
			//gsl_matrix_set(incoming, i, j, gsl_matrix_get(incoming, i, j));
			if (gsl_matrix_get(incoming, i, j) < 0) {
				gsl_matrix_set(incoming, i, j, -1);
			}
			else {
				gsl_matrix_set(incoming, i, j, 1);
			}
		}
	}
}

gsl_matrix* gsl_matrix_get_inverse(gsl_matrix* incoming) {
	gsl_permutation* p = gsl_permutation_alloc(incoming->size1);
	int s;

	gsl_linalg_LU_decomp(incoming, p, &s);
	gsl_matrix* inver = gsl_matrix_alloc(incoming->size1, incoming->size2);
	gsl_matrix_set_zero(inver);
	gsl_linalg_LU_invert(incoming, p, inver);

	gsl_permutation_free(p);
	return inver;

}

void gsl_matrix_my_memcpy(gsl_matrix* a, gsl_matrix* b) {
	//a->b
	//Must be the same dimensions
	for (int i = 0; i < a->size1; i++) {
		for (int j = 0; j < a->size2; j++) {
			gsl_matrix_set(b, i, j, gsl_matrix_get(a, i, j));
		}
	}
}

//Dimensions must be equal in product
gsl_matrix* gsl_set_matrix_with_format(gsl_matrix* a, int limit_format, bool custom_format) {
	if ((a->size1 * a->size2) != (limit_format*limit_format)) {
		cout << "Formato inadecuado de matrices, perdida de datos" << endl;
		gsl_matrix* answer = gsl_matrix_alloc(limit_format, limit_format);
		return answer;
	}

	else {
		gsl_matrix* answer = gsl_matrix_alloc(limit_format, limit_format);
		int iterator_i = 0;
		int iterator_j = 0;
		int temp = 0;

		for (int i = 0; i < limit_format; i++) {
			for (int j = 0; j < limit_format; j++) {
				temp = gsl_matrix_get(a, iterator_i, iterator_j);
				if (custom_format) {
					if (temp < 1) { temp = 0; }
				}
				gsl_matrix_set(answer, i, j, temp);

				iterator_i++;
				if (iterator_i >= a->size1) {
					iterator_j++; iterator_i = 0;
				}

			}
		}
		return answer;
	}
}

void gsl_matrix_multiplication(gsl_matrix* a, gsl_matrix* b, gsl_matrix* c) {
	if (a->size2 != b->size1) {
		cout << "No se pudo realizar la multiplicacion" << endl;
	}
	else {
		gsl_matrix_set_zero(c);
		for (int i = 0; i < a->size1; i++) {
			for (int j = 0; j < b->size2; j++) {

				for (int k = 0; k < a->size2; k++) {
					gsl_matrix_set(c, i, j, gsl_matrix_get(c, i, j) + (gsl_matrix_get(a, i, k) * gsl_matrix_get(b, k, j)) );
				}
			}
		}
		return;
	}
}


//Uncomplete function
int gsl_matrix_point_product(gsl_matrix* a, gsl_matrix* b){
	if ((a->size1 != 1) or (b->size1 != 1)) {
		cout << "Point products problems" << endl;
	}

	//cout << "Point product" <<" ["<<a->size1<<"-"<<a->size2<<"]"<<" ["<<b->size1<<"-"<<b->size2<<"]"<< endl;
	int answer = 0;
	//a->size2 must be equal to b->size2
	for (int i = 0; i < a->size2; i++) {
		answer += (gsl_matrix_get(a, 0, i) * gsl_matrix_get(b, 0, i));
	}
	return answer;
}

void gsl_my_matrix_int_get_col(gsl_matrix* dest, gsl_matrix* src, int pos) {
	if (dest->size2 != src->size1) {
		cout << "Posible error al adquirir fila" << endl;
	}


	for (int i = 0; i < src->size1; i++) {
		gsl_matrix_set(dest, 0, i, gsl_matrix_get(src, i, pos));
	}
	return;
}


void gsl_my_matrix_int_get_row(gsl_matrix* dest, gsl_matrix* src, int pos) {
	if (dest->size2 != src->size2) {
		cout << "Posible error al adquirir fila" << endl;
	}

	for (int i = 0; i < src->size2; i++) {
		gsl_matrix_set(dest, 0, i, gsl_matrix_get(src, pos, i));
	}
	return;
}

#endif // ! SOMEFUNCTIONS_H
