
// Machin-like formula Pi/4 = 4 arctan(1/5) - arctan(1/239)
// Author: MARTE.BEST - Sylwester Bogusiak aka Sylvi91
// More info about this formula: https://mathworld.wolfram.com/Machin-LikeFormulas.html
// This is free code to calculate pi to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// The mpfr library has further restrictions.
// To Compile:
// gcc -o mlpi mlpi.c -lmpfr
// Usage in command line:
// ./mlpi


#include <stdio.h>
#include <mpfr.h>

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>


int mlpi(){
   
   
    	mpfr_t one, five, twothreenine, temp, pi;
    	
    	mpfr_inits2(10000, one, five, twothreenine, temp, pi, NULL);

	mpfr_set_ui (one, 1, MPFR_RNDD);
	
    	mpfr_set_ui (five, 5, MPFR_RNDD);
    	
	mpfr_set_ui (twothreenine, 239, MPFR_RNDD);
	
	mpfr_div(temp,one,five, MPFR_RNDN);
	
	mpfr_atan (temp, temp, MPFR_RNDN);
		
	mpfr_mul_ui(temp,temp,4, MPFR_RNDN);
	
	mpfr_set(pi, temp, MPFR_RNDN);
	
   	mpfr_div(temp,one,twothreenine, MPFR_RNDN);
	
	mpfr_atan (temp, temp, MPFR_RNDN);
		
	mpfr_sub(pi, pi, temp, MPFR_RNDN);
	
	mpfr_mul_ui(pi, pi, 4, MPFR_RNDN);
	
	
	
		
		
    	//Print Out Answer
    	printf ("\n===================\nPI: ");
    	mpfr_out_str (stdout, 10, 0, pi, MPFR_RNDD);
    	printf ("\n===================\n\n");

    	mpfr_clears (one, five, twothreenine, temp, pi, NULL);
  
    	mpfr_free_cache ();
    	return 0;
}




int main(int argc, char * argv[]) {
  
	
  	time_t start; // system time var

  	time_t end; // system time var

  	time(&start); // Get the begining system time
   
  	mlpi();  // no iterations
    
  	time(&end); // Get the end system time

  	double dif;

	dif = difftime (end,start); // calculate the diff
	printf ("\nYour calculations took %.2lf seconds to run.\n", dif ); // time

    return 0;
}


