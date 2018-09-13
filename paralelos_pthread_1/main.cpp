#include <iostream>
#include <thread>

using namespace std;

void foo(int x){
  cout<<"Hello World  from: "<<x<<endl;
  printf("\n");
}

int main(){
  thread first(foo, 1);
  thread second(foo, 2);

  first.join();
  second.join();

  return 0;
}
