#include <cstdlib>
#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char **argv) {
	
	// Variables
	int N = 4; // determines matrix size (N * N)
	double B[N][N]; // matrix
	double C[N]; // vector_1
	double A[N]; // vector_2 aka Die Antwoord
	double ACell = 0.0; // holds calculated answer per 
	double BCell[N]; // for holding the value of B-matrix
	double CCell = 0.0;
	double count = 0.0;

	// Initialize MPI
	MPI:: Init ( argc , argv );
	int nproc = MPI::COMM_WORLD.Get_size(); 
	int rank = MPI::COMM_WORLD.Get_rank();
	
	// Creating two MPI blank datatypes
	MPI::Datatype mpi_vector, mpi_resized_vector;   	
	
	// Populate vectors with values
	if (rank == 0) { 
		// Initialize the vectors
		for (int i=0; i<N; i++) {
			C[i] = 1.0; // All "1.0"
			A[i] = 0.0; // All "0.0"
			BCell[i] = 0.0; // All "0.0"
			for (int j = 0; j < N; j++) { 
				B[i][j] = count + 1.0; // 1 ~ N*N (16 for this run).
				count++;
			} 
		}
	}

	// creates a vector of ((number of blocks, block length, stride(number of elements between beginning and end of blocks))) 
	//
	// |X|-|-|-|X|-|-|-|X|-|-|-|X|-|-|-|
	mpi_vector = MPI::DOUBLE.Create_vector(N,1,N); 
	mpi_vector.Commit();
		
	// Lower bound and extent (range from lb to ub) added to mpi_vector
	mpi_resized_vector = mpi_vector.Create_resized(0,1*sizeof(double));
	mpi_resized_vector.Commit(); 

	// MPI::COMM_WORLD.Scatter(&sendbuf, int count, sendtype, &recvbuf, int count, recvtype, int root)
	MPI::COMM_WORLD.Scatter(&B, 1, mpi_resized_vector, &BCell, N, MPI::DOUBLE, 0);
	MPI::COMM_WORLD.Scatter(&C, 1, MPI::DOUBLE, &CCell, 1, MPI::DOUBLE, 0);
	
	// Calculating the answer (A) from received data
	// Everyything up to and including this part works as expected.
	// ACell gets the correct value for each rank (at least with p = 4)
	for (int i=0; i<N; i++) {
		ACell += BCell[i] * CCell;
	}	
	
	MPI::COMM_WORLD.Barrier();

	// Gather up all the ACells and fill Die Antwoord
	MPI::COMM_WORLD.Gather(&ACell, 1, MPI::DOUBLE, &A, 1, MPI::DOUBLE, 0);

	// Print results to console
	if (rank == 0) {
		cout << "Results:\n" << endl;
		for (int i = 0; i < N; i++) {
			cout << "A[" << A[i] << "]\n";
		}
	}
	
	MPI::Finalize();
	
	return 0;
}
