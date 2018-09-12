#ifndef C_PASSWORD_H
#define C_PASSWORD_H

#include <iostream>

using namespace std;

class c_password{
public:
  static string alfa;
  string password;

  c_password();
  ~c_password();
};

c_password::c_password(){
  this->alfa = "0123456789,abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-.()";
  this->password = "";
}

c_password::~c_password(){}



#endif
