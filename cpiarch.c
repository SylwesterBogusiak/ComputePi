// Calculate the value of pi with use Archimedes method started from hexagon with side length equal to initiated radius value.
// Program is comparing Archimedes Pi with MPFR Canonical Pi.

// CPIARCH algorithm. Compute Pi - Archimedes algorithm

// Author: MARTE.BEST - Sylwester Bogusiak aka Sylvi91

// This is free code to calculate MPFR Canonical Pi and other Archimedes Pi value from polygons to an arbitrary degree of precision.

// There is no warranty or guarantee of any kind.

// The mpfr library has further restrictions.

// To Compile:

// gcc -o cpiarch cpiarch.c -lmpfr

// Usage in command line:

// ./cpiarch 1000 1000 1000  // bigger values gives better approximation

// More info at YouTube : 

// Finding Pi by Archimedes' Method https://www.youtube.com/watch?v=_rJdkhlWZVQ on MathWithoutBorders channel.

// Finding Pi by Archimedes' Method (Follow-up) https://www.youtube.com/watch?v=9zO0-QOcJQ0 on MathWithoutBorders channel.

//

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



int cpiarch(char *stop, int radius, int decimals)
{


        mpfr_t n, s1, s2, a, b, news, pin, pdin, pout, pdout, r, pow_r, temp1, temp2, temp3, i, six, sixtimes, div, pi, goldenpi, middlepi, threepi, archimedespi;

        mpfr_inits2(decimals, n, s1, s2, a, b, news, pin, pdin, pout, pdout, r, pow_r, temp1, temp2, temp3, i, six, sixtimes, div, pi, archimedespi, NULL);

    

        // a = sqrt(1-((b/2)^2)) = sqrt(1-0.25) = sqrt(0.75) = 0,866025404

        // b = 1 - a = 0,133974596

        // news = sqrt(b^2 + s2^2)

        // pin = six * s1,   

        // pout = pin * r/a

        // pdout = pout/2 = is PI oversized


        // Initialize hexagon and circle data

        mpfr_set_ui(r, radius, MPFR_RNDN);  // radius 1

        mpfr_set(s1, r, MPFR_RNDN);  // side s1 of hex = radius

	      mpfr_set_ui(six, 6, MPFR_RNDN);  // 6 sides

        mpfr_set_ui(sixtimes, 6, MPFR_RNDN);  // 6 sides

        mpfr_mul(pin, six, s1, MPFR_RNDN); // inner circumference 6 times s1

        mpfr_div_ui(s2, s1, 2, MPFR_RNDN);  // half of the side if s1 = 1 => s2 = 0.5

     	  mpfr_pow_ui(temp1, s2, 2, MPFR_RNDN); // s2 power to 2

    	  mpfr_pow_ui(pow_r, r, 2, MPFR_RNDN);

    	  mpfr_sub(temp2, pow_r, temp1, MPFR_RNDN);     // 1 -  (s/2)^2

    	  mpfr_sqrt(a, temp2, MPFR_RNDD);    // sqrt(1 - (s/2)^2)

 	      mpfr_sub(b, r, a, MPFR_RNDD);     // 1 -  (s/2)^2  // 1 - 0.866

	      // From Pythagorean theorem we can find the new polygon news side lenght value

    	  // news = sqrt(b^2 + s2^2)

    	  mpfr_pow_ui(temp3, b, 2, MPFR_RNDN);    // b^2

	      mpfr_add(temp3, temp1, temp3, MPFR_RNDN);  // (s2^2+b^2)

	      mpfr_sqrt(temp3,temp3,MPFR_RNDN);  // news

	      mpfr_set(news, temp3, MPFR_RNDN); 

 
        mpfr_mul_ui(div, r, 2, MPFR_RNDN);  // div = r * 2

       	// PIN Perimeter of inner polygon

       	mpfr_mul(pin, six, s1, MPFR_RNDN);

      	mpfr_div(pdin, pin, div, MPFR_RNDN);

      

        // POUT Perimeter of outer polygon

       	mpfr_div(temp1, r, a, MPFR_RNDN);

       	mpfr_mul(pout, pin, temp1, MPFR_RNDN);

      	mpfr_div(pdout, pout, div, MPFR_RNDN);

    

       	mpfr_printf("n            ,");

    	  mpfr_printf("s            ,");

    	  mpfr_printf("s/2          ,");

    	  mpfr_printf("a            ,");

    	  mpfr_printf("b            ,");

    	  mpfr_printf("new s        ,");

    	  mpfr_printf("p (in)       ,");

    	  mpfr_printf("p/d (in)     ,");

    	  mpfr_printf("p (out)      ,");

    	  mpfr_printf("p/d (out)     ");

    

        mpfr_printf("\n");

    	  mpfr_printf("%.0RNf,", sixtimes);

    	  mpfr_printf("%.0RNf,", s1);

    	  mpfr_printf("%.6RZf,", s2);

    	  mpfr_printf("%.*RZf,", decimals, a);

    	  mpfr_printf("%.*RZf,", decimals, b);

    	  mpfr_printf("%.*RZf,", decimals, news);

    	  mpfr_printf("%.*RZf,", decimals, pin);

    	  mpfr_printf("%.*RZf,", decimals, pdin);

    	  mpfr_printf("%.*RZf,", decimals, pout);

    	  mpfr_printf("%.*RZf", decimals, pdout);

    	  mpfr_printf("\n");

    
       	mpfr_set_si (i, 0, MPFR_RNDD);          // step

       	mpfr_set_str (n, stop, 10, MPFR_RNDD);  // limit of the loop

      

     	while(mpfr_cmpabs(i,n)<0)

 

        {   

        mpfr_sub_si(i, i, 1, MPFR_RNDD); //// or add_si

	      mpfr_mul_ui(sixtimes,sixtimes,2, MPFR_RNDN);  // 12  * 2 sides       

	      mpfr_set(s1, news, MPFR_RNDN);     //

	      mpfr_div_d(s2, s1, 2.0, MPFR_RNDN);     // s2 half of the side s1

	      mpfr_pow_ui(temp1, s2, 2, MPFR_RNDN); // temp1 power of 2

  	    mpfr_sub(temp2, pow_r, temp1, MPFR_RNDN);     // 1 -  (b/2)^2

	      mpfr_sqrt(a, temp2, MPFR_RNDN);    // sqrt(1 - (b/2)^2)

	      mpfr_sub(b, r, a, MPFR_RNDN);     // 1 -  sqrt(1 - (b/2)^2) // 1 - 0.866

    
    	  //From pythagorean theorem we can find the new polygon S/2 side lenght value

    	  //news = sqrt(b^2 + s2^2)

    	  mpfr_pow_ui(temp3, b, 2, MPFR_RNDN);    // b^2

    	  mpfr_add(temp3, temp1, temp3, MPFR_RNDN); 

    	  mpfr_sqrt(news,temp3,MPFR_RNDN);  // new s

    

    	  // PIN Perimeter of inner polygon

      	mpfr_mul(pin, sixtimes, s1, MPFR_RNDN);

       	mpfr_div(pdin, pin, div, MPFR_RNDN);

      
        // POUT Perimeter of outer polygon

      	mpfr_div(temp1, r, a, MPFR_RNDN);

      	mpfr_mul(pout, pin, temp1, MPFR_RNDN);

     	  mpfr_div(pdout, pout, div, MPFR_RNDN);

      

    	  /* Uncomment to print all results from the loop

    

    	mpfr_printf("%.0RNf,", sixtimes);

    	mpfr_printf("%.0RNf,", s1);

    	mpfr_printf("%.6RZf,", s2);

    	mpfr_printf("%.*RZf,", decimals, a);

    	mpfr_printf("%.*RZf,", decimals, b);

    	mpfr_printf("%.*RZf,", decimals, news);

    	mpfr_printf("%.*RZf,", decimals, pin);

    	mpfr_printf("%.*RZf,", decimals, pdin);

    	mpfr_printf("%.*RZf,", decimals, pout);

    	mpfr_printf("%.*RZf", decimals, pdout);

    	mpfr_printf("\n");

    

    

    	  */

    

    

    


        }

    

        /* Print out last result from the loop */

        mpfr_printf("%.0RNf,", sixtimes);

    	  mpfr_printf("%.0RNf,", s1);

    	  mpfr_printf("%.6RZf,", s2);

    	  mpfr_printf("%.*RZf,", decimals, a);

    	  mpfr_printf("%.*RZf,", decimals, b);

    	  mpfr_printf("%.*RZf,", decimals, news);

    	  mpfr_printf("%.*RZf,", decimals, pin);

    	  mpfr_printf("%.*RZf,", decimals, pdin);

    	  mpfr_printf("%.*RZf,", decimals, pout);

    	  mpfr_printf("%.*RZf", decimals, pdout);

    	  mpfr_printf("\n");

    

    

        mpfr_const_pi(pi, MPFR_RNDN);  // MPFR Canonical Pi computed with Brent Salamin formula


    	  mpfr_add(archimedespi, pdout, pdin, MPFR_RNDN); // Archimedes Pi (Outer Pi from polygon + Inner Pi from polygon) / 2

    	  mpfr_div_d(archimedespi, archimedespi, 2.0, MPFR_RNDN); 

  
        mpfr_printf("Final results for the polygon with n sides where n = %.0RZf:", sixtimes);

        mpfr_printf("\n");

        mpfr_printf("MPFR Canonical Pi %.*RZf", decimals, pi);

     	  mpfr_printf("\n");

        mpfr_printf("Archimedes Pi     %.*RZf", decimals, archimedespi);

        mpfr_printf("\n");

       
        // MPFR Canonical Pi

        
        if(mpfr_cmpabs(pi,pdin)>0)

        {

        mpfr_printf("MPFR Canonical Pi value higher  than inner Pi derived from polygon. OK.");

        mpfr_printf("\n");

        }

        else

        {

        mpfr_printf("MPFR Canonical Pi value lower than inner Pi derived from polygon. BAD!");

        mpfr_printf("\n");

        }

    

        if(mpfr_cmpabs(pi,pdout)<0)

        {

        mpfr_printf("MPFR Canonical Pi value lower than outer Pi derived from polygon. OK.");

        mpfr_printf("\n");

        }

        else

        {

        mpfr_printf("MPFR Canonical Pi value higher than outer Pi derived from polygon. BAD!.");

        mpfr_printf("\n");

        }

    

    

       if(mpfr_cmpabs(pi,archimedespi)<0)

        {

        mpfr_printf("MPFR Canonical Pi is lower than Archimedes Pi derived from 2 polygons (outer and inner). Why? Test more.");

        mpfr_printf("\n");

        }

        

        if(mpfr_cmpabs(pi,archimedespi)>0)

        {

        mpfr_printf("MPFR Canonical Pi is higher than Archimedes Pi derived from 2 polygons (outer and inner). Why? Test more.");

        mpfr_printf("\n");
			
	}


    

        if(mpfr_cmpabs(pi,pdin)==0)

        {

        mpfr_printf("MPFR Canonical Pi equal to inner Pi derived from polygon. SUPER.");

        mpfr_printf("\n");

        }

    

        if(mpfr_cmpabs(pi,pdout)==0)

        {

        mpfr_printf("MPFR Canonical Pi equal to outer Pi derived from polygon. SUPER.");

        mpfr_printf("\n");

        }

        

        if(mpfr_cmpabs(pi,archimedespi)==0)

        {

        mpfr_printf("MPFR Canonical Pi equal to Archimedes Pi derived from polygon. SUPER.");

        mpfr_printf("\n");

        }

    


    	  // Clean up

    	  mpfr_clears(n, s1, s2, a, b, news, pin, pdin, pout, pdout, r, pow_r, temp1, temp2, temp3, i, six, sixtimes, div, pi, archimedespi, NULL);

}



int main(int argc, char * argv[]) {

 
        int r, d;

    	  char * i;

      	if (argc <= 3)
      	{

        printf ("Usage: %s <number of iterations> <radius of the circle> <number of decimal places>\n", argv[0]);

        return 1;

      	}


      	i = argv[1];

      	assert(i != NULL);

    	  r = atoi(argv[2]);  // radius of the circle from 1 to MAX_LONG_INT

    	  assert( r >= 1);

      	d = atoi(argv[3]);  // decimal places from 10 to 1000000 or more

   	    assert( d >= 1);

 

 	      // Get system time START

      	#ifdef __APPLE__

        uint64_t start = mach_absolute_time();

    	  #else

        clock_t start = clock();

    	  #endif

 

        cpiarch(i, r, d);  // Change the argument i to adjust the number of iterations and change argument r to set radius of the circle and change argument d for decimal precision of the values of variables

    
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
