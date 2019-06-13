/* CSCI5850 - Final - Question 2(A): Serial Monte Carlo 
 * Name: Mike James
 */

# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <ctime>
# include <cmath>

using namespace std;

int main (int argc, char *argv[]) {
	double numIter;
	cout << "Please enter an iteration value: ";
	cin >> numIter;

	double x,y;   	// x,y value for the random coordinate
	int i;	    	// loop counter
	int count=0;  	// Counts good coordinates
	double z;	    // Used to check if x^2+y^2 <= 1 (inner circle)
	double pi;		// holds approx value of pi (count / numItr)


	clock_t begin = clock();		// Start the clock

	// Randomness
	for (i = 0; i < numIter; i++) {
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		z = (x * x + y * y);
		
		if (z <= 1) count++;		// Checking to see if Z is inside
    }
    
    // Calculating pi from our randomness
    // Number of hits inside the circle (count)
    // Divided by the total randomness (numIter)
	pi = (static_cast<double>(count) / numIter) * 4;

	clock_t end = clock();			// Stop the clock
	
	double elapsedTime = double(end - begin) / CLOCKS_PER_SEC;

	cout << "  " << setw(12) << "iterations"
		 << "  " << setw(12) << "pi (calc)"
		 << "  " << setw(12) << "time" << endl;

	cout << "  " << setw(12) << numIter
		 << "  " << setw(12) << pi
		 << "  " << setw(12) << elapsedTime << endl;

	return 0;
}

