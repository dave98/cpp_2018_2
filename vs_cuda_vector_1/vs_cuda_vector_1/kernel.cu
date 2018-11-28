
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <iostream>

#define CUDA_CALLABLE_MEMBER __host__ __device__
#define BLUR_SIZE = 3

using namespace std;
using namespace cv;

class OpenCVUnit
{
public:
	float r;
	float g;
	float b;
	
	CUDA_CALLABLE_MEMBER OpenCVUnit(float r_, float g_, float b_) {
		this->r = r_;
		this->g = g_;
		this->b = b_;
	}

	CUDA_CALLABLE_MEMBER OpenCVUnit() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}

	CUDA_CALLABLE_MEMBER void set_r(float r_) { this->r = r_; }
	CUDA_CALLABLE_MEMBER void set_g(float g_) { this->g = g_; }
	CUDA_CALLABLE_MEMBER void set_b(float b_) { this->b = b_; }

	CUDA_CALLABLE_MEMBER float get_r() { return this->r; }
	CUDA_CALLABLE_MEMBER float get_g() { return this->g; }
	CUDA_CALLABLE_MEMBER float get_b() { return this->b; }
};


void change_to_gray(OpenCVUnit* , float* , unsigned int , unsigned int );
void change_to_blur(OpenCVUnit*, OpenCVUnit*, unsigned int, unsigned int);

__global__ void change_to_gray_kernel(OpenCVUnit*, float*, unsigned int, unsigned int);
__global__ void change_to_blur_kernel(OpenCVUnit*, OpenCVUnit*, unsigned int, unsigned int);

void print_matrix(OpenCVUnit*, int, int);
void print_matrix(float*, int, int);
void set_matrix_zero(float*, int, int);


//Main 
int main()
{

	Mat image_in = imread("zombie_1.png", IMREAD_COLOR);
	if (image_in.empty()) {
		cout << "No se pudo leer la imagen" << endl;
		return 0;
	}

	unsigned int columnas = image_in.cols;
	unsigned int filas = image_in.rows;

	cout << "Columnas: " << columnas << " -- " << "Filas: " << filas << endl;

	OpenCVUnit* pixels_in = new OpenCVUnit[columnas * filas]; //Pool for pixels from image
	
	float* pixel_out = new float[columnas *  filas]; //For gray image
	OpenCVUnit* blur_image = new OpenCVUnit[columnas * filas]; //For Blur image;


	for (int i = 0; i < filas; i++) { //Copiar datos dentro de matriz de pixeles
		for (int j = 0; j < columnas; j++) {
			pixels_in[i*columnas + j].set_r((float)image_in.at<Vec3b>(i, j)[0]);
			pixels_in[i*columnas + j].set_g((float)image_in.at<Vec3b>(i, j)[1]);
			pixels_in[i*columnas + j].set_b((float)image_in.at<Vec3b>(i, j)[2]);
		}
	}

	//Tratamiento de la imagen 
	change_to_gray(pixels_in, pixel_out, columnas, filas); ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	change_to_blur(pixels_in, blur_image, columnas, filas);
	
	Mat image_out(filas, columnas, CV_8UC3); //For Gray
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			image_out.at<Vec3b>(i, j)[0] = pixel_out[i*columnas + j];
			image_out.at<Vec3b>(i, j)[1] = pixel_out[i*columnas + j];
			image_out.at<Vec3b>(i, j)[2] = pixel_out[i*columnas + j];
		}
	}

	Mat image_blur(filas, columnas, CV_8UC3); //For Gray
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			image_blur.at<Vec3b>(i, j)[0] = blur_image[i*columnas + j].get_r();
			image_blur.at<Vec3b>(i, j)[1] = blur_image[i*columnas + j].get_g();
			image_blur.at<Vec3b>(i, j)[2] = blur_image[i*columnas + j].get_b();
		}
	}

	namedWindow("Entrada", WINDOW_NORMAL);
	imshow("Entrada", image_in);

	namedWindow("Gray", WINDOW_NORMAL);
	imshow("Gray", image_out);


	namedWindow("Blur", WINDOW_NORMAL);
	imshow("Blur", image_blur);

	waitKey(0);
	destroyWindow("Entrada");
	destroyWindow("Gray");
	destroyWindow("Blur");

	delete pixels_in;
	delete pixel_out;
	return 0;
}

//Configuration for CUDA deployment
void change_to_gray(OpenCVUnit* h_pixels_in, float* h_out, unsigned int h_columnas, unsigned int h_filas) {
	OpenCVUnit* d_pixels_in;
	float* d_out;

	//Imprimiendo matriz//HERE
	//print_matrix(h_pixels_in, h_filas, h_columnas);
	//print_matrix(h_out, h_filas, h_columnas);

	int size_of_pixel_max = h_columnas * h_filas * sizeof(OpenCVUnit);
	int size_of_float_max = h_columnas * h_filas * sizeof(float);

	cudaMalloc((void** ) &d_pixels_in, size_of_pixel_max);
	cudaMalloc((void**) &d_out, size_of_float_max);
	cudaMemcpy(d_pixels_in, h_pixels_in, size_of_pixel_max, cudaMemcpyHostToDevice);

	//print_matrix(d_pixels_in, h_filas, h_columnas);

	float block = 32;
	dim3 size_grid(ceil(h_columnas / block), ceil(h_filas / block), 1);
	dim3 size_block(block, block, 1);				
	
	cout << "Dimensiones de Grid: [" << size_grid.x << " - " << size_grid.y << " - " << size_grid.z << "]  Size Block: [" << size_block.x << " - " << size_block.y << " - " << size_block.z << "] " << endl;

	change_to_gray_kernel<<< size_grid, size_block >>>(d_pixels_in, d_out, h_columnas, h_filas);

	cudaMemcpy(h_out, d_out, size_of_float_max, cudaMemcpyDeviceToHost);

	//print_matrix(h_out, h_filas, h_columnas);
	cudaFree(d_pixels_in);
	cudaFree(d_out);
}

void change_to_blur(OpenCVUnit* img_in, OpenCVUnit* img_out, unsigned int columnas, unsigned int filas) {
	unsigned img_size = columnas * filas * sizeof(OpenCVUnit);

	OpenCVUnit* d_img_in;
	OpenCVUnit* d_img_out;

	cudaMalloc((void**)&d_img_in, img_size);
	cudaMalloc((void**)&d_img_out, img_size);

	cudaMemcpy(d_img_in, img_in, img_size, cudaMemcpyHostToDevice);
	float block = 32;
	dim3 size_grid(ceil(columnas / block), ceil(filas / block), 1);
	dim3 size_block(block, block, 1);

	change_to_blur_kernel <<< size_grid, size_block >>> (d_img_in, d_img_out, columnas, filas);

	cudaMemcpy(img_out, d_img_out, img_size, cudaMemcpyDeviceToHost);
	cudaFree(d_img_in);
	cudaFree(d_img_out);
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
1

__global__ void change_to_blur_kernel(OpenCVUnit* image, OpenCVUnit* blur, unsigned int columnas, unsigned int filas) {
	unsigned int gpu_columna = threadIdx.x + (blockIdx.x * blockDim.x);
	unsigned int gpu_fila = threadIdx.y + (blockIdx.y *  blockDim.y);

	if (gpu_columna < columnas && gpu_fila < filas) {
		int blur_size = 3;
		float in_r = 0.0;
		float in_g = 0.0;
		float in_b = 0.0;
		float size = 0;

		int in_fila, in_columna;
		for (int _fila = -blur_size; _fila < (blur_size + 1); _fila++) {
			for (int _col = blur_size; _col < blur_size + 1; _col++) {
				in_fila = gpu_fila + _fila;
				in_columna = gpu_columna + _col;
				if ( (in_fila > -1 && in_fila < filas) && (in_columna > -1 && in_columna < columnas) ) {
					in_r += image[(in_fila*columnas) + in_columna].get_r();
					in_g += image[(in_fila*columnas) + in_columna].get_g();
					in_b += image[(in_fila*columnas) + in_columna].get_b();
					size += 1;
				}
			}
		}

		blur[(gpu_fila*columnas) + gpu_columna].set_r(in_r / size);
		blur[(gpu_fila*columnas) + gpu_columna].set_g(in_g / size);
		blur[(gpu_fila*columnas) + gpu_columna].set_b(in_b / size);
	}
}


void print_matrix(OpenCVUnit* matriz, int fila, int columna) {
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < columna; j++) {
			cout << "[ " << matriz[i*columna + j].get_r() << " - " << matriz[i*columna + j].get_g() << " - " << matriz[i * columna + j].get_b() << " ]";
		}
	}
}

void print_matrix(float* matriz, int fila, int columna) {
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < columna; j++) {
			cout << "[ " << matriz[i * columna +  j] <<" ]";
		}
	}
}


void set_matrix_zero(float* matriz, int fila, int columna) {
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < columna; j++) {
			matriz[i*columna + j] = 0;
		}
	}
}