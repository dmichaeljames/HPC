33/* csci4850/5850 hw3 : calculate PI using Monte Carlo method
 * Name: Mike James
 * Date: 02/19/2018
 */

# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <ctime>
# include <cmath>
# include <omp.h>

using namespace std;

//****************************************************************************80
int main ( int argc, char *argv[] )
//****************************************************************************80
{
  int numIter;
  cout << "Please enter an integer iteration number: ";
  cin >> numIter;

  int randOption;
  cout << "Please select option function 1:rand 2:rand_r 3:drand48_r ";
  cin >> randOption;

  int numThreads;
  cout << "Please enter number of threads: ";
  cin >> numThreads;

  double x,y;   	// x,y value for the random coordinate
  int i;	    	// loop counter
  int count=0;  	// Count holds all the number of how many good coordinates
  double z;	    	// Used to check if x^2+y^2<=1
  double pi;		// holds approx value of pi
  unsigned seed;	// seed change
  struct drand48_data drand_buf;    // for drand RNG

  double time1 =  omp_get_wtime();

  // Complete your code for XXXXX
  switch (randOption) {
    case 1: 
      #pragma omp parallel private(z) num_threads(numThreads)
      {
        srand(time(NULL));
        #pragma omp for reduction(+:count)
        for (i=0; i<numIter; i++) {
          x = (double)rand()/RAND_MAX;
          y = (double)rand()/RAND_MAX;
          z = (x * x + y * y);
          if (z <= 1) count++;
        }
      }
      break;

    case 2: 
      #pragma omp parallel private(z) num_threads(numThreads)
      {
        #pragma omp for reduction(+:count)
        for (i=0; i<numIter; i++) {
          seed = ((int)time(NULL) + (i+100)*(omp_get_thread_num()+100));	// random seed change
          x = (double)rand_r(&seed)/RAND_MAX;
          y = (double)rand_r(&seed)/RAND_MAX;
          z = (x * x + y * y);
          if (z <= 1) count++;
        }
      }
      break;

    case 3: 
      #pragma omp parallel private(z) num_threads(numThreads)
      {
        #pragma omp for reduction(+:count)
        for (i=0; i<numIter; i++) {
          seed = ((int)time(NULL) * i * omp_get_thread_num());
          srand48_r (seed, &drand_buf);
          drand48_r (&drand_buf, &x);
		  drand48_r (&drand_buf, &y);
          z = (x * x + y * y);
          if (z <= 1) count++;
        }
      }
      break;
  }

  pi = (static_cast<double>(count) / numIter) * 4;
  
  double time2 = omp_get_wtime() - time1;

  cout << "  " << setw(15) << "n"
       << "  " << setw(15) << "Pi"
       << "  " << setw(15) << "time" << endl;

  cout << "  " << setw(15) << numIter
       << "  " << setw(15) << pi
       << "  " << setw(15) << time2 << endl;

  return 0;
}

