#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include <vector>
#include "c_point.h"

using namespace std;
extern vector<c_point > data_region;
extern int profundity;//Verified when a region must be draw

class c_nodo{
public:
  c_nodo* hijos[4];
  vector< c_point > values;//Se almacena una cantidad específica de puntos
  int cant; //Controla cantidad de puntos que se almacenan
  bool es_hoja; //Indica si el nodo esuna hoja, como se sabe solo en las hojas se almacenan lo datos
  c_point d_l; //margen inferior izquierdo
  c_point u_r; // margen superior derecho
  c_point m_m; // punto central
  int deep;


  c_nodo(c_point, c_point, c_point);//Inciamos el nodo con un punto, no sirve
  c_nodo(c_point, c_point, int);
  ~c_nodo();

  void add_point(c_point);
  int send_region(c_point);//Recibe un punto y acorde a esto returna la posicion a la que pertenece
  void reorganize_region(int);
  bool review_cant(int);
  bool find_p(c_point);
};

c_nodo::c_nodo(c_point down_p, c_point top_p, int _deep){
  this->cant = 0; //Iniciamos el nodo sin nada almacenado
  this->d_l = down_p;
  this->u_r = top_p;
  this->m_m = c_point((this->d_l.x + this->u_r.x)/2, (this->d_l.y + this->u_r.y)/2);
  this->es_hoja = true;
  this->deep = _deep;
  //data_region.push_back(this->d_l);
  //data_region.push_back(this->u_r);


  for(int i = 0; i < 4; i++){ this->hijos[i] = NULL;}//Todos los hijos son nullos
}

c_nodo::c_nodo(c_point punto, c_point down_p, c_point top_p){
  this->values.push_back(punto); //Se construye el nodo con un nuevo punto ingresante,
  this->cant = 1;
  this->d_l = down_p;
  this->u_r = top_p;
  this->es_hoja = true;
  this->deep = 0;//Ni siquira lo estoy usando


  this->m_m = c_point((this->d_l.x + this->u_r.x)/2, (this->d_l.y + this->u_r.y)/2);
}

bool c_nodo::find_p(c_point applier){
  for(unsigned int i = 0; i < this->values.size(); i++){
    if(values[i] == applier){
      return true;
    }
  }
  return false;
}

void c_nodo::add_point(c_point applier){
  this->values.push_back(applier);
  this->cant++;
}

int c_nodo::send_region(c_point applier){ // 0->r1, 1->r2, 2->r3, 3->r4
  if(applier.y > this->m_m.y){
      if(applier.x < this->m_m.x){
      return 0;
    }else{
      return 1;
    }
  }else{
    if(applier.x < this->m_m.x){
      return 2;
    }else{
      return 3;
    }
  }
}

void c_nodo::reorganize_region(int flag){
  //Redistribuimos los espacios para los hijos. Manera logica :b
  //cout<<"Realizando acomodamiento de nodo"<<endl;
  if(this->deep < profundity){
    data_region.push_back(this->d_l);//Puntos de grafico
    data_region.push_back(this->u_r);//Puntos de grafico
  }
  /*R1*/this->hijos[0] = new c_nodo( c_point( this->d_l.x , (this->d_l.y + this->u_r.y)/2), c_point( (this->d_l.x + this->u_r.x)/2, this->u_r.y) , this->deep+1);
  /*R2*/this->hijos[1] = new c_nodo( this->m_m, this->u_r, this->deep+1);
  /*R3*/this->hijos[2] = new c_nodo( this->d_l, this->m_m, this->deep+1);
  /*R4*/this->hijos[3] = new c_nodo( c_point( (this->d_l.x + this->u_r.x)/2 , this->d_l.y), c_point( this->u_r.x ,(this->d_l.y + this->u_r.y)/2), this->deep+1);
  //Los hijos con las regiones han sido creados, ahora procederemos a ceder los datos de este nodo a esos hijos.
  for(unsigned int i = 0; i < values.size(); i++){
      int new_region = this->send_region(values[i]);
      this->hijos[new_region]->add_point(values[i]);
  }
  this->values.empty();//Una vez que los puntos hayan sido distribuidos vaciamos el nodo
  this->cant = 0;
  this->es_hoja = false;//Ahora este nodo se ha convertido en un punto de paso en vez de un almacen de datos

  for(int i = 0; i < 4; i++){
    if(!(this->hijos[i]->review_cant(flag))){
      this->hijos[i]->reorganize_region(flag);
    }
  }
}

bool c_nodo::review_cant(int flag){
  if(this->cant > flag){//Si se sobrepasa el numero de puntos permitidos entonces devuelve falso
    return false;
  }else{
    return true;}
}

c_nodo::~c_nodo(){}

#endif
