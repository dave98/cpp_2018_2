#include <iostream>
#include <vector>

using namespace std;

#define MAX 13000

int main(){

  vector< vector<double> > a(MAX, vector<double>(MAX, 1));
  vector<double> x(MAX, 1);
  double y = 0;



  for(int j = 0; j < MAX-1; j++){
    for(int i = 0; i < MAX-1; i++){
      y += a[i][j] * x[j];
    }
  }
  cout<<"y: "<<y<<endl;


}
