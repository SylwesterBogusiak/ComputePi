// Calculate the approximation of value of Pi with use large numbers of Fibonacci sequence and/or Golden Phi number
// FFCPI algorithm - Fibonacci Fast Compute Pi
// Assuming that Pi = 6 * (Phi ^ 2) / 5
// we can have three versions of this algorithm
// FFCPI 1) Pi = (6 * (f(n) / f(n-1) ) ^ 2 ) / 5 
// FFCPI 2) Pi = 6 * ( ( (sqrt(5) + 1) / 2 ) ^ 2) / 5
// FFCPI 3) Pi = 6 * ( ( (sqrt(5) + 1) / 2 ) + 1) / 5
// Author: Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi value to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o ffcpi ffcpi.c -lmpfr
// Usage in command line:
// ./ffcpi 1000 1000

#include <stdio.h>
#include <mpfr.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
#else
#include <time.h>
#endif

int ffcpi1(char *stop, long long int decimals){

   
   	  mpfr_t pi, f_n, f_n_minus_1, temp, n, i;
   	  mpfr_inits2(decimals, pi, f_n, f_n_minus_1, temp, n, i, NULL);

   	  // Initialize Fibonacci numbers
   	  mpfr_set_ui(f_n, 1, MPFR_RNDN);
   	  mpfr_set_ui(f_n_minus_1, 0, MPFR_RNDN);

   	  // Compute consecutive Fibonacci numbers
   	  mpfr_set_si (i, 0, MPFR_RNDD);
   	  mpfr_set_str (n, stop, 10, MPFR_RNDD);


	    while(mpfr_cmpabs(i,n)<0)
 
    	{
    	mpfr_add_si(i, i, 1, MPFR_RNDD); //// or add_si
      mpfr_add(temp, f_n, f_n_minus_1, MPFR_RNDN);
    

      // Swap Fibonacci numbers
      mpfr_set(f_n_minus_1, f_n, MPFR_RNDN);
      mpfr_set(f_n, temp, MPFR_RNDN);
        
    	}
    
    
      // Compute Pi using Fibonacci numbers and other natural numbers
      mpfr_div(pi, f_n, f_n_minus_1, MPFR_RNDN);
      mpfr_sqr(pi, pi, MPFR_RNDN);
      mpfr_mul_ui(pi, pi, 6, MPFR_RNDN);
      mpfr_div_ui(pi, pi, 5, MPFR_RNDN);

      // Set the precision for the result
    	mpfr_prec_round(pi, decimals, MPFR_RNDN);

	    mpfr_printf("\n Pi = (6 * (f(n) / f(n-1) ) ^ 2 ) / 5  For f(%.0RNf) Pi = \n ", i);   // decimal points
	
    	// Print the calculated value of Pi
    	mpfr_printf("%.*RZf", decimals, pi);
    	
    	printf("\n");

    	// Clean up
    	mpfr_clears(pi, f_n, f_n_minus_1, temp, NULL);
}

int ffcpi2(long long int decimals)
{


	    mpfr_t pi, phi, temp;
   	  mpfr_inits2(decimals, pi, phi, temp, NULL);

	    // Compute Phi using (sqrt(5) + 1 ) / 2
    	mpfr_sqrt_ui(temp, 5, MPFR_RNDN);
    	mpfr_add_ui(temp, temp, 1, MPFR_RNDN);
    	mpfr_div_ui(phi, temp, 2, MPFR_RNDN);

    	// Compute Pi using Phi
    	mpfr_sqr(temp, phi, MPFR_RNDN);
    	mpfr_mul_ui(temp, temp, 6, MPFR_RNDN);
    	mpfr_div_ui(pi, temp, 5, MPFR_RNDN);
    	
    	 // Set the precision for the result
    	mpfr_prec_round(pi, decimals, MPFR_RNDN);
 
    	printf ("\n Pi = 6 * ( ( (sqrt(5) + 1) / 2 ) ^ 2) Pi = \n ");
 
    	// Print the calculated value of Pi
    	mpfr_out_str(stdout, 10, decimals, pi, MPFR_RNDN);
    	printf("\n");
 
    	// Clean up
    	mpfr_clears(pi, phi, temp, NULL);
    	
}

int ffcpi3(long long int decimals)
{


	    mpfr_t pi, phi, temp;
   	  mpfr_inits2(decimals, pi, phi, temp, NULL);

	    // Compute Phi using (sqrt(5) + 1 ) / 2
    	mpfr_sqrt_ui(temp, 5, MPFR_RNDN);
    	mpfr_add_ui(temp, temp, 1, MPFR_RNDN);
    	mpfr_div_ui(phi, temp, 2, MPFR_RNDN);

    	// Compute Pi using Phi
    	mpfr_add_d(temp, phi, 1.0, MPFR_RNDN);
    	mpfr_mul_ui(temp, temp, 6, MPFR_RNDN);
    	mpfr_div_ui(pi, temp, 5, MPFR_RNDN);
    	
    	 // Set the precision for the result
    	mpfr_prec_round(pi, decimals, MPFR_RNDN);
 
    	printf ("\n Pi = 6 * ( ( (sqrt(5) + 1) / 2 ) + 1) Pi = \n ");
 
    	// Print the calculated value of Pi
    	mpfr_out_str(stdout, 10, decimals, pi, MPFR_RNDN);
    	printf("\n");
 
    	// Clean up
    	mpfr_clears(pi, phi, temp, NULL);
    	
}


int main(int argc, char * argv[]){

	  long long int b;

	  char * i;
  	if (argc <= 2){
    	printf ("Usage: %s <number of iterations> <number of bits>\n", argv[0]);
    	return 1;
  	}

  	i = argv[1];
  	b = atoi(argv[2]);

  	assert(i != NULL);
  
  	assert( b >= 15);
  
  	// Get system time START
  	#ifdef __APPLE__
    	uint64_t start = mach_absolute_time();
	  #else
    	clock_t start = clock();
	  #endif
  	
  	// Run the main procedure.

	  ffcpi1(i, b);  // Change the argument to adjust the number of iterations and precision
	  ffcpi2(b);  // Change the argument to adjust precision
	  ffcpi3(b);  // Change the argument to adjust precision
	 
	  // Get system time END 
	  #ifdef __APPLE__
    	uint64_t end = mach_absolute_time();
    	mach_timebase_info_data_t timebase_info;
    	mach_timebase_info(&timebase_info);
    	long double diff = (end - start) * timebase_info.numer / timebase_info.denom; // nano sec
	
    	printf("Your calculations took %.3Lf seconds to run.\n", diff / 1e9 );
	  #else
    	clock_t end = clock();
    	printf("Your calculations took %.3Lf seconds to run.\n", (long double)(end - start) / CLOCKS_PER_SEC );
	  #endif
	
	
	  mpfr_free_cache ();
    
    return 0;
}
// Bye, bye, My computer with Fibonacci compute Pi ;) FCPI AKA FFCPI - fibonacci fast compute pi
