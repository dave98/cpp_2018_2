// AntColonySystem.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>

#include <iostream>
#include "create_graph.h"
#include "acs.h"


int main()
{
	std::vector<CoordDouble> nodes;
	std::string name_file = "d198.tsp";
	read_tsp_file(nodes, name_file);

	/*
	for (int i = 0; i < nodes.size(); ++i)
	{
		std::cout << "Node " << i << ": x = " << nodes[i].x << ", y = " << nodes[i].y << "\n";
	}*/

	int num_iter = 1000;
	int num_ants = 30;
	double beta = 2.0;
	double q0 = 0.9;
	double alpha = 0.1;
	double rho = 0.1;
	std::vector<int> global_best_route;
	double cost_global_best_route;

	//el numero de ants tiene que ser menor o igual al numero de nodos/ciudades
	ant_colony_system(nodes, num_iter, num_ants, beta, q0, alpha, rho, global_best_route, cost_global_best_route);

	for (int i = 0; i < global_best_route.size(); ++i)
	{
		std::cout << global_best_route[i] << " ";
	}
	std::cout << "\n";
	std::cout << "Costo = " << cost_global_best_route << "\n";

	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
