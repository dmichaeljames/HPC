/* CSCI5850 - Final - Question 2(B): MPI Monte Carlo 
 * Name: Mike James
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include "mpi.h"

using namespace std;

int main (int argc, char *argv[]) {
	MPI::Init(argc, argv );
	MPI::Status status;
	int myid = MPI::COMM_WORLD.Get_rank();
	int nprocs = MPI::COMM_WORLD.Get_size();
	
	int N = 1E8;						
	double pi;							
	int sendcounts[N];					
	int vector_size = N/(nprocs-1);
	int remaining = N%(nprocs-1);
	int count[nprocs-1];
	int total_count = 0;
	double thyme = 0;
	double x,y,z;   					// x,y value for the random coordinates
	int hits = 0;  						// Counts good coordinates
	int n = 0;						// Iterations
		
	
	if (myid == 0) {
		// Determining data distribution
		for (int i = 0; i < (nprocs - 1); i++) {
			if (i < remaining) {
				sendcounts[i] = vector_size+1;
			}
			else {
				sendcounts[i] = vector_size;
			}
		}
		
		thyme = MPI::Wtime();
		
		// Distribution to worker nodes
		for (int i = 0; i < (nprocs - 1); i++) {
			MPI::COMM_WORLD.Send(&sendcounts[i], 1, MPI::INT, i+1, 0);
		}
		
		for (int i = 0; i < nprocs - 1; i++) {
			MPI::COMM_WORLD.Recv(&count[i], 1, MPI::INT, MPI::ANY_SOURCE, MPI::ANY_TAG);
			total_count += count[i];
		}
		
		pi = ((double)total_count / (double)N) * 4.0;
		
		thyme = MPI::Wtime() - thyme;
		
		cout << "For " << N << " iterations, pi was calculated as: " << pi << endl;
		cout << "The time it took to complete the simulation was: " << thyme << " seconds\n";
	
	}
	
	else {
		MPI::COMM_WORLD.Recv(&n,1,MPI::INT,MPI::ANY_SOURCE,MPI::ANY_TAG);
		
		srand(time(NULL));
		
		// Randomness
		for (int i = 0; i < n; i++) {
			x = (double)rand()/RAND_MAX;
			y = (double)rand()/RAND_MAX;
			z = sqrt((x * x) + (y * y));
			
			if (z <= 1) hits++;			// Checking to see if Z is inside
		}
		
		MPI::COMM_WORLD.Send(&hits, 1, MPI::INT, 0, 0);
    }	
	
	MPI::Finalize();

	return EXIT_SUCCESS;
}