
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int SIZE = 50;
const float BLOCK_WIDTH = 8;

void add_matrix(int* , int* , int* , int, char); //Just work with same sizes matrices.
__global__ void add_matrix_kernel(int*, int*, int*, int);
__global__ void add_matrix_row_kernel(int*, int*, int*, int);
__global__ void add_matrix_col_kernel(int*, int*, int*, int);

void mul_matrix_vec(int*, int*, int*, int);
__global__ void mul_matrix_vec_kernel(int*, int*, int*, int);

//void BlockTranspose(int*, int*, int, int);
//__global__ void BlockTransposeKernel(int*, int, int);

void print_matrix(int*, int, int);
void print_vec(int*, int);



int main()
{
	
	int* m_a = new int[SIZE * SIZE];
	int* m_b = new int[SIZE * SIZE];
	int* m_c = new int[SIZE * SIZE];
	int* m_c2 = new int[SIZE * SIZE];
	int* m_c3 = new int[SIZE * SIZE];

	int* vec1 = new int[SIZE];
	int* vec2 = new int[SIZE];

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int pos = (i * SIZE) + j;
			m_a[pos] = i + j;
			m_b[pos] = i * j;
			m_c[pos] = 0;
			m_c2[pos] = 0;
			m_c3[pos] = 0;
		}
	}

	for (int j = 0; j < SIZE; j++) {
		vec1[j] = j;
		vec2[j] = 0;
	}

	/*
	cout << "Vector" << endl;
	print_vec(vec1, SIZE); cout << endl;
	cout << "Matriz" << endl;
	print_matrix(m_a, SIZE, SIZE); cout << endl;
	cout << "Resultado" << endl;
	mul_matrix_vec(m_a, vec1, vec2, SIZE);
	
	print_vec(vec2, SIZE); 
	*/

	//print_matrix(m_a, SIZE, SIZE); cout << endl;
	//print_matrix(m_b, SIZE, SIZE); cout << endl;

	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//BlockTranspose(m_a, m_c, SIZE, SIZE);
	add_matrix(m_a, m_b, m_c, SIZE, 'n');
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//print_matrix(m_c, SIZE, SIZE);
	auto duration1 = duration_cast<microseconds>(t2 - t1).count();

	t1 = high_resolution_clock::now();
	add_matrix(m_a, m_b, m_c2, SIZE, 'r');
	t2 = high_resolution_clock::now();
	//print_matrix(m_c, SIZE, SIZE);
	auto duration2 = duration_cast<microseconds>(t2 - t1).count();

	t1 = high_resolution_clock::now();
	add_matrix(m_a, m_b, m_c3, SIZE, 'c');
	t2 = high_resolution_clock::now();
	//print_matrix(m_c, SIZE, SIZE);
	auto duration3 = duration_cast<microseconds>(t2 - t1).count();

	cout << "Normal 1: " << duration1 << endl;
	cout << "Filas 2: " << duration2 << endl;
	cout << "Columnas 3: " << duration3 << endl;
	

	return 0;	
}


void add_matrix(int* a, int* b, int* c, int size, char ans) {
	int total_size = size * size * sizeof(int);

	int* d_a;
	int* d_b;
	int* d_c;

	cudaMalloc( (void**) &d_a, total_size);
	cudaMalloc( (void**) &d_b, total_size);
	cudaMalloc( (void**) &d_c, total_size);

	cudaMemcpy(d_a, a, total_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, total_size, cudaMemcpyHostToDevice);

	float block = 16;
	dim3 grid_size(ceil(size/block), ceil(size/block), 1);
	dim3 block_size(block, block, 1);

	switch (ans)
	{
	case 'n':
		add_matrix_kernel <<< grid_size, block_size >>> (d_a, d_b, d_c, size);
		break;
	case 'r':
		add_matrix_row_kernel <<< grid_size, block_size >>> (d_a, d_b, d_c, size);
		break;
	case 'c':
		add_matrix_col_kernel <<< grid_size, block_size >>> (d_a, d_b, d_c, size);
		break;
	default:
		break;
	}
	cudaMemcpy(c, d_c, total_size, cudaMemcpyDeviceToHost);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
}

//normal addition;
__global__ void add_matrix_kernel(int* a, int* b, int* c, int size) {
	int gpu_columna = (blockDim.x * blockIdx.x) + threadIdx.x;
	int gpu_fila = (blockDim.y * blockIdx.y) + threadIdx.y;

	if (gpu_columna < size  && gpu_fila < size) {
		int pos = gpu_fila * size + gpu_columna;
		c[pos] = a[pos] + b[pos];
	}
}

//row addition;
__global__ void add_matrix_col_kernel(int* a, int* b, int* c, int size) {
	int gpu_columna = (blockDim.x * blockIdx.x) + threadIdx.x;
	int gpu_fila = (blockDim.y * blockIdx.y) + threadIdx.y;

	if (gpu_fila == 0){
		for (int i = 0; i < size; i++) {
			int pos = (i *  size + gpu_columna);
			c[pos] = a[pos] + b[pos];
		}
	}
}

//col addition;
__global__ void add_matrix_row_kernel(int* a, int* b, int* c, int size) {
	int gpu_columna = (blockDim.x * blockIdx.x) + threadIdx.x;
	int gpu_fila = (blockDim.y * blockIdx.y) + threadIdx.y;

	if (gpu_columna == 0) {
		for (int i = 0; i < size; i++) {
			int pos = (gpu_fila *  size + i);
			c[pos] = a[pos] + b[pos];
		}
	}
}

/*
void BlockTranspose(int* h_mat, int* out_mat, int columnas, int filas) {
	int* d_mat;
	int m_size = columnas * filas * sizeof(int);

	cudaMalloc((void**) &d_mat, m_size);
	cudaMemcpy(d_mat, h_mat, m_size, cudaMemcpyHostToDevice);

	dim3 gridDim(ceil(columnas/BLOCK_WIDTH), ceil(filas/BLOCK_WIDTH), 1);
	dim3 blockDim(BLOCK_WIDTH, BLOCK_WIDTH, 1);

	BlockTransposeKernel<<< gridDim, blockDim >>>(d_mat, columnas, filas);

	cudaMemcpy(out_mat, d_mat, m_size, cudaMemcpyDeviceToHost);
	
	cudaFree(d_mat);
}
*/


void mul_matrix_vec(int* h_m, int* h_vec_1, int* h_vec_2, int size) {
	int* d_m;
	int* d_vec_1;
	int* d_vec_2;

	int size_mat = size * size * sizeof(int);
	int size_vec = size * sizeof(int);
	
	cudaMalloc((void**) &d_m, size_mat);
	cudaMalloc((void**) &d_vec_1, size_vec);
	cudaMalloc((void**) &d_vec_2, size_vec);

	cudaMemcpy(d_m, h_m, size_mat, cudaMemcpyHostToDevice);
	cudaMemcpy(d_vec_1, h_vec_1, size_vec, cudaMemcpyHostToDevice);

	dim3 gridDim(ceil(size / BLOCK_WIDTH), ceil(size / BLOCK_WIDTH), 1);
	dim3 blockDim(BLOCK_WIDTH, BLOCK_WIDTH, 1);
	
	mul_matrix_vec_kernel <<< gridDim, blockDim >>> (d_m, d_vec_1, d_vec_2, size);

	cudaMemcpy(h_vec_2, d_vec_2, size_vec, cudaMemcpyDeviceToHost);
	cudaFree(d_m);
	cudaFree(d_vec_1);
	cudaFree(d_vec_2);
}


//execution order vect(x_1, y_1) x mat(x_2, y_2); y_1 == x_2
__global__ void mul_matrix_vec_kernel(int* h_m, int* h_vec_1, int* h_vec_2, int size) {
	int gpu_columna = (blockIdx.x * blockDim.x) + threadIdx.x;
	int gpu_fila = (blockIdx.y * blockDim.y) + threadIdx.y;
	
	if (gpu_fila == 0) {
		h_vec_2[gpu_columna] = 0; //Index for resultant matrix
		for (int i = 0; i < size; i++) { // To descend in matrix
			h_vec_2[gpu_columna] += h_m[i*size + gpu_columna] * h_vec_1[i];
		}
	}
}



void print_matrix(int* a, int s_1, int s_2) {
	for (int i = 0; i < s_1; i++) {
		for (int j = 0; j < s_2; j++) {
			cout << a[i*s_2 + j] << "  ";
		}
		cout << endl;
	}
}

void print_vec(int* a, int s_1) {
	for (int i = 0; i < s_1; i++) {
		cout << a[i] << "  ";
	}
}
