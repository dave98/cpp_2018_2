#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

void foo(int x){
  cout<<"Hello World  from: "<<x<<endl;
  printf("\n");
}

int main(){
  thread first(foo, 1);
  Sleep(1000);
  thread second(foo, 2);

  first.join();
  second.join();

  return 0;
}
