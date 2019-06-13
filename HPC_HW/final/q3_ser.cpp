// Mike James
// CSCI5850 Final
// Question 3: Serial quicksort

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
 
// A utility function to swap two elements
void swap(int* a, int* b);
int partition (int array[], int low, int high);
void quicksort(int array[], int low, int high);
void printarray(int array[], int size);

int main(int argc, char *argv[]) {
    
	// Initialize variables
	int count = 10;
	int array[count];
		
	// Initialize the seed for the random number generator
	srand(time(0));
	
	// Fill arrayay with random numbers
	cout << "The unsorted array: \n";
	for (int i = 0; i < count; i++) {
		array[i] = (rand() % 10) + 1;
		if (i + 1 == count) {
			cout << array[i] << endl;
		}
		else {
			cout << array[i] << ", ";
		}		
	}
	int high = sizeof(array)/sizeof(array[0]);		// Getting the last element 
    quicksort(array, 0, high-1);
    cout << "Sorted array: \n";
    printarray(array, high);
    return 0;
}

void swap(int* low, int* high) {
    int temp = *low;
    *low = *high;
    *high = temp;
}

int partition (int array[], int low, int high) {
    int pivot = array[high];    // pivot
    int index = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (array[j] <= pivot) {
            index++;    // increment index of smaller element
            swap(&array[index], &array[j]);
        }
    }
    swap(&array[index + 1], &array[high]);
    return (index + 1);
}
 
void quicksort(int array[], int low, int high) {
    if (low < high) {
        int partIndex = partition(array, low, high);
 
        // Partition the array around the pivot and recursively sort until done 
        quicksort(array, low, partIndex - 1);
        quicksort(array, partIndex + 1, high);
    }
}
 
/* Function to print an arrayay */
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