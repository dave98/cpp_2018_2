// vs_cs_project.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "c_graph.h"

using namespace std;

int main()
{
	c_graph a(1580);
	a.set_nodes();
	a.sybil_analyze();
}



