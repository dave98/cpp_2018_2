#include <iostream>
#include <vector>
#include <thread>
#include "function.h"

using namespace std;

void process(vector<int>, vector<int>, int, vector<int>&);


int main(){
	int n = 20000;
	int m = 20000;
	//cin>>n;
	//cin>>m;
	
	vector< vector<int> > matrix_;
	vector< int > vec_;
	vector< int > res_ = vector<int>(n, 0);

	set_matrix(matrix_, n, m);
	set_vector(vec_, m);

	for(unsigned int i = 0; i < matrix_.size(); i++){
		thread(process, matrix_[i], vec_, i, std::ref(res_)).detach();
	}

	//print_matrix(matrix_);
	//print_vector(vec_);
	//print_vector(res_);

	return 0;
}

void process(vector<int> _m, vector<int> _v, int index, vector<int>& _r){
	//El tamaño de _m y _v debe ser el mismo
	int local_value = 0;
	for(unsigned int i = 0; i < _m.size(); i++){
		local_value += _m[i] * _v[i];
	}
	_r[index] = local_value;
}
