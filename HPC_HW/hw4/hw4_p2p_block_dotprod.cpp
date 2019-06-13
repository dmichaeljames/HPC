#include <cstdlib>
#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
	MPI::Status status;
	MPI::Init(argc, argv);
		
	for (int N = 100; N <=1000000; N *= 100) {
		vector<float> x(N, 1);
		vector<float> y(N, 1);
		
		int myid = MPI::COMM_WORLD.Get_rank();
		
		if(myid == 0) {
		//	double starttime = MPI::Wtime();
			
			MPI::COMM_WORLD.Send(&N, 1, MPI::INT, 1, 0);
			MPI::COMM_WORLD.Send(&x[0], N, MPI::FLOAT, 1, 0);
			MPI::COMM_WORLD.Send(&y[0], N, MPI::FLOAT, 1, 0);
			
			float sum = 0.0;
			double time = 0.0;
			
			MPI::COMM_WORLD.Recv(&sum, 1, MPI::FLOAT, MPI::ANY_SOURCE, MPI::ANY_TAG);
			MPI::COMM_WORLD.Recv(&time, 1, MPI::DOUBLE, MPI::ANY_SOURCE, MPI::ANY_TAG);
					
		//	double endtime = MPI::Wtime();
					
			cout << "Dot product is: " << sum << " and it took " << time << " seconds." << endl;
		}
		
		else {
			double s = MPI::Wtime();
			
			MPI::COMM_WORLD.Recv(&N, 1, MPI::INT, MPI::ANY_SOURCE, MPI::ANY_TAG);
			MPI::COMM_WORLD.Recv(&x[0], N, MPI::FLOAT, MPI::ANY_SOURCE, MPI::ANY_TAG);
			MPI::COMM_WORLD.Recv(&y[0], N, MPI::FLOAT, MPI::ANY_SOURCE, MPI::ANY_TAG);
		
			float sum = 0.0;
			double time = 0.0;
			for (int j = 0; j < N; j++) {
				sum += (x[j] * y[j]);
			}
			
			double stop = MPI::Wtime();
			time = stop - s;

			MPI::COMM_WORLD.Send(&sum, 1, MPI::FLOAT, 0, 0);
			MPI::COMM_WORLD.Send(&time, 1, MPI::DOUBLE, 0, 0);
			
		}
	}
	MPI::Finalize();
		
	return EXIT_SUCCESS;

}
	
