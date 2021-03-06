// MatrixVector.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// omp_parallel.cpp
// compile with: /openmp

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <vector>
#include <time.h>
#include <ctime>

using namespace std;

template<class T>
void fill_vector(vector<T>&, int);

template<class T>
void fill_matrix(vector< vector<T> >&, int, int);

int main()
{
	int n;
	int m;
	int thread_count;
	int i = 0;
	int j = 0;
	cout << "Longitud 1 de vector: " << endl;
	cin >> n;
	cout << "Longitud 2 de vector: " << endl;
	cin >> m;

	cout << "Cantidad de threads: " << endl;
	cin >> thread_count;

	vector< vector <float> > A(0, vector<float>(0, 0)); //Matrix
	vector<float> x(0, 0); //Vector
	vector<float> y(n, 0); //Resultado
	unsigned t0;
	unsigned t1;

	fill_vector(x, m);
	fill_matrix(A, n, m);

	t0 = clock();
#	pragma omp parallel for num_threads(thread_count) \
	default(none) shared(A, x, y, m, n) private(i, j)
		for (i = 0; i < n; i++) {
			y[i] = 0.0;
			for (j = 0; j < m; j++) {
				y[i] += A[i][j] * x[j];
			}
		}
	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);

	cout << "Tiempo de Ejecucion: " << time << endl;
}

template<class T>
void fill_vector(vector<T>& coming, int value) {
	for (int i = 0; i < value; i++) {
		coming.push_back((T)(rand() % 100));
	}
}

template <class T>
void fill_matrix(vector< vector<T> >& coming, int value, int value2) {
	for (int i = 0; i < value; i++) {
		vector<T> tempo_vec(0, 0);
		for (int j = 0; j < value2; j++) {
			tempo_vec.push_back((T)(rand() % 100));
		}
		coming.push_back(tempo_vec);
	}
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
