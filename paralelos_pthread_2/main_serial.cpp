#include <iostream>
#include <vector>
#include "function.h"

using namespace std;


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
		int local_val = 0;
		for(unsigned int j = 0; j < matrix_[i].size(); j++){
			local_val += matrix_[i][j] * vec_[j];
		}
		res_[i] = local_val;
	}

	//print_matrix(matrix_);
	//print_vector(vec_);
	//print_vector(res_);

	return 0;
}