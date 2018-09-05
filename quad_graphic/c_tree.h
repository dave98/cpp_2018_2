#ifndef C_TREE_H
#define C_TREE_H

#include <iostream>
#include "c_nodo.h"
#include "c_point.h"
#include "vector"

using namespace std;

class c_tree{
public:
  c_nodo* head;
  int limit_per_area;
  float range_1;
  float range_2;
  c_point point_range_1;//Debo inicializarlos
  c_point point_range_2;
  int numero_puntos;

  c_tree(int);
  ~c_tree();

  void insert(float, float);
  void find(float, float);
  int get_region();
  void initial_region_setter(c_point, c_point);//Enable if my tree doesn't have any point
};

c_tree::c_tree(int _limit){
  this->head = NULL;
  this->limit_per_area = _limit;
  this->range_1 = 0;//-200.0; //Teacher's decision
  this->range_2 = 1000.0;//200.0; //It's unusable 'cause x and y maust be the same numbers and that's wrong
  this->numero_puntos = 0;
  this->point_range_1 = c_point(0, 0);//Default value for my tree
  this->point_range_2 = c_point(1000.0, 1000.0);
}

void c_tree::find(float _x, float _y){
  c_nodo** chariot = &this->head;
  c_point temp_p(_x, _y);
  vector <int> ruta_cuadrants;

  bool travel_condition = true;
  while (travel_condition) {
    if(*chariot == NULL or (*chariot)->es_hoja == true){
      travel_condition = false;
    }
    else{
      int trainer = (*chariot)->send_region(temp_p);
      chariot = &((*chariot)->hijos[ trainer]);
      ruta_cuadrants.push_back(trainer);
    }
  }
  if(*chariot == NULL){
    cout<<"No existe el punto buscado"<<endl;
  }
  else{
    //Aqui se busca el punto en la hoja
    if( (*chariot)->find_p(temp_p) ){
      cout<<"El punto "<<temp_p<<" existe con ruta: ";
      for(unsigned int i = 0; i < ruta_cuadrants.size(); i++){
        cout<<ruta_cuadrants[i]+1;
      }
      cout<<endl;
    }
    else{
      cout<<"El punto "<<temp_p<<" no existe"<<endl;
    }
  }
}

void c_tree::insert(float _x, float _y){
  c_nodo** chariot = &this->head;//Puntero a puntero que viaja por el arbol buscando el lugar apropiado
  c_point temp_p(_x, _y);//Creamos el punto a insertar;

  bool travel_condition = true; //Determina la duracion del bucle

  while(travel_condition){
      if(*chariot == NULL or (*chariot)->es_hoja == true){
      travel_condition = false;
      //Siempre nos vamos a quedar en un nodo, en el incio puede que este vacio
    }
    else{
      //calling a function to get the region, at this region is provided by c_nodo
      chariot = &((*chariot)->hijos[  (*chariot)->send_region(temp_p) ]);
    }
  }

  if(*chariot == NULL){
    //cout<<"Estamos en el inicio o es punto muerto"<<endl;
    //*chariot = new c_nodo( c_point(range_1, range_1), c_point(range_2, range_2));
    *chariot = new c_nodo(this->point_range_1, this->point_range_2, 0);//Using a new type of data
    (*chariot)->add_point(temp_p);
    this->numero_puntos++;
    //No es lo convenient, pero al estar al incio podemos asumir que hay solo un punto en dicho nodo
    //esto nos evita realizar un escaneo en dicho lugar
  }
  else{//Como no existen los nullos salvo en el primer caso, entonces esta sera una opcion por defecto
    if(!(*chariot)->find_p(temp_p)) {
      (*chariot)->add_point(temp_p);//Añadimos el punto en la hoja.
      this->numero_puntos++;
      if(!(*chariot)->review_cant(this->limit_per_area)){
        (*chariot)->reorganize_region(this->limit_per_area);
      }
    }
  }
  //cout<<"Inserccion correcta, existen "<<this->numero_puntos<<" puntos."<<endl;
}

void c_tree::initial_region_setter(c_point down, c_point up){
  if(this->numero_puntos == 0){
    this->point_range_1 = down;
    this->point_range_2 = up;
  }
  else{
    cout<<"Existen puntos en el arbol, ya no es posible cambiar la region inicial de distribucion"<<endl;
  }
}

c_tree::~c_tree(){}

#endif
