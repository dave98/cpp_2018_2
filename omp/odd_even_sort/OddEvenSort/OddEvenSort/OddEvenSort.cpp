// OddEvenSort.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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

template <class T>
void print_vector(vector<T>);

template<class T>
void fill_vector(vector<T>&, int);

int main()
{
	srand(time(NULL));

	int n = 0; //Longitud del array
	int tmp = 0; //valor temporal
	int thread_count = 0; //Cantidad de Threads a utilizar
	int phase = 0;
	vector<int> a;

	unsigned t0;
	unsigned t1;

	std::cout << "Tamaño del array: " << endl;
	cin >> n;

	std::cout << "Cantidad de Threads: " << endl;
	cin >> thread_count;

	fill_vector(a, n);
	//print_vector(a);

	t0 = clock();
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
#			pragma omp parallel for num_threads(thread_count) \
			default(none) shared(a, n) private(i, tmp);

			for (int j = 1; j < n; j += 2) {
				if (a[j - 1] > a[j]) {
					tmp = a[j - 1];
					a[j - 1] = a[j];
					a[j] = tmp;
				}
			}
		}
		else {
#			pragma omp parallel for num_threads(thread_count) \
			default(none) shared(a, n) private(i, tmp);

			for (int j = 1; j < n - 1; j += 2) {
				if (a[j] > a[j + 1]) {
					tmp = a[j + 1];
					a[j + 1] = a[j];
					a[j] = tmp;
				}
			}
		}
	}
	t1 = clock();
	double time = (double(t1 - t0)/ CLOCKS_PER_SEC);
	//print_vector(a);
	std::cout << "Tiempo de ejecucion: " << time << endl;


	std::cout << "Segundo Metodo: " << endl<<endl;
	//Segunda Implementacion
	a.clear();
	fill_vector(a, n);
	//print_vector(a);

#	pragma omp parallel num_threads(thread_count) \
	default(none) shared(a, n) private(i, tmp, phase)

	t0 = clock();
	for (phase = 0; phase < n; phase++) {
		if (phase % 2 == 0) {
			#pragma omp for
			for (int i = 1; i < n; i += 2) {
				if (a[i - 1] > a[i]) {
					tmp = a[i - 1];
					a[i - 1] = a[i];
					a[i] = tmp;
				}
			}
		}
		else {
			#pragma omp for
			for (int i = 1; i < n-1; i += 2) {
				if (a[i] > a[i + 1]) {
					tmp = a[i + 1];
					a[i + 1] = a[i];
					a[i] = tmp;
				}
			}
		}
	}
	t1 = clock();
	time = (double(t1 - t0) / CLOCKS_PER_SEC);

	//print_vector(a);
	std::cout << "Tiempo de ejecucion: " << time << endl;
}

template <class T>
void print_vector(vector<T> coming) {
	for (unsigned int i = 0; i < coming.size(); i++) {
		cout << coming[i] << " ";
	}
	cout << endl << endl;
}

template<class T>
void fill_vector(vector<T>& coming, int value) {
	for (int i = 0; i < value; i++) {
		coming.push_back(rand()%100);
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
