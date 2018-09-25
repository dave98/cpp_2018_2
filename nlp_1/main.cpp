#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include "functions.h"
#include "c_pwise.h"

using namespace std;
vector<string> list_of_work = vector<string>(0, "");
vector<string> delete_list = vector<string>(0, "");

bool find_word(string);
void get_str();

int main(){
  get_str();

  c_pwise datos(list_of_work);
//  datos.show_content();
  list_of_work.clear();
  delete_list.clear();

  return 0;
}

void get_str(){
  string docname;
  ifstream file_1;

  cout<<"Nombre del documento: "<<endl;
  cin>>docname;
  file_1.open(docname);

  while(file_1 >> docname){
    if(find_word( docname )){
      delete_list.push_back(docname);
    }
    else{
      list_of_work.push_back(docname);
    }
  }

  file_1.close();
  //cout<<"Listed words: "<<list_of_work.size()<<endl;
  //cout<<"Deleted words: "<<delete_list.size()<<endl;
  //print_list(list_of_work); cout<<endl;
}

bool find_word(string look_for_value){
  string line;
  int offset;
  ifstream file_2;
  file_2.open("constraints_2.txt");
  while(!file_2.eof()){
    getline(file_2, line);
    if((offset = line.find(look_for_value, 0)) != string::npos){
      //cout<<"Found"<<endl;
      return true;
    }
  }
  file_2.close();
  return false;
}
