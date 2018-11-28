
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <iostream>
#include "matrix.h"
#include <chrono>


using namespace std;

void print_matrix(int*, int, int);

int main() {
	int width = 32;
	float block = 32;

	unsigned ntotal = width * width;

	int *h_m = new int[ntotal];
	int *h_n = new int[ntotal];
	int *h_p = new int[ntotal];
	int *h_r = new int[ntotal];

	unsigned i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < width; j++) {
			h_m[(i*width) + j] = j;
			h_n[(i*width) + j] = j;
			h_p[(i*width) + j] = 0;
			h_r[(i*width) + j] = 0;
		}
	}

	cout << "Matriz 1:" << endl;
	print_matrix(h_m, width, width); cout << endl;
	cout << "Matriz 2:" << endl;
	print_matrix(h_n, width, width); cout << endl;

	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	cout << "Multiplicacion Normal" << endl;
	square_matrix_mult(h_m, h_n, h_p, width, block, 'n');
	//high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//auto duration1 = duration_cast<microseconds>(t2 - t1).count();
	print_matrix(h_p, width, width); cout << endl;

	cout << "Multiplicacion Tiles" << endl;
	square_matrix_mult(h_m, h_n, h_r, width, block, 't');
	print_matrix(h_r, width, width); cout << endl;

	delete h_m;
	delete h_n;
	delete h_p;
	delete h_r;

	return 0;
}

void print_matrix(int* m_x, int fila, int columna) {
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < columna; j++) {
			cout << m_x[i*columna + j] << " ";
		}
		cout << endl;
	}
}

