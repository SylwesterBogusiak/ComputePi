// Calculate value of PI with use phi value
// FTSPHIPI2 algorithm - Four Times Squared phi. pi = (4*sqrt(phi)) = 3.1446055110296931442782343433718357180924;
// More info about this value at JAIN ACADEMY: PHI-PI as the TRUE VALUE OF PI = 3.144 https://www.youtube.com/watch?v=mTqYxBdYa4k&list=PLC86GPii6Rb0O_HsAlRk5vDvjxZSMA6ao&index=1
// Author: Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi value to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o ftsphipi2 ftsphipi2.c -lmpfr
// Usage in command line:
// ./ftsphipi2 1000
 
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


int ftsphipi2(int decimals){

   
    	mpfr_t pi, phi, temp;
    
    
    	mpfr_inits2(decimals, pi, phi, temp, NULL);
	
    	mpfr_sqrt_ui(phi, 5, MPFR_RNDN);
    	mpfr_sub_ui(phi, phi,  1, MPFR_RNDN);
    	mpfr_div_ui(phi, phi, 2, MPFR_RNDN);
    	
       // Compute Pi using phi number pi = (4*sqrt(phi))
     
       	mpfr_sqrt(pi, phi, MPFR_RNDN);
       	mpfr_mul_ui(pi, pi, 4, MPFR_RNDN);

    	// Set the precision for the result
    	mpfr_prec_round(pi, decimals, MPFR_RNDN);
	
    	// Print the calculated value of Pi

    	mpfr_printf("Pi = %.*RZf", decimals, pi);
    	printf("\n");

    	// Clean up
    	mpfr_clears(pi, phi, temp, NULL);
}




int main(int argc, char * argv[]) {
  

 	//unsigned int b;

	int d;
  	if (argc <= 1){
    	printf ("Usage: %s <precision>\n", argv[0]);
    	return 1;
  	}

  	
  	d = atoi(argv[1]);  // decimal places from 10 to 1000000 or more

   	assert( d >= 1);
  

  	// Get system time START

      	#ifdef __APPLE__

        uint64_t start = mach_absolute_time();

    	#else

        clock_t start = clock();

    	#endif

 
   
  	ftsphipi2(d);  // Change the argument to adjust the decimals
    
 
 
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

// Bye, bye, My computer with Phi compute Pi ;)
