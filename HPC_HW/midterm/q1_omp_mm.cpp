#include <cstdlib> 
#include <iostream> 
#include <iomanip> 
#include <omp.h>
#include <vector>

using namespace std; 

int n = 100, c = 10, t = 1;

int main (int argc, char *argv[])
{
	vector<vector<int> > A(n, vector<int>(n));
	vector<vector<int> > B(n, vector<int>(n));
	vector<vector<int> > C(n, vector<int>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = 1.0; 
			B[i][j] = 1.0;
			C[i][j] = 0;
		}
	}
	
	for (t = 1; t < 9; t *= 2) {
		cout << "Thread count is: " << t << "\n\n";
		
		double starttime = omp_get_wtime();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}

		double endtime = omp_get_wtime();
		double time = endtime - starttime;
		cout << setw(23) << "Serial time was: " << time << " seconds.\n";
	
		starttime = omp_get_wtime();
		
		#pragma omp parallel for schedule (static) num_threads(t)
				
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		
		endtime = omp_get_wtime();
		time = endtime - starttime;
		cout << setw(23) << "Static time was: " << time << " seconds.\n";
		
		starttime = omp_get_wtime();
		
		
		#pragma omp parallel for schedule (static,c) num_threads(t)
				
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		
		endtime = omp_get_wtime();
		time = endtime - starttime;
		cout << setw(23) << "Static (10) time was: " << time << " seconds.\n";
		
		starttime = omp_get_wtime();
		
		#pragma omp parallel for schedule (dynamic) num_threads(t)
				
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}

		cout << setw(23) << "Dynamic time was: " << time << " seconds.\n";
		
		starttime = omp_get_wtime();
		
		#pragma omp parallel for schedule (dynamic,c) num_threads(t)
				
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		
                endtime = omp_get_wtime();
		time = endtime - starttime;
		cout << setw(23) << "Dynamic (10) time was: " << time << " seconds.\n\n\n";
	}
	return 0;
}
