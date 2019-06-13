#include <cstdlib>
#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
	MPI::Status status;
	MPI::Init(argc, argv);
	
	int n = 1E8, numIter = 100;
	double x,y;   	// x,y value for the random coordinate
    int count=0;  	// Count holds all the number of how many good coordinates
	double z;	// Used to check if x^2+y^2<=1
	double pi;	// holds approx value of pi
	double total_pi; // holds sum of pi for averaging later
	double avg_pi;  // duh
	unsigned seed;	// seed change
	
	int myid = MPI::COMM_WORLD.Get_rank();
	
	if (myid == 0) {
		double starttime =  MPI::Wtime();

		MPI::COMM_WORLD.Send(&n, 1, MPI::INT, 1, 0);
		MPI::COMM_WORLD.Send(&x, 1, MPI::DOUBLE, 1, 0);
		MPI::COMM_WORLD.Send(&y, 1, MPI::DOUBLE, 1, 0);
		MPI::COMM_WORLD.Send(&count, 1, MPI::INT, 1, 0);
		MPI::COMM_WORLD.Send(&z, 1, MPI::DOUBLE, 1, 0);
		MPI::COMM_WORLD.Send(&seed, 1, MPI::UNSIGNED, 1, 0);
		
		double pi = -1;
		
		MPI::COMM_WORLD.Recv(&pi, 1, MPI::DOUBLE, MPI::ANY_SOURCE, MPI::ANY_TAG); 
		
		for (int a = 0; a < numIter; a++) {
			total_pi += pi;
		}

		avg_pi = total_pi/numIter;
		
		cout << "Average: " << avg_pi << "\n" << endl;
		double endtime = MPI::Wtime() - starttime;

		cout << endtime << " seconds." << endl;
		
		// Getting the serial time
		starttime =  MPI::Wtime();

		pi = -1;
		
		for (int i = 0; i < n; i++) {
			seed = ((int)time(NULL) + (i+100)*(MPI::COMM_WORLD.Get_size()+100));																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
			x = (double)rand_r(&seed)/RAND_MAX;
			y = (double)rand_r(&seed)/RAND_MAX;
			z = (x * x + y * y);
			if (z <= 1) count++;
		}
		
		pi = (static_cast<double>(count) / n) * 4;
		
		endtime = MPI::Wtime() - starttime;

		cout << endtime << " seconds for serial run." << endl;
		
	}
	
	else {
		MPI::COMM_WORLD.Recv(&n, 1, MPI::INT, MPI::ANY_SOURCE, MPI::ANY_TAG);
		MPI::COMM_WORLD.Recv(&x, 1, MPI::DOUBLE, MPI::ANY_SOURCE, MPI::ANY_TAG);
		MPI::COMM_WORLD.Recv(&y, 1, MPI::DOUBLE, MPI::ANY_SOURCE, MPI::ANY_TAG);
		MPI::COMM_WORLD.Recv(&count, 1, MPI::INT, MPI::ANY_SOURCE, MPI::ANY_TAG);
		MPI::COMM_WORLD.Recv(&z, 1, MPI::DOUBLE, MPI::ANY_SOURCE, MPI::ANY_TAG);
		MPI::COMM_WORLD.Recv(&seed, 1, MPI::UNSIGNED, MPI::ANY_SOURCE, MPI::ANY_TAG);
		
		for (int i = 0; i < n; i++) {
			seed = ((int)time(NULL) + (i+100)*(MPI::COMM_WORLD.Get_size()+100));																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
			x = (double)rand_r(&seed)/RAND_MAX;
			y = (double)rand_r(&seed)/RAND_MAX;
			z = (x * x + y * y);
			if (z <= 1) count++;
		}
		
		pi = (static_cast<double>(count) / n) * 4;
		
		MPI::COMM_WORLD.Send(&pi, 1, MPI::DOUBLE, 0, 0);
		
	}
	MPI::Finalize();
	
	return 0;
}
