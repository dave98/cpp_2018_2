#ifndef C_PASSWORD_H
#define C_PASSWORD_H

#include <iostream>

using namespace std;

class c_password{
public:
  string alfa;
  string password;
  string encrypted_password;
  int key;


  int size_min = 8;
  int size_max = 28;

  c_password();
  ~c_password();
  void create_password();
  bool rules_verification(string);
  bool rule_1_size(string); //Con un tamaño determinado de caracteres
  bool rule_2_min(string); //Debe haber por lo menos una minúscula;
  bool rule_3_num(string); //Debe de haber un numero;
  bool rule_4_car(string); //Caracter especial;
  bool rule_5_esp(string); //No debe aceptar espacio;

  void encriptar();
    int get_position(char);
};

c_password::c_password(){
  this->alfa = "0123456789,abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-.()";
  this->password = "";
  this->encrypted_password = "";
  this->key = 0;
}

c_password::~c_password(){}

void c_password::create_password(){
  string tem_pass;
  cout<<"Ingrese su password: "<<endl;
  cin>>tem_pass;

  while(!this->rules_verification(tem_pass)){
    cout<<"Nuevo pasword:"<<endl;
    cin>>tem_pass;
    cout<<endl;
  }

  cout<<"Password aceptado"<<endl<<endl;
  this->password = tem_pass; // Aceptamos el password;
  this->encrypted_password = this->password;

  cout<<"Encriptando..."<<endl;
  this->encriptar();
  cout<<"Password encriptado: "<<this->encrypted_password<<endl<<endl;
}

bool c_password::rules_verification(string pass){
  bool total_review = true;
  if( ! this->rule_1_size(pass)){return false;}
  else if( !this->rule_2_min(pass)){return false;}
  else if( !this->rule_3_num(pass)){return false;}
  else if( !this->rule_4_car(pass)){return false;}
  else if( !this->rule_5_esp(pass)){return false;}
  else{return true;}

}

bool c_password::rule_1_size(string pass){
  if((pass.size() < this->size_min) or (pass.size() > this->size_max)){
    cout<<" Longitud incorrecta"<<endl;
    return false;
  }
  else{
    return true;
  }
}


bool c_password::rule_2_min(string pass){
  for(unsigned int i = 0; i < pass.size(); i++){
    if(( (int)pass[i] >= 97)  and ((int)pass[i] <= 122) ){
      return true;
    }
  }
  cout<<" Debe poseer minúsuculas "<<endl;
  return false;
}

bool c_password::rule_3_num(string pass){
  for(unsigned int i = 0; i < pass.size(); i++){
    if(( (int)pass[i] >= 48)  and ((int)pass[i] <= 57) ){
      return true;
    }
  }
  cout<<" Debe poseer numeros"<<endl;
  return false;
}

bool c_password::rule_4_car(string pass){
  for(unsigned int i = 0; i < pass.size(); i++){
    if( !( ( (int)pass[i] >= 48)  and ((int)pass[i] <= 57) or ( (int)pass[i] >= 97)  and ((int)pass[i] <= 122) ) ){
      return true;
    }
  }
  cout<<" Debe tener un caracter especial"<<endl;
  return false;
}

bool c_password::rule_5_esp(string pass){
  for(unsigned int i = 0; i < pass.size(); i++){
    if( (int)pass[i] == 32 ){
      return false;
      cout<<"No debe aceptar espacios"<<endl;
    }
  }
  return true;
}

void c_password::encriptar(){
  cout<<"Encriptando, ingrese una llave: "<<endl;
  cin>>this->key;
  //Cifrando con cesar
  for(unsigned int i = 0; i < this->password.size(); i++){
    int encripted = this->get_position(this->password[i]);
    encripted = (encripted + key) % this->alfa.size();
    this->encrypted_password[i] = this->alfa[encripted];
  }
}

int c_password::get_position(char lo){
  for(unsigned int i = 0; i < this->password.size(); i++){
    if(lo == this->password[i]);
      return i;
  }
  cout<<"Valor no registrado"<<endl;
}


#endif
