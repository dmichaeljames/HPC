// Homework 8: CUDA implementation
// Mike James
// 5/3/2018

#include <cstdlib>
#include <stdio.h>
#define max 1024
#define elements 2

__global__ void dotprod(float *x, float *y, float *k, int *i) {
	float sum = 0.0;
	for (int m = 0; m < *i; m++) {
		sum = x[m] * y[m];
		__syncthreads();
		*k = *k + sum;
	}
}

int main(int argc, char *argv[]) 
{
	// Host variables
	unsigned int N[elements] = {100, 1024};
	float x[max], y[max];
	int i = 0, j = 0, intSize = 0;
	float k = 0.0, size = 0.0; 
	
	// Calculate the total size of "size"
	size = sizeof(float);
	intSize = sizeof(int);
	
	// GPU variables
	float *d_x, *d_y, *d_k;
	int *d_i;

	// Adjusting the size
	i = N[atoi(argv[1])];	// Setting "i" equal to N[x] based on the CLA (0 or 1)
	size = i * size;		// Recalculating "size" by taking the size of a float times the number of items in N[x]
	intSize = i * intSize;	// Recalculating "size" "  "      "   "    "  " int   "     "   "      "  "     "  "
	
	// initialize data (x and y)
	for (j = 0; j < max; j++) {
		x[j] = y[j] = 1.0;
		//x[j] = 1.0;
		//if (j%2 == 0) {
		//	y[j] = 1.0;
		//}
		//else {
		//	y[j] = 2.0;
		//}
	}
		
	// GPU variable allocation
	cudaMalloc((void **)&d_x, size); 
	cudaMalloc((void **)&d_y, size); 
	cudaMalloc((void **)&d_k, size);
	cudaMalloc((void **)&d_i, intSize);
	
	// send partial data to GPU
	cudaMemcpy(d_x, &x, size, cudaMemcpyHostToDevice); 
	cudaMemcpy(d_y, &y, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_i, &i, intSize, cudaMemcpyHostToDevice);

	// Launching kernel on GPU
	dotprod<<<1,i>>>(d_x, d_y, d_k, d_i); 
	
	// Collect everything back to Host
	cudaMemcpy(&k, d_k, size, cudaMemcpyDeviceToHost); 
	
	// Answer
	printf ("k = %f\n\n", k);
	
	// Clean up after CUDA
	cudaFree(d_x); 
	cudaFree(d_y); 
	cudaFree(d_k); 
	cudaFree(d_i);

	return 0;
}
