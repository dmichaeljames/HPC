// CSCI5850 - Final - Q1(A)
// Mike James

#include <cstdlib>
#include <mpi.h>
#include <iostream>
#include <sstream>
#define MaxN 2880

using namespace std;

double cannon();

int main (int argc, char **argv) {

	// Initialize variables
	
	// Iterations 
	int N[3] = {4, 1440, 2880};
	
	// CLA
	char *e; // for the strtol()
	int n;
	
	// Root matricies
	int A[MaxN][MaxN],B[MaxN][MaxN],C[MaxN][MaxN];
	
	// Worker matricies and variables
	int aHold[MaxN][MaxN], bHold[MaxN][MaxN], c;
	
	// Timer
	int starttime, endtime, totalTime;
	
	// Distribution
	int sendcounts[MaxN];
	int displs[MaxN];
	int recvcounts;

	// No CLA? No play!
	if (argc == 1) {
		cout << "No command line arguments made. Please select:\n0 = 4\n1 = 1440\n2 = 2880" << endl;
		return EXIT_FAILURE;
	}

	// Iteration selection via CLA
	else {
		long con = strtol(argv[1], &e, 10);
		int b = con;
		n = N[b]; // Pulling 4, 1440, or 2880 from N[] based on CLA
	}
	
	// Initialize the vectors (validation)
	if (n == 4) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * n + j;
				B[i][j] = i * n + j;
			}
		}
	}

	// Initialize the vectors (analysis)
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = B[i][j] = 1;
			}
		}
	}
	
	// Initialize MPI and dependent variables
	MPI::Init(argc, argv);
	int nprocs = MPI::COMM_WORLD.Get_size();
	int rank = MPI::COMM_WORLD.Get_rank();

	// Calculate vector size
    int vector_size = n/nprocs;
    int remaining = n%nprocs;

	// Determine displacements and counts for scatterv
	int  k = 0;
  	for (int i=0; i<nprocs; i++) {
      		if (i<remaining) {
			sendcounts[i] = vector_size+1;
      		}
		else {
			sendcounts[i] = vector_size;
		}
      		displs[i] = k;
      		k = k+sendcounts[i];
 	}
	recvcounts = sendcounts[rank];

	// Start the clock
	if (rank == 0) {
		starttime = MPI::Wtime();
	}
	
	------------------------------------------------------------

	// Scatter A[] to the wind
	MPI::COMM_WORLD.Scatterv(&A, sendcounts, displs, MPI::INT, &aHold, recvcounts, MPI::INT, 0);
	
	// Broadcast B[] to everyone
	MPI::COMM_WORLD.Bcast(&B, 1, MPI::INT, 0);
	
	// Figure out the answer for each process
	for (int i = 0; i<recvcounts; i++) {
		for (int j = 0; j < n*n; j++) {
			c += aHold[i] * bHold[j];
		}
	}
	---------------------------------------------------------------------------

	// Call Cannon's Algorithm
	cannon();
	
	// Waiting patiently for all workers to finish
	MPI::COMM_WORLD.Barrier();

	// Gather all of the data back to root
	MPI::COMM_WORLD.Gather(&c, 1, MPI::INT, C, 1, MPI::INT, 0);

	// Putting it all back together	
	if (rank == 0) {
		int q = 0.0;

		// Calculate the dot product
		for (int i = 0; i<nprocs; i++) {
			q += C[i];
		}

		// Stop the clock and calculate total time
		endtime = MPI::Wtime();
		totalTime = endtime - starttime;

		// Print the results
		cout << "\n\nThe dot product for " << n << " is: " << q
		     << "\nTime to complete was: " << totalTime << " seconds.\n"
		     << "The number of processors was: " << nprocs << "\n\n\n";
	}

	MPI::Finalize();

	return(0);
}

double cannon(int A[][], int B[][]) {

	// Initialize variables
	int sum = 0;
	
	for (int k = 0; k < 3; k++) {					// 3 Shifts of Cannon's Algorithm
		if (k == 0) {								// Initial shift 0 through k
			for (int row = 0; row < n; row++) {
				for (int col = 0; col < n; col++) {
					if (col 
				}
			}
		}
	}
}

int leftSwap(x,y) {
	
}

int rightSwap(x,y) {
	
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
