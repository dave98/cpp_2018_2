#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void vecAdd(double *a, double *b, double *c, int n)
{

    int id = blockIdx.x*blockDim.x+threadIdx.x;

    if (id < n) //EVitar salir de rangos
        c[id] = a[id] + b[id];
}

int main( int argc, char* argv[] )
{
    int n = 100000; //Tamaño vector

    //Entradas host
    double *h_a;
    double *h_b;
    //Salidas host
    double *h_c;

    // Entrada vector
    double *d_a;
    double *d_b;
    //Salida vector
    double *d_c;

    // Allocate memory for each vector on host
    h_a = (double*)malloc(n*sizeof(double));
    h_b = (double*)malloc(n*sizeof(double));
    h_c = (double*)malloc(n*sizeof(double));

    // Allocate memory for each vector on GPU
    cudaMalloc(&d_a, n*sizeof(double));
    cudaMalloc(&d_b, n*sizeof(double));
    cudaMalloc(&d_c, n*sizeof(double));

    int i;
    for( i = 0; i < n; i++ ) {
        h_a[i] = rand();
        h_b[i] = rand();
    }

    cudaMemcpy( d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy( d_b, h_b, bytes, cudaMemcpyHostToDevice);

    int blockSize = 1024;
    int gridSize;

    gridSize = (int)ceil((float)n/blockSize);

    vecAdd<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);

    cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );

    //Sumar resultado del vector
    double sum = 0;
    for(i=0; i<n; i++)
        sum += h_c[i];
    printf("final result: %f\n", sum/n);

    //Liberar Memoria
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}
