#include <iostream>
#include <vector>

using namespace std;



int main(int argc, char** argv){
  int MAX = 0;
  cin>>MAX;

  vector< vector<double> > a(MAX, vector<double>(MAX, 1));
  vector<double> x(MAX, 1);
  double y = 0;

  for(int i = 0; i < MAX; i++){
    for(int j = 0; j < MAX; j++){
      y += a[i][j] * x[j];
    }
  }

}
