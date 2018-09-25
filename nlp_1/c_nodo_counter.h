#ifndef C_NODO_COUNTER_H
#define C_NODO_COUNTER_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class c_nodo_counter{
public:
  T value;
  int times;
  c_nodo_counter<T>* hijos[2];

  c_nodo_counter(T);
  ~c_nodo_counter();

  void add_rept();
};

template <class T>
c_nodo_counter<T>::c_nodo_counter(T value_){
  this->value = value_;
  this->times = 1;

  this->hijos[0] = NULL;
  this->hijos[1] = NULL;
}

template <class T>
c_nodo_counter<T>::~c_nodo_counter(){}


template <class T>
void c_nodo_counter<T>::add_rept(){
  this->times++;
}

#endif
