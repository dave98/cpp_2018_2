#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
void print_list(vector<T> list_v){
  for(unsigned int i = 0; i < list_v.size(); i++){
    cout<<list_v[i]<<endl;
  }
  //cout<<endl;
}

#endif
