// Mike James
// CSCI5850 Final
// Question 3: OMP quicksort

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;
 
void swap(int* a, int* b);
int partition (int array[], int low, int high);
void quicksort(int array[], int low, int high);
void printarray(int array[], int size);

// Global variable
const long int count = 1E7;
int array[count];
// int threads[4] = {1,4,8,16};								        // For Q4 
int threads[4] = {1,2,4,8};
int counter = 0;

int main(int argc, char *argv[]) {
	srand(time(0));													// Initialize the seed for the random number generator
	
	//for (counter; counter < 4; counter++) {
		double time = omp_get_wtime();								// low the clock
		
		#pragma omp parallel for num_threads(8)
		for (int i = 0; i < count; i++) {							// Fill array with random numbers
			array[i] = (rand() % 10) + 1;
		}
		
		#pragma omp parallel default(none) shared(array) num_threads(8)
		{
			#pragma omp single nowait
			{
				quicksort(array, 0, count - 1);								// Sorting the array
			}
		}
		
		time = omp_get_wtime() - time;								// Stop the clock
		
		cout << "Time to finish: " << time << endl;
	//}
	
	return 0;
}

void swap(int* low, int* high) {
    int temp = *low;
    *low = *high;
    *high = temp;
}

int partition (int array[], int low, int high) {
    int pivot = array[high];											// Setting the pivot
    int index = (low - 1); 							 			// Index of smaller element
	int tick = threads[counter];
	
	#pragma omp parallel for num_threads(8) shared(array)
	for (int j = low; j <= high - 1; j++) {
		if (array[j] <= pivot) {
			index++;
			swap(&array[index], &array[j]);							// Swap the two numbers
		}
	}
	
	swap(&array[index + 1], &array[high]);
    return (index + 1);
}
 
void quicksort(int array[], int low, int high) {
	if (low < high) {
        int partIndex = partition(array, low, high);
		
		#pragma omp task firstprivate(low, partIndex)
		quicksort(array, low, partIndex - 1);					// Split the array around the pivot
		#pragma omp task firstprivate(high, partIndex)
		quicksort(array, partIndex + 1, high);					// Split the array around the pivot
    }
}
 
void printarray(int array[], int size) {
    for (int i = 0; i < size; i++) {
	    if (i + 1 == size) {
			cout << array[i] << endl;
		}
		else {
			cout << array[i] << ", ";
		}		
	}
}