// Calculate value of PI with use large numbers of Fibonacci sequence and phi value
// FTSPHIPI algorithm - Four Times Squared phi. pi = (4*sqrt(phi)) = 3.1446055110296931442782343433718357180924;
// More info about this value at JAIN ACADEMY: PHI-PI as the TRUE VALUE OF PI = 3.144 https://www.youtube.com/watch?v=mTqYxBdYa4k&list=PLC86GPii6Rb0O_HsAlRk5vDvjxZSMA6ao&index=1
// Author: Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi value to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o ftsphipi ftsphipi.c -lmpfr
// Usage in command line:
// ./ftsphipi 1000000000

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


int ftsphipi(char *stop){

   
    mpfr_t pi, f_n, f_n_minus_1, temp, n, i;
    mpfr_inits2(1000, pi, f_n, f_n_minus_1, temp, n, i, NULL);

    // Initialize Fibonacci numbers
    mpfr_set_ui(f_n, 1, MPFR_RNDN);
    mpfr_set_ui(f_n_minus_1, 0, MPFR_RNDN);

   // Compute consecutive Fibonacci numbers
   
   mpfr_set_si (i, 0, MPFR_RNDD);
   mpfr_set_str (n, stop, 10, MPFR_RNDD);


 while(mpfr_cmpabs(i,n)<0)
      
    {
    	mpfr_sub_si(i, i, 1, MPFR_RNDD);
        mpfr_add(temp, f_n, f_n_minus_1, MPFR_RNDN);
    

        // Swap Fibonacci numbers
        mpfr_set(f_n_minus_1, f_n, MPFR_RNDN);
        mpfr_set(f_n, temp, MPFR_RNDN);
        
    }
    
    
       // Compute Pi using Fibonacci numbers and phi number pi = (4*sqrt(phi))
        mpfr_div(pi, f_n_minus_1, f_n, MPFR_RNDN);
       	mpfr_sqrt(pi, pi, MPFR_RNDN);
       	mpfr_mul_ui(pi, pi, 4, MPFR_RNDN);

    	// Set the precision for the result
    	mpfr_prec_round(pi, 1000, MPFR_RNDN);
	
	mpfr_printf("\n For f(%.0RNf) Pi = ", i);   // decimal points
	
    	// Print the calculated value of Pi
    	mpfr_out_str(stdout, 10, 0, pi, MPFR_RNDN);
    	printf("\n");

    	// Clean up
    	mpfr_clears(pi, f_n, f_n_minus_1, temp, NULL);
}




int main(int argc, char * argv[]) {
  

 	//unsigned int b;

	char * i;
  	if (argc <= 1){
    	printf ("Usage: %s <number of iterations>\n", argv[0]);
    	return 1;
  	}

  	i = argv[1];

  	assert(i != NULL);
  
  

  // Get system time START

      	#ifdef __APPLE__

        uint64_t start = mach_absolute_time();

    	#else

        clock_t start = clock();

    	#endif

 
   
  	ftsphipi(i);  // Change the argument to adjust the number of iterations
    
 
 
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


    
    return 0;
}

// Bye, bye, My computer with Fibonacci compute Pi ;)

