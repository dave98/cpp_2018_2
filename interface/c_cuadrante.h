#ifndef C_CUADRANTE_H
#define C_CUADRANTE_H

#include <iostream>
#include <vector>

using namespace std;

class c_cuadrante{
public:
  float lu_x;
  float lu_y;
  float rd_x;
  float rd_y;
  bool state;

  c_cuadrante(float, float, float, float);
  ~c_cuadrante();
};


c_cuadrante::c_cuadrante(float lu_x_, float lu_y_, float rd_x_, float rd_y_){
  this->lu_x = lu_x_;
  this->lu_y = lu_y_;
  this->rd_x = rd_x_;
  this->rd_y = rd_y_;
  this->state = false;
}

c_cuadrante::~c_cuadrante(){}

#endif
