// vs_arboles_desicion.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#include "Dataset_Reader.h"
#include "c_tree.h"

//Datasets;
//Bands: 512 datos, 39 atributos  -> Not ready
//Nurse: 12960 datos, 8 atributos -> Ready
int main()
{
	Dataset_Reader<9, 12960> a_read("nurse.txt");
	a_read.read_data();
	//a_read.show_data();

	//vector< vector <string> > g;// = a_read.get_data();
	/*g = a_read.get_data();
	for (int i = 0; i < g.size(); i++) {
		for (int j = 0; j < g[0].size(); j++) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}*/

	c_tree a_tree(a_read.get_data(), 8, 0);//0 to size-1

	//a_tree.print_data();
	a_tree.main_iteraction_v2();
}
