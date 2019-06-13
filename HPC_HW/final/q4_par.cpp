// Mike James
// CSCI5850 Final
// Question 3: OMP quicksort

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;
 
void swap(int* a, int* b);
int partition (int array[], int start, int end);
void quicksort(int array[], int start, int end);
void printarray(int array[], int size);

// Global variable
const unsigned long int count = 1E8;
int array[count];
int threads[6] = {1,2,4,8,16,32};
int counter = 0;

int main(int argc, char *argv[]) {
	srand(time(0));											// Initialize the seed for the random number generator
	
	for (counter; counter < 4; counter++) {
		double time = omp_get_wtime();							// Start the clock
		
		cout << "Filling the array with random numbers...";		// Fill array with random numbers
		for (int i = 0; i < count; i++) {					
			array[i] = (rand() % 10) + 1;
		}
		cout << "DONE.\n\n";
		
		cout << "Beginning Quicksort...";						// Begin sorting the array
		quicksort(array, 0, count - 1);							
		cout << "DONE.\n\n";
		
		time = omp_get_wtime() - time;							// Stop the clock
		
		cout << "Sorted array: \n" << "TEMPORARILY ON HOLD\n\n";
		//printarray(array, count);									// Print the sorted array
		
		cout << "Time to finish: " << time << endl;
		cout << "Counter: " << counter << endl;
	}
	
	return 0;
}

void swap(int* start, int* end) {
    int temp = *start;
    *start = *end;
    *end = temp;
}

int partition (int array[], int start, int end) {
    int pivot = array[end];									// Setting the pivot
    int index = (start - 1); 							 	// Index of smaller element
	
	#pragma omp scheduled(static) parallel for num_threads(counter)
	for (int j = start; j <= end - 1; j++) {
		if (array[j] <= pivot) {
			index++;
			swap(&array[index], &array[j]);				// Swap the two numbers
		}
	}
	
	swap(&array[index + 1], &array[end]);
    return (index + 1);
}
 
void quicksort(int array[], int start, int end) {
	if (start < end) {
        int partIndex = partition(array, start, end);
	
        quicksort(array, start, partIndex - 1);			// Split the array around the pivot
		quicksort(array, partIndex + 1, end);
    }
}
 
void printarray(int array[], int size) {
    for (int i = 0; i < size; i++) {
	//for (int i = 0; i < size; i++) {
        if (i + 1 == size) {
			cout << array[i] << endl;
		}
		else {
			cout << array[i] << ", ";
		}		
	}
}