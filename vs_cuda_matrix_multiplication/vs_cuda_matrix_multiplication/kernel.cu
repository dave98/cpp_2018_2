
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cuda.h>
#include <device_functions.h>
#include <cuda_runtime_api.h>

__host__ __device__ const int TILE_WIDTH = 2;

__global__ void MatrixMulKernel(float* d_M, float* d_N, float* d_P, int Width);

int main()
{

    return 0;
}

__global__ void MatrixMulKernel(float* d_M, float* d_N, float* d_P, int Width) {
	__shared__ float Mds[TILE_WIDTH][TILE_WIDTH];
	__shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

	int bx = blockIdx.x;  int by = blockIdx.y;
	int tx = threadIdx.x; int ty = blockIdx.y;

	int Row = by * TILE_WIDTH + ty;
	int Col = bx * TILE_WIDTH + tx;

	float Pvalue = 0;
	for (int ph = 0; ph < Width / TILE_WIDTH; ++ph) {
		Mds[ty][tx] = d_M[Row*Width + ph * TILE_WIDTH + tx];
		Nds[ty][tx] = d_N[(ph*TILE_WIDTH + ty) * Width + Col];
	}
	__syncthreads();

	for (int k = 0; k < TILE_WIDTH; ++k) {
		Pvalue += Mds[ty][k] * Nds[tx]
	}
}