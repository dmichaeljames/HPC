#include <cstdlib>
#include <mpi.h>
#include <iostream>
#include <sstream>
#define MaxN 1000000


using namespace std;

int main (int argc, char **argv) {

	// Variables
	int N[3] = {100, 10000, 1000000};
	char *e; // for the strtol()
	int n;
	float x[MaxN];
	float y[MaxN];
	float xHold[MaxN], yHold[MaxN], dieAntwoord, endDotProd[MaxN];
	double starttime, endtime, totalTime;
	int sendcounts[MaxN];
	int displs[MaxN];
	int recvcounts;

	// Complaining if there is no command line argument made
	if (argc == 1) {
		cout << "No command line arguments made. Please select:\n0 = 100\n1 = 10000\n2 = 1000000" << endl;
		return EXIT_FAILURE;
	}

	// Setting b to the command line argument provided (0-2)
	else {
		long con = strtol(argv[1], &e, 10);
		int b = con;
		n = N[b]; // Pulling 100, 10000, or 1000000 from N[] based on CLA
	}

	// Initialize the vectors
	for (int i=0; i<MaxN; i++) {
		x[i] = 1.0;
		y[i] = 1.0;
		endDotProd[i] = 0.0;
	}

	// Initialize MPI
	MPI:: Init ( argc , argv );
	int nprocs = MPI::COMM_WORLD.Get_size();
	int rank = MPI::COMM_WORLD.Get_rank();

	// calculate vector size
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

	// Scatter the data to the wind
	MPI::COMM_WORLD.Scatterv(&x, sendcounts, displs, MPI::FLOAT, &xHold, recvcounts, MPI::FLOAT, 0);
	MPI::COMM_WORLD.Scatterv(&y, sendcounts, displs, MPI::FLOAT, &yHold, recvcounts, MPI::FLOAT, 0);

	// Figure out the answer for each process
	for (int i = 0; i<recvcounts; i++) {
		dieAntwoord += xHold[i] * yHold[i];
	}

	MPI::COMM_WORLD.Barrier();

	// Gather all of the data back to root
	MPI::COMM_WORLD.Gather(&dieAntwoord, 1, MPI::FLOAT, endDotProd, 1, MPI::FLOAT, 0);

	if (rank == 0) {
		float q = 0.0;

		// Calculate the dot product globally
		for (int i = 0; i<nprocs; i++) {
			q += endDotProd[i];
		}

		// Get the end time and compute total time
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
