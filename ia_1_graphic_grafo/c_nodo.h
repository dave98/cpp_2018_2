#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include <vector>

using namespace std;

class c_nodo{
public:
  float x;
  float y;
  vector<int> l_adyacentes;

  c_nodo();
  ~c_nodo();
  
};

c_nodo::c_nodo(){
  this->x = 0;
  this->y = 0;
  this->l_adyacentes = vector<int>(0,0);
}

c_nodo::~c_nodo(){}



#endif
