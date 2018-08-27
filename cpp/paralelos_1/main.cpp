#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

#define MAX 13000

int main(){

  vector< vector<double> > a(MAX, vector<double>(MAX, 1));
  vector<double> x(MAX, 1);
  //vector<double> y(MAX, 0);
  double y = 0;

  for(int i = 0; i < MAX; i++){
    for(int j = 0; j < MAX; j++){
      //y[i] += a[i][j] + x[j]
      y += a[i][j] * x[j];
    }
  }

  cout<<"y: "<<y<<endl;
  y = 0;


  for(int j = 0; j < MAX; j++){
    for(int i = 0; i < MAX; i++){
      y += a[i][j] * x[j];
    }
  }
  cout<<"y: "<<y<<endl;


}
