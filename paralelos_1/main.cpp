#include <iostream>
#include <vector>

using namespace std;



int main(int argc, char** argv){

  vector< vector<double> > a(argc, vector<double>(argc, 1));
  vector<double> x(argc, 1);
  double y = 0;

  for(int i = 0; i < argc; i++){
    for(int j = 0; j < argc; j++){
      y += a[i][j] * x[j];
    }
  }

}
