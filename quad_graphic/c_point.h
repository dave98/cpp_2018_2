#ifndef C_POINT_H
#define C_POINT_H

#include <iostream>
using namespace std;


class c_point{
public:
  float x;
  float y;
  c_point();
  c_point(float, float);
  ~c_point();

  void set_p(float, float);
  c_point & operator = ( const c_point  &p);
  bool operator == (const c_point &p) const;
  friend ostream& operator << (ostream &o, const c_point& p);
};

c_point::c_point(){
  this->x = 0.0;
  this->y = 0.0;
}

c_point::c_point(float _x, float _y){
  this->x = _x;
  this->y = _y;
}

c_point::~c_point(){}

void c_point::set_p(float _x, float _y){
  this->x = _x;
  this->y = _y;
}

c_point& c_point::operator = (const c_point &p){
  this->x = p.x;
  this->y = p.y;
  return *this;
}

bool c_point::operator == (const c_point &p) const{
  if(this->x == p.x and this->y == p.y){
    return true;
  }
  else{return false;}
}

ostream& operator << (ostream &o, const c_point& p){
  o << "("<< p.x<<";"<<p.y<<")";
  return o;
}
#endif
