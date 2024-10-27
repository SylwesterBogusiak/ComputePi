// Euler solution for Basel problem. Iterative algorithm for Pi approximation
// CPILE - COMPUTE PI LONG EULER'S
//
// Author: MARTE.BEST - Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o cpile cpile.c -lmpfr
// Usage:
// ./cpile 1000 1000

#include <stdio.h>
#include <mpfr.h> // for floating point mumbers
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
#else
#include <time.h>
#endif



int cpile(char *stop, unsigned int *bt)
{
mpfr_t i, n, one, two, div, sum, pi;
    
mpfr_inits2(*bt, i, n, one, two, div, sum, pi, NULL);
    
    
mpfr_set_str (n, stop, 10, MPFR_RNDD);
mpfr_sub_ui(n, n, 1, MPFR_RNDD);     // i - 1 as end, example 99 from 100 
mpfr_set_si (i, 0, MPFR_RNDD);
mpfr_set_d (one, 1.0, MPFR_RNDD);
mpfr_set_si (two, 2, MPFR_RNDD);
mpfr_set_si (div, 0, MPFR_RNDD);
mpfr_set_si (sum, 0, MPFR_RNDD);
  
      
while(mpfr_cmpabs(i,n)<0)

{
    	mpfr_add_si(i, i, 1, MPFR_RNDD); 
    	mpfr_pow(div, i, two, MPFR_RNDD);      
	mpfr_div(div,one,div,MPFR_RNDD);  
    	mpfr_add(sum,sum,div,MPFR_RNDD); 
    	
}   
        // print out last - 1 result
        
        mpfr_mul_si(pi, sum, 6, MPFR_RNDD);
        mpfr_sqrt(pi, pi, MPFR_RNDD);
        
        mpfr_printf ("\n===================\nPI for (n = %.*RZf): ",0,i);
    	mpfr_out_str (stdout, 10, *bt, pi, MPFR_RNDD);
    	printf ("\n===================\n\n");
        
    	// print out last result
     
    	mpfr_add_si(i, i, 1, MPFR_RNDD);
        mpfr_pow(div, i, two, MPFR_RNDD);      
	mpfr_div(div,one,div,MPFR_RNDD);  
    	mpfr_add(sum,sum,div,MPFR_RNDD); 
    	mpfr_mul_si(pi, sum, 6, MPFR_RNDD);
        mpfr_sqrt(pi, pi, MPFR_RNDD);
   
        mpfr_printf ("\n===================\nPI for (n = %.*RZf): ",0,i);
    	mpfr_out_str (stdout, 10, *bt, pi, MPFR_RNDD);
    	printf ("\n===================\n\n");
        
    
    
}


int main(int argc, char * argv[]){

	unsigned int b;

	char * i;
  	if (argc <= 2){
    	printf ("Usage: %s <number of iterations> <decimals>\n", argv[0]);
    	return 1;
  	}

  	i = argv[1];
  	b = atoi(argv[2]);

  	assert(i != NULL);
  
  	assert( b >= 1);
  
  	// Get system time START
  	#ifdef __APPLE__
    	uint64_t start = mach_absolute_time();
	#else
    	clock_t start = clock();
	#endif
  
	// Run the main procedure.
	cpile(i, &b);
	
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
