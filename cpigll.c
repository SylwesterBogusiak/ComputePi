// Gauss - Legendre algorithm aka Brent - Salamin to compute Pi.
// More info: https://en.wikipedia.org/wiki/Gauss%E2%80%93Legendre_algorithm
// CPIGLL - Compute Pi Gauss Legendre Long
// Author: MARTE.BEST - Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o cpigll cpigll.c -lmpfr
// Usage in command line:
// ./cpigll 1000 1000


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


int cpigll(char *stop, int decimals){

    	mpfr_t pi, a, b, i, j, n, t, t2, p, temp, two;
    	mpfr_inits2(decimals, pi, a, b, i, j, n, t, t2, p, temp, two, NULL);

	
    
    	//Initialize the values according to the Gauss-Legendre algorithm.
    	mpfr_set_d (a, 1.0, MPFR_RNDD);
    	mpfr_set_d (b, 2.0, MPFR_RNDD);
    	mpfr_sqrt (b, b, MPFR_RNDD);
    	mpfr_ui_div (b, 1, b, MPFR_RNDD);
    	mpfr_set_d (t, 0.25, MPFR_RNDD);
    	mpfr_set_ui(p, 1, MPFR_RNDD);
     	mpfr_set_ui(two, 2, MPFR_RNDD);
  
    
    	mpfr_set_si (i, 0, MPFR_RNDD);
    	mpfr_set_si (j, 0, MPFR_RNDD);
    	mpfr_set_str(n, stop, 10, MPFR_RNDD);
    	mpfr_sub_si(n, n, 1, MPFR_RNDD); 
     
  
    
    

 while(mpfr_cmpabs(i,n)<0)
   
    {   
    	mpfr_sub_si(i, i, 1, MPFR_RNDD); // loop iteration
     	mpfr_add_si(j, j, 1, MPFR_RNDD); // helper
     
        mpfr_add (temp, a, b, MPFR_RNDD);
        mpfr_div_ui (temp, temp, 2, MPFR_RNDD);
 
        mpfr_mul (b, a, b, MPFR_RNDU);
        mpfr_sqrt (b, b, MPFR_RNDD);
 
        mpfr_sub (a, a, temp, MPFR_RNDD);
        mpfr_sqr (a, a, MPFR_RNDD);
        mpfr_mul (a, a, p, MPFR_RNDU);
        mpfr_sub (t, t, a, MPFR_RNDD);
 
        mpfr_set (a, temp, MPFR_RNDD);
        mpfr_mul (p,two,p, MPFR_RNDN);
        //p = 2 * p;
     
     
    }
    
    
    
        //Perform final calculation for last -1 number
    	mpfr_add (pi, a, b, MPFR_RNDD);
    	mpfr_sqr (pi, pi, MPFR_RNDD);

    	mpfr_mul_ui (t2, t, 4, MPFR_RNDU);

    	mpfr_div (pi, pi, t2, MPFR_RNDD);

    	//Print Out Last - 1 Answer
    	mpfr_printf("\n For n(%.0RNf) Pi =  ", j);   // decimal points
	
   
    	mpfr_out_str (stdout, 10, decimals, pi, MPFR_RNDD);
   
    	printf("\n");
    	
    	
    	//mpfr_sub_si(i, i, 1, MPFR_RNDD); // loop iteration
     	mpfr_add_si(j, j, 1, MPFR_RNDD); // loop iteration
     
        mpfr_add (temp, a, b, MPFR_RNDD);
        mpfr_div_ui (temp, temp, 2, MPFR_RNDD);
 
        mpfr_mul (b, a, b, MPFR_RNDU);
        mpfr_sqrt (b, b, MPFR_RNDD);
 
        mpfr_sub (a, a, temp, MPFR_RNDD);
        mpfr_sqr (a, a, MPFR_RNDD);
        mpfr_mul (a, a, p, MPFR_RNDU);
        mpfr_sub (t, t, a, MPFR_RNDD);
 
        mpfr_set (a, temp, MPFR_RNDD);
        mpfr_mul (p,two,p, MPFR_RNDN);
    	
    	//Perform final calculation for last number
    	mpfr_add (pi, a, b, MPFR_RNDD);
    	mpfr_sqr (pi, pi, MPFR_RNDD);

    	mpfr_mul_ui (t2, t, 4, MPFR_RNDU);

    	mpfr_div (pi, pi, t2, MPFR_RNDD);

    	//Print Out Last - 1 Answer
    	mpfr_printf("\n For n(%.0RNf) Pi =  ", j);   // decimal points
	
   
    	mpfr_out_str (stdout, 10, decimals, pi, MPFR_RNDD);
   
    	printf("\n");
    	
    	mpfr_const_pi(pi, MPFR_RNDD);
    	
    	//Print Out MPFR Canonical Pi value
    	mpfr_printf("\n MPFR Canonical Pi = ");   // decimal points
	
   
    	mpfr_out_str (stdout, 10, decimals, pi, MPFR_RNDD);
   
    	printf("\n");
    	
    	
    	

    	// Clean up

    	mpfr_clears(pi, a, b, i, j, n, t, t2, p, temp, two, NULL);
    	
    	return 0;
    	
}



int main(int argc, char * argv[]) {
  
	int  d;

    	char * i;

      	if (argc <= 2)
      	{

        printf ("Usage: %s <number of iterations> <number of decimal places>\n", argv[0]);

        return 1;

      	}


      	i = argv[1];

      	assert(i != NULL);


      	d = atoi(argv[2]);  // decimal places from 10 to 1000000 or more

   	assert( d >= 1);

 

 	// Get system time START

      	#ifdef __APPLE__

        uint64_t start = mach_absolute_time();

    	#else

        clock_t start = clock();

    	#endif

 
        cpigll(i,d);  // Change the argument to adjust the number of iterations

   
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

