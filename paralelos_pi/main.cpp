#include <iostream>
#include <thread>
#include <vector>
#include <ctime>

using namespace std;

int main(int argc, char const *argv[])
{
	int n_iteracciones = 100000000;
	
	double factor = 1.0;
	double sum = 0.0;
	double pi = 0;
	//cout<<"Ingrese n: "<<endl;
	//cin>>n_iteracciones;

	unsigned t0, t1;

	t0=clock();
	for(int i = 0; i < n_iteracciones; i++, factor = -factor){
		sum += factor / (2*i +1);
	}

	pi = 4.0 *  sum;
	
	t1=clock();
	double time = (double(t1-t0)/CLOCKS_PER_SEC);

	cout<<"PI serial: "<<pi<<endl;
	cout<<"EXecution Time: "<<time<<endl;
	return 0;
}
