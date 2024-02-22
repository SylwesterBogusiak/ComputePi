// Euler solution for Basel problem. Iterative algorithm for Pi approximation
// CPISE - COMPUTE PI STANDARD EULER'S
//
// Author: MARTE.BEST - Sylwester Bogusiak aka Sylvi91
// This is free code to calculate pi to an arbitrary degree of precision.
// There is no warranty or guarantee of any kind.
// 
// To Compile:
// gcc -o cpise cpise.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
#else
#include <time.h>
#endif



int cpise(unsigned long long int iters)
{
	unsigned long long int i;
	long double sum=0.0;
	long double pi=0.0;
	
	
	
    
  	/* Applying Standard Euler's Formula */
      
        for (i=1; i<(iters-1); i++)
    {
       
            sum += 1.0 / (pow(i, 2));
            
            
 
    }

  
        // print out last - 1 result
        
     	pi = 6.0 * sum;
    	pi = sqrt(pi);
        
        printf ("\n===================\nPI for (n = %llu): ",i);
    	printf (" %.20Lf",pi);
    	printf ("\n===================\n\n");
        
    
    	// print out last result
     
    	i++;
    	sum += 1.0 / (pow(i, 2));
    	pi = 6.0 * sum;
    	pi = sqrt(pi);
        
        printf ("\n===================\nPI for (n = %llu): ",i);
    	printf ("%.20Lf",pi);
    	printf ("\n===================\n\n");
        
    
    
  
}



int main(int argc, char * argv[]){

	

	unsigned long long int i;
	
	char * pEnd;
	
	
  	if (argc != 2){
    	printf ("Usage: %s <number of iterations>\n", argv[0]);
    	return 1;
  	}
  	
	
    	i = strtoull(argv[1], &pEnd, 10);
  
  	
        assert(i >=1);
  
  
  	// Get system time START
  	#ifdef __APPLE__
    	uint64_t start = mach_absolute_time();
	#else
    	clock_t start = clock();
	#endif
  	
  	// Run the main procedure.
  	
	cpise(i);
	
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
