#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]){
  if(argc < 20){
    cout<<"you must supply a value"<<endl;
    exit(0);
  }
  char buffer[10];
  strcpy(buffer, argv[1]);
  cout<<"El valor proprocionado es: "<<buffer<<endl;
  return 0;
}
