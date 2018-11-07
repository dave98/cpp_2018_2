
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

class OpenCVUnit
{
public:
	float r;
	float g;
	float b;
	__host__ __device__ OpenCVUnit(float r_, float g_, float b_) {
		this->r = r_;
		this->g = g_;
		this->b = b_;
	}

	__host__ __device__ OpenCVUnit() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	
	__host__ __device__ void set_r(float r_) { this->r = r_; }
	__host__ __device__ void set_g(float g_) { this->g = g_; }
	__host__ __device__ void set_b(float b_) { this->b = b_; }

	__host__ __device__ float get_r() { return this->r; }
	__host__ __device__ float get_g() { return this->g; }
	__host__ __device__ float get_b() { return this->b; }

};


void change_to_gray(OpenCVUnit* , float* , unsigned int , unsigned int );

__global__ void change_to_gray_kernel(OpenCVUnit*, float*, unsigned int, unsigned int);

int main()
{

	Mat image_in = imread("lena.jpg", IMREAD_COLOR);
	if (image_in.empty()) {
		cout << "No se pudo leer la imagen" << endl;
		return 0;
	}

	namedWindow("Entrada", WINDOW_NORMAL);
	imshow("Entrada", image_in);

	unsigned int columnas = image_in.cols;
	unsigned int filas = image_in.rows;

	cout << "Columnas: " << columnas << " -- " << "Filas: " << filas << endl;

	OpenCVUnit* pixels_in = new OpenCVUnit[columnas * filas]; //Pool for pixels from image
	float* pixel_out = new float[columnas *  filas];

	for (int i = 0; i < filas; i++) { //Copiar datos dentro de matriz de pixeles
		for (int j = 0; j < columnas; j++) {
			//cout << "[ " << (float)image_in.at<Vec3b>(i, j)[0] << " - " << (float)image_in.at<Vec3b>(i, j)[1] << " - " << (float)image_in.at<Vec3b>(i, j)[2] <<" ]";

			pixels_in[i*columnas + j].set_r((float)image_in.at<Vec3b>(i, j)[0]);
			pixels_in[i*columnas + j].set_g((float)image_in.at<Vec3b>(i, j)[1]);
			pixels_in[i*columnas + j].set_b((float)image_in.at<Vec3b>(i, j)[2]);
		}
		//cout << "------------" << endl;
	}

	/*
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			cout << "[ " << pixels_in->get_r() << " " << pixels_in->get_g() << " " << pixels_in->get_b() << " ]";
		}
		cout << endl;
	}
	*/

	//Tratamiento de la imagen 
	//change_to_gray(pixels_in, pixel_out, columnas, filas);
	
	int size_of_image_in = columnas * filas * sizeof(OpenCVUnit);
	int size_of_image_out = columnas * filas * sizeof(float);

	OpenCVUnit* d_pixels_in;
	float* d_pixel_out;
	
	cudaMalloc((void** ) &d_pixels_in, size_of_image_in);
	cudaMalloc((void** ) &d_pixel_out, size_of_image_out);
	cudaMemcpy(d_pixels_in, pixels_in, size_of_image_in, cudaMemcpyHostToDevice);


	int block = 16;
	dim3 size_grid = (ceil(columnas / block), ceil(filas / block), 1);
	dim3 size_block = (block, block, 1);

	change_to_gray_kernel <<< size_grid, size_block >>> (d_pixels_in, d_pixel_out, columnas , filas );
	

	cudaMemcpy(pixel_out, d_pixel_out, size_of_image_out, cudaMemcpyDeviceToHost);

	cudaFree(d_pixels_in);
	cudaFree(d_pixel_out);
	
/////

	Mat image_out(filas, columnas, CV_8UC3, Scalar(0, 0, 0));
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			//cout << "[ " << pixel_out[i*columnas + j] << " ]";
			image_out.at<Vec3b>(i, j)[0] = pixel_out[i*columnas + j];
			image_out.at<Vec3b>(i, j)[1] = pixel_out[i*columnas + j];
			image_out.at<Vec3b>(i, j)[2] = pixel_out[i*columnas + j];
		}
		//cout << endl;
	}

	namedWindow("Salida", WINDOW_NORMAL);
	imshow("Salida", image_out);

	waitKey(0);
	destroyWindow("Entrada");
	destroyWindow("Salida");

	delete pixels_in;
	delete pixel_out;
	return 0;
}

//Configuration for CUDA deployment
void change_to_gray(OpenCVUnit* h_pixels_in, float* h_out, unsigned int h_columnas, unsigned int h_filas) {
	OpenCVUnit* d_pixels_in;
	float* d_out;

	int size_of_pixel_max = h_columnas * h_filas * sizeof(OpenCVUnit);
	int size_of_float_max = h_columnas * h_filas * sizeof(float);


	cudaMalloc((void** ) &d_pixels_in, size_of_pixel_max);
	cudaMalloc((void**) &d_out, size_of_float_max);
	cudaMemcpy(d_pixels_in, h_pixels_in, size_of_pixel_max, cudaMemcpyHostToDevice);

	int block = 16;
	dim3 size_grid = (ceil(h_columnas / block), ceil(h_filas / block), 1);
	dim3 size_block = (block, block, 1);

	change_to_gray_kernel<<< size_grid, size_block >>>(d_pixels_in, d_out, h_columnas, h_filas);

	cudaMemcpy(h_out, d_out, size_of_float_max, cudaMemcpyDeviceToHost);

	cudaFree(d_pixels_in);
	cudaFree(d_out);
	
}

//CUDA code
__global__ void change_to_gray_kernel(OpenCVUnit* image, float* gray, unsigned int columnas, unsigned int filas) {
	unsigned int gpu_columma = threadIdx.x + (blockIdx.x * blockDim.x);
	unsigned int gpu_fila = threadIdx.y + (blockIdx.y * blockDim.y);

	if (gpu_columma < columnas && gpu_fila < filas) {
		int place = gpu_fila * columnas + gpu_columma;
		gray[place] = (image[place].get_r() * 0.21 /*0.299*/) + (image[place].get_g() * 0.72/*0.587*/) + (image[place].get_b() * 0.07/*0.114*/);
	}
}




