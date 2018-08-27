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
  vector< vector<double> >  b(200, vector<double>(100, rand()%100) );

  multi_1(a, b);
  //multi_2(a, b);
  //print_v(a);

}

void multi_1(vector<vector<double>> a, vector<vector<double>> b){
  //--->a*b
  unsigned int t0, t1;
  t0 = clock();

  vector<vector<double>> c(a.size(), vector<double>(b[0].size(), 0));

  for(unsigned int i = 0; i < c.size(); i++){
      for(unsigned int j = 0; j < c[0].size(); j++){
        for(unsigned int k = 0; k < a[0].size(); k++){
          c[i][j] = c[i][j] + (a[i][k] * b[k][j]);
        }
      }
  }

  t1 = clock();
  double time_ = (double(t1-t0)/CLOCKS_PER_SEC);
  cout << "Done 1 on: " << time_ << endl;
}

void multi_2( vector<vector<double>> a, vector<vector<double>> b){

  unsigned int b = 4;
  vector<vector<double>> c(a.size(), vector<double>(b[0].size(), 0));

 for(unsigned int i  = 0; i < c.size(); i+=b){
   for(unsigned int j = 0; i < c[0].size(); j+=b){
     for(unsigned int k = 0; k < a[0].size(); k+=b){
       for(unsigned int i_0 = i; i_0 < min(i + b - 1, n); i_0++){

       }
     }
   }
 }

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
