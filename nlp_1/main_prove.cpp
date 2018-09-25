#include <iostream>
#include <vector>
#include "c_arbol_counter.h"

using namespace std;

int main(){
  c_arbol_counter<string> tree_1;

  tree_1.insert("como");
  tree_1.insert("como");
  tree_1.insert("como");
  tree_1.insert("como");

  tree_1.buscar("como");

  return 0;
}
