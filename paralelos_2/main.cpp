#include <iostream>
#include <vector>
#include <ctime>

//Add cahce misses

using namespace std;

void multi_1( vector<vector<double>>, vector<vector<double>> );
void multi_2( vector<vector<double>>, vector<vector<double>> );

void print_v( vector<vector<double>>);
int min(int, int);

int main(){
  vector< vector<double> >  a(1000, vector<double>(200, rand()%100) );
  vector< vector<double> >  b(200, vector<double>(1000, rand()%100) );

  multi_1(a, b);
  multi_2(a, b);

}

void multi_1(vector<vector<double>> a, vector<vector<double>> b){

  vector<vector<double>> c(a.size(), vector<double>(b[0].size(), 0));

  for(unsigned int i = 0; i < c.size(); i++){
      for(unsigned int j = 0; j < c[0].size(); j++){
        for(unsigned int k = 0; k < a[0].size(); k++){
          c[i][j] = c[i][j] + (a[i][k] * b[k][j]);
        }
      }
  }

  cout<<"Hi_1"<<endl;
}


void multi_2( vector< vector<double> > a, vector<vector<double>> b){

  vector< vector<double> > c(a.size(), vector<double>(b[0].size(),0));

  unsigned int jump = 8;
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

  cout<<"Hi_2"<<endl;
}



int min(int a, int b){
  if(a < b){return a;}
  else{return b;}
}




void print_v(vector<vector<double>> a){
  for(unsigned int i = 0; i < a.size(); i++){
    for(unsigned int j = 0; j < a[i].size(); j++){
      cout<<a[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}
