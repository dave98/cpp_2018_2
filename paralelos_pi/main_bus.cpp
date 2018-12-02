#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

double global_sum = 0.0;
mutex mtx;

void thread_processing(int, int);

int main(int argc, char const *argv[])
{
	//int n_thread = thread::hardware_concurrency();
	int n_thread = 0;
	int n_iteracciones = 1000000000;

	int segments = 0;
	double pi = 0;
	
	//cout<<"Ingrese n: "<<endl;
	//cin>>n_iteracciones;
	cout<<"Numeros de Threads: "<<endl;
	cin>>n_thread;

	thread list_thread[n_thread];
	segments = n_iteracciones / n_thread; //Obtenemos el tamaño de elementos en cada segmentos
	
	unsigned t0, t1;
	t0=clock();

	for(int i = 0, marker = 0; i  < n_thread; i++, marker+=segments){
		list_thread[i] = thread(thread_processing, marker, segments);
	}

	for(int i = 0; i < n_thread; i++){
		list_thread[i].join();
	}

	pi = 4.0 * global_sum;
	t1=clock();
	double time = (double(t1-t0)/CLOCKS_PER_SEC);

	cout<<"PI paralelo: "<<pi<<endl;
	cout<<"EXecution Time: "<<time<<endl;
	return 0;
}

void thread_processing(int start_at, int quantity){
	double local_sum = 0.0;
	double factor = 1.0;

	if((start_at % 2) == 0){
		factor = 1.0;
	}
	else{
		factor = -1.0;
	}

	for(int i = 0; i < quantity; i++, factor = -factor, start_at++){
		local_sum += factor / (2*start_at + 1);
	}

	//mtx.lock();	
	thread::id main_t = this_thread::get_id();
	if(main_t == this_thread::get_id()){
		global_sum += local_sum;
	}
	
	//mtx.unlock();

}


