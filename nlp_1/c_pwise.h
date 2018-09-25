#ifndef C_PWISE_H
#define C_PWISE_H

#include <iostream>
#include <vector>
#include "c_arbol_counter.h"

using namespace std;

class c_pwise{
public:
  //vector<string> content;
  c_arbol_counter<string> structured_content;

  c_pwise(vector<string>);
  ~c_pwise();

  void show_content();
};




c_pwise::c_pwise(vector<string> content_){
  //this->content = content_;
  for(unsigned int i = 0; i < content_.size(); i++){
    structured_content.insert(content_[i]);
  }
}

c_pwise::~c_pwise(){}

void c_pwise::show_content(){
  //for(unsigned int i = 0; i < this->content.size(); i++){
    //cout<<content[i]<<endl;
  //}
  //cout<<endl;
}

#endif
