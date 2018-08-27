#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


int min(int, int);

int main(){
  int max_1 = 0;
  int max_2 = 0;
  cin>>max_1;
  cin>>max_2;


  vector< vector<double> >  a(max_1, vector<double>(max_2, rand()%100) );
  vector< vector<double> >  b(max_2, vector<double>(max_1, rand()%100) );

  vector< vector<double> > c(a.size(), vector<double>(b[0].size(),0));

  unsigned int jump = 6;
  for(unsigned int i = 0; i < a.size(); i+=jump){
    for(unsigned int j = 0; j < b[0].size(); j+=jump){
      for(unsigned int k = 0; k < a[0].size(); k+=jump){
        for(unsigned int i0 = i; i0 < min(i + jump - 1, a.size()); i0++){
          for(unsigned int j0 = j; j0 < min(j + jump -1, b[0].size()); j0++){
            for(unsigned int k0 = k; k0 < min(k + jump - 1, a[0].size()); k0++){
              c[i0][j0] = c[i0][j0] + (a[i0][k0] * b[k0][j0]);
            }
          }
        }
      }
    }
  }

}

int min(int a, int b){
  if(a < b){return a;}
  else{return b;}
}
