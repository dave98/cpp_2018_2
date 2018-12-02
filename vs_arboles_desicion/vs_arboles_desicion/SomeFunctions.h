#ifndef SOMEFUNCTIONS_H
#define SOMEFUNCTIONS_H

#include<iostream>
#include<vector>

using namespace std;

template<class T>
void print_vector(vector<T> incoming) {
	for (unsigned int i = 0; i < incoming.size(); i++) {
		cout << incoming[i] << " ";
	}
	cout << endl;
}

template<class T>
void print_matrix(vector< vector<T> > incoming) {
	for (unsigned int i = 0; i < incoming.size(); i++) {
		for (unsigned int j = 0; j < incoming[0].size(); j++) {
			cout << incoming[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template<class T>
int get_max_value_position_in_vector(vector<T> incoming) {
	T max_value = incoming[0];
	int answer = 0;
	for (unsigned int i = 1; i < incoming.size(); i++) {
		if (incoming[i] > max_value) {
			answer = i;
			max_value = incoming[i];
		}
	}
	return answer;
}

#endif