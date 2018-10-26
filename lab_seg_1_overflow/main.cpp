#include <iostream>
#include <stdio.h>
#include <string.h>


using namespace std;


int foo(char* str){
  char buffer[100];
  strcpy(buffer, str);

  return 1;
}

int main(){
  char str[400];
  FILE *badfile;

  badfile = fopen("badfile", "r");
  fread(str, sizeof(char), 200, badfile);
  foo(str);

  printf("Returned properly\n");
  return 0;
}
