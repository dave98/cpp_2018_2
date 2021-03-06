#ifndef _MATRIX_H_
#define _MATRIX_H_

#define tile_width 4

#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void normal_square_matrix_mult_kernel(int *m, int *n, int *p, int width) {
	unsigned col = threadIdx.x + (blockIdx.x*blockDim.x);
	unsigned row = threadIdx.y + (blockIdx.y*blockDim.y);

	if (col < width && row < width) {
		int pvalue = 0;
		for (unsigned k = 0; k < width; k++) {
			pvalue += m[(row*width) + k] * n[(k*width) + col];
		}

		p[(row*width) + col] = pvalue;
	}
}

__global__ void tile_square_matrix_mult_kernel(int *m, int *n, int *p, int width) {
	__shared__ int mds[tile_width][tile_width];
	__shared__ int nds[tile_width][tile_width];

	int bx = blockIdx.x;
	int by = blockIdx.y;

	int tx = threadIdx.x;
	int ty = threadIdx.y;

	int row = (by*tile_width) + ty;
	int col = (bx*tile_width) + tx;

	int pvalue = 0;
	int ph, k;
	for (ph = 0; ph < width / tile_width; ph++) {
		mds[ty][tx] = m[(row*width) + (ph*tile_width) + tx];
		nds[ty][tx] = n[(((ph*tile_width) + ty)*width) + col];
		__syncthreads();

		for (k = 0; k < tile_width; k++) {
			pvalue += mds[ty][k] * nds[k][tx];
		}
		__syncthreads();
	}

	p[(row*width) + col] = pvalue;
}

void square_matrix_mult(int *m, int *n, int *p, int width, float block, char type) {
	int size = width * width * sizeof(int);
	int *d_m, *d_n, *d_p;

	cudaMalloc((void **)&d_m, size);
	cudaMalloc((void **)&d_n, size);
	cudaMalloc((void **)&d_p, size);

	cudaMemcpy(d_m, m, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_n, n, size, cudaMemcpyHostToDevice);

	dim3 dimGrid(ceil((float)width / block), ceil((float)width / block), 1);
	dim3 dimBlock(block, block, 1);

	switch (type) {
	case 'n':
		normal_square_matrix_mult_kernel <<< dimGrid, dimBlock >>> (d_m, d_n, d_p, width);
		break;
	case 't':
		tile_square_matrix_mult_kernel <<< dimGrid, dimBlock >>> (d_m, d_n, d_p, width);
		break;
	default:
		break;
	}

	cudaMemcpy(p, d_p, size, cudaMemcpyDeviceToHost);
				
	cudaFree(d_m);
	cudaFree(d_n);
	cudaFree(d_p);
}

#endif
