// CSCI5850 - Final - Q1(A)
// Mike James

#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <iostream>
#include <sstream>
#define MAX 2880

using namespace std;

int main (int argc, char **argv) {
	MPI::Init(argc, argv);
	
	int nprocs = MPI::COMM_WORLD.Get_size();
    int rank = MPI::COMM_WORLD.Get_rank();
	double totalTime = 0;
	char *e; // for the strtol()
	int n = MAX, right = 0, left = 0, down = 0, up = 0, c = 0;
	int N[3] = {4, 1440, 2880}, periods[] = {1,1}, dims[] = {nprocs, 1}, coords[2], displs[n], sendcounts[n*n], A[n][n], B[n][n], aHold[n], C[n];
	int recvcounts = sendcounts[rank];
				
	// Complaining if there is no command line argument made
	if (argc == 1) {
		cout << "No command line arguments made. Please select:\n0 = 4\n1 = 1440\n2 = 2880" << endl;
		return EXIT_FAILURE;
	}

	// Setting b to the command line argument provided (0-2)
	else {
		long con = strtol(argv[1], &e, 10);
		int b = con;
		n = N[b]; 
	}
	
	int vector_size = (n*n)/nprocs, remaining = (n*n)%nprocs; 
	
	if (n == 4) {	
		// Initialize the vectors (validation)
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
				A[i][j] = 1;
				B[i][j] = 1;
			}
		}
	}
	
	// Determine displacements and counts for scatterv
	int  k = 0;
	for (int i = 0; i < nprocs; i++) {
		if (i < remaining) {
			sendcounts[i] = vector_size + 1;
		}
		else {
			sendcounts[i] = vector_size;
		}
		 
		displs[i] = k;
		k = k + sendcounts[i];
	}
		
	if (rank == 0) totalTime = MPI::Wtime();	// Start the clock
		
	MPI::COMM_WORLD.Scatterv(&A, sendcounts, displs, MPI::INT, &aHold, recvcounts, MPI::INT, 0);
	MPI::COMM_WORLD.Bcast(&B, 1, MPI::INT, 0);

	MPI_Comm cannon;
	
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &cannon);
	MPI_Comm_rank(cannon,&rank);
	MPI_Cart_coords(cannon, rank, 2, coords);
	MPI_Cart_shift(cannon, 1, coords[0], &left, &right);
	MPI_Cart_shift(cannon, 0, coords[1], &up, &down);
	MPI_Sendrecv_replace(&aHold, 1 , MPI::INT, left, 11, right, 11, cannon, MPI_STATUS_IGNORE);
	MPI_Sendrecv_replace(&B, 1, MPI::INT, up, 11, down, 11, cannon, MPI_STATUS_IGNORE);
	
	// Figure out the answer for each process
	for (int i = 0; i < recvcounts; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				c += aHold[i] * B[j][k];
			}
		}
	}
	
	for(int i = 1; i < n; i++)
    {
		MPI_Cart_shift(cannon, 1, 1, &left, &right);
		MPI_Cart_shift(cannon, 0, 1, &up, &down);
		MPI_Sendrecv_replace(&aHold, 1 , MPI::INT, left, 11, right, 11, cannon, MPI_STATUS_IGNORE);
		MPI_Sendrecv_replace(&B, 1, MPI::INT, up, 11, down, 11, cannon, MPI_STATUS_IGNORE);
	 
		// Figure out the answer for each process
		for (int i = 0; i < recvcounts; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					c += aHold[i] * B[j][k];
				}
			}
		}
	}
	
	MPI_Barrier(cannon);
	
	MPI_Gather(&c, 1, MPI::INT, C, 1, MPI::INT, 0, cannon);
	if (rank == 0) {	
		int q = 0.0;
			
		// Calculate the dot product globally
		for (int i = 0; i < nprocs; i++) {
			q += C[i];
		}

		totalTime = MPI::Wtime() - totalTime;
		
		cout << "\nDot product(" << n << "): " << q
			 << "\nTime: " << totalTime << " seconds.\n"
			 << "Processors: " << nprocs << "\n\n";
	}
		
	MPI::Finalize();

	return(0);
}