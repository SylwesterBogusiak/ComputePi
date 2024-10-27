// Madhava–Leibniz, Gottfried Wilhelm Leibniz iterative algorithm for Pi approximation
// CPILL1 - COMPUTE PI LONG LEIBNIZ V1
//
// Author: MARTE.BEST - Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o cpill1 cpill1.c -lmpfr
// Usage:
// ./cpill1 1000 1000

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


int cpill1(char *stop, unsigned int *bt){

/* Applying Classic Leibniz Formula V1 */
    
/*
 for(i=0;i< *stop;i++)
 {
  term = pow(-1, i) / (2*i+1);
  sum += term;
 }
 pi = 4 * sum;

 printf("\nPI = %.16lf \n", pi);
*/
 
 mpfr_t sum3, term3, pi3, i3, n3, x3, i2, one3,two3, power3, div3, div33;
    
 mpfr_inits2 (*bt, sum3, term3, pi3, i3, n3, x3, i2, one3, two3, power3, div3, div33, NULL);

 
  
   	mpfr_set_si (i3, 0, MPFR_RNDD);
 	mpfr_set_si(x3, 0, MPFR_RNDD);
 	mpfr_set_d (sum3, 0.0, MPFR_RNDD);
 	mpfr_set_d (term3, 0.0, MPFR_RNDD);
  	mpfr_set_d (div3, 0.0, MPFR_RNDD);
	mpfr_set_si (one3, -1, MPFR_RNDD);
 	mpfr_set_si (two3, 2, MPFR_RNDD);
	mpfr_set_d (pi3, 0.0, MPFR_RNDD);
	mpfr_set_str (n3, stop, 10, MPFR_RNDD);
	mpfr_sub_si(i2, n3, 1, MPFR_RNDD);
	

 while(mpfr_cmpabs(i3,i2)<0)
 
 {     
	mpfr_add_si(i3, i3, 1, MPFR_RNDD);

	mpfr_pow (power3, one3, x3, MPFR_RNDD);  
	mpfr_mul(div3, two3, x3, MPFR_RNDD);  
	mpfr_add_si(div3,div3,1,MPFR_RNDD);      
	mpfr_div(term3,power3,div3,MPFR_RNDD);           
   	mpfr_add(sum3,sum3,term3,MPFR_RNDD);        
   	mpfr_add_si(x3, x3, 1, MPFR_RNDD);

 }
  
    	//Print out last - 1 answer
    
	mpfr_mul_si(pi3,sum3,4,MPFR_RNDD);
    	mpfr_printf ("\n===================\nPI for (n = %.*RZf): ",0,i2);
    	mpfr_out_str (stdout, 10, *bt, pi3, MPFR_RNDD);
    	printf ("\n===================\n\n");
    
    	// Do one more step
	
  	mpfr_add_si(i3, i3, 1, MPFR_RNDD);
	mpfr_pow (power3, one3, x3, MPFR_RNDD);  
	mpfr_mul(div3, two3, x3, MPFR_RNDD);  
	mpfr_add_si(div3,div3,1,MPFR_RNDD);      
	mpfr_div(term3,power3,div3,MPFR_RNDD);           
   	mpfr_add(sum3,sum3,term3,MPFR_RNDD);        
   	mpfr_add_si(x3, x3, 1, MPFR_RNDD);
  	mpfr_mul_si(pi3,sum3,4,MPFR_RNDD);
  

    	//Print put last answer
	
    	mpfr_printf ("\n===================\nPI for (n = %.*RZf): ",0,i3);
    	mpfr_out_str (stdout, 10, *bt, pi3, MPFR_RNDD);
    	printf ("\n===================\n\n");
    
    	mpfr_clears (sum3, term3, pi3, i3, n3, x3, i2, one3,two3, power3, div3, div33, NULL);

    	return 0;
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
 	cpill1(i,&b);
	 
	 
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
