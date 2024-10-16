// Calculate value of Pi with Phi and in opposite 
// FDSPHIPI algorithm - Four div by squared Phi Pi.  Pi = (4 / sqrt(Phi)) hence Phi = (4 / Pi)^2 = 1.618033
// More info about this value at JAIN ACADEMY: PHI-PI as the TRUE VALUE OF PI = 3.144 https://www.youtube.com/watch?v=mTqYxBdYa4k&list=PLC86GPii6Rb0O_HsAlRk5vDvjxZSMA6ao&index=1
// Author: Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi value to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o fdsphipi fdsphipi.c -lmpfr
// Usage in command line:
// ./fdsphipi  100

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


int fdsphipi(int decimals){

   
    	mpfr_t pi, phi, r_phi, temp;
    
    
    	mpfr_inits2(decimals, pi, phi, r_phi, temp, NULL);
	
    	mpfr_sqrt_ui(temp, 5, MPFR_RNDN);
    	mpfr_add_ui(temp, temp,  1, MPFR_RNDN);
    	mpfr_div_ui(phi, temp, 2, MPFR_RNDN); // Phi
    	
    	mpfr_printf("Phi 1 = %.*RZf", decimals, phi);
    	printf("\n");
    	
    	mpfr_sqrt(r_phi, phi, MPFR_RNDN);
    	
    	mpfr_printf("sqrt Phi 1 = %.*RZf", decimals, r_phi);
    	printf("\n");
    	
    	mpfr_ui_div(pi, 4, r_phi, MPFR_RNDN); // Phi
    	
    	
    	mpfr_printf("pi = %.*RZf", decimals, pi);
    	printf("\n");
    	
    	
    	mpfr_ui_div(temp, 4, pi, MPFR_RNDN); 
    	mpfr_pow_ui(phi, temp, 2, MPFR_RNDN);
    	
    	mpfr_printf("Phi 2 = %.*RZf", decimals, phi);
    	printf("\n");
    	
	
    	// Clean up
    	mpfr_clears(pi, phi, r_phi, temp, NULL);
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

 
   
  	fdsphipi(d);  // Change the argument to adjust the decimals
    
 
 
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

// Bye, bye, My computer with true Pi compute Phi ;)
