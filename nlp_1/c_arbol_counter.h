#ifndef C_ARBOL_COUNTER_H
#define C_ARBOL_COUNTER_H

#include <iostream>
#include <vector>
#include "c_nodo_counter.h"

using namespace std;

template <class T>
class c_arbol_counter{
public:
    c_nodo_counter<T>* head;

    c_arbol_counter();
    ~c_arbol_counter();

    void insert(T);
    bool buscar(T);
    void show_content();
};

template <class T>
c_arbol_counter<T>::c_arbol_counter(){
  this->head = NULL;
}

template <class T>
c_arbol_counter<T>::~c_arbol_counter(){}

template <class T>
void c_arbol_counter<T>::insert(T incoming){
  c_nodo_counter<T>** chariot = &this->head;
  while(*chariot){
    if((*chariot)->value == incoming){
      (*chariot)->add_rept();
      return;
    }
    else{
      chariot = &((*chariot)->hijos[(*chariot)->value < incoming]);
    }
  }

  (*chariot) = new c_nodo_counter<T>(incoming);
  cout<<"Inserted"<<endl;
}

template <class T>
bool c_arbol_counter<T>::buscar(T incoming){
  c_nodo_counter<T>** chariot = &this->head;
  while(*chariot){
    if((*chariot)->value == incoming){
      cout<<"Encontrado "<<(*chariot)->times<<" veces."<<endl;
      return true;
    }
    else{
      chariot = &((*chariot)->hijos[(*chariot)->value < incoming]);
    }
  }
  cout<<"No Encontrado"<<endl;
  return false;
}

template <class T>
void c_arbol_counter<T>::show_content(){
  vector<c_nodo_counter<T>*> buss = vector<c_nodo_counter<T>*>(0, NULL);
}

#endif
