// ListaParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include "c_list.h"
#include "c_list_1.h"
#include "c_list_2.h"
#include "c_list_3.h"
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <mutex>
#include <ctime>
using namespace std;

mutex mtx;
const int hebras_number = 10;
const int cantidad_datos = 1000;

int main(){
	c_list_1 lista_1;
	c_list_2 lista_2;
	c_list_3 lista_3;

	thread list_thread[hebras_number];
	unsigned t0, t1;

	t0 = clock();

	for (int i = 0; i < cantidad_datos; i++) {

		for (int j = 0; j < hebras_number; j++) {
			list_thread[j] = thread(&c_list_1::insert, &lista_1, rand()%100);
		}
		for (int j = 0; j < hebras_number; j++) {
			list_thread[j].join();
		}
	}

	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Tiempo de Ejecucion 1 " << time << endl;

	t0 = clock();
	for (int i = 0; i < cantidad_datos; i++) {

		for (int j = 0; j < hebras_number; j++) {
			list_thread[j] = thread(&c_list_2::insert, &lista_2, rand() % 100);
		}
		for (int j = 0; j < hebras_number; j++) {
			list_thread[j].join();
		}
	}
	t1 = clock();
	time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Tiempo de ejecucion 2 " << time << endl;

	t0 = clock();
	for (int i = 0; i < cantidad_datos; i++) {

		for (int j = 0; j < hebras_number; j++) {
			list_thread[j] = thread(&c_list_3::insert, &lista_3, rand() % 100);
		}
		for (int j = 0; j < hebras_number; j++) {
			list_thread[j].join();
		}
	}
	t1 = clock();
	time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Tiempo de ejecucion 3 " << time << endl;

}



// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln


