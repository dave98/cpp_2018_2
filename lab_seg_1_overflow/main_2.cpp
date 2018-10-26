#include <iostream>

using namespace std;

int x = 100;
int main(){
  int a = 2;
  float b = 2.5;
  static int y;

  int *ptr = (int*)malloc(2*sizeof(int));

  ptr[1] = 5;
  ptr[2] = 6;

  free(ptr);
  return 1;

}
