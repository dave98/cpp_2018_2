#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;



int main(){
  int max_1 = 0;
  int max_2 = 0;
  cin>>max_1;
  cin>>max_2;

  vector< vector<double> >  a(max_1, vector<double>(max_2, rand()%100) );
  vector< vector<double> >  b(max_2, vector<double>(max_1, rand()%100) );

  vector<vector<double> > c(a.size(), vector<double>(b[0].size(), 0));

  for(unsigned int i = 0; i < c.size(); i++){
      for(unsigned int j = 0; j < c[0].size(); j++){
        for(unsigned int k = 0; k < a[0].size(); k++){
          c[i][j] = c[i][j] + (a[i][k] * b[k][j]);
        }
      }
  }

}
