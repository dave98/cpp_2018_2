#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <vector>

using namespace std;

int MAX_VALUE = 10;


void set_matrix(vector<vector<int>>& _matrix, int a, int b){
	_matrix = vector<vector<int>>(a, vector<int>(b, rand()%MAX_VALUE ));
}

void set_vector(vector<int>& _vec, int a){
	_vec = vector<int>(a, rand()%MAX_VALUE);
}


void print_matrix(vector<vector<int>> _a){
	for(unsigned int i = 0; i < _a.size(); i++){
		for(unsigned int j = 0; j < _a[0].size(); j++){
			cout<<_a[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void print_vector(vector<int> _a){
	for(unsigned int i = 0; i < _a.size(); i++){
		cout<<_a[i]<<" ";
	}
	cout<<endl;
	cout<<endl;
}


#endif