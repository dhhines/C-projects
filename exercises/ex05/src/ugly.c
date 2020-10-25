// Same prime-detection strategy, but without any structured
// looping constructs.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Report a list of prime values.
 */
int main( void )
{
  // Get the range of values we're supposed to test.
  unsigned int low, high;
  if ( scanf( "%d%d", &low, &high ) != 2 ) {
    printf( "Invalid input\n" );
    exit( EXIT_FAILURE );
  }
  
  // Write your own, ugly solution, using goto instead of structured looping.

  int val = low;
  //outer loop for going through all values between low and high to find primes
  topOfLoop:

    if (val >= high)
      goto doneWithLoop;
    
    //Inner loop for finding Primes
    int fact = 2;
    topOfInnerLoop:
      
      //if the value survives all of the tests then print the value and exit the loop    
      if (fact * fact > val) {
        printf( "%u\n", val );
        goto doneWithInnerLoop;
      }

      //if any of the values are not prime then exit the loop early
      if (val % fact == 0) {
        goto doneWithInnerLoop;
      }
             
      fact++;
      goto topOfInnerLoop;

    doneWithInnerLoop:

    val++;
    goto topOfLoop;

  doneWithLoop:
  
  return EXIT_SUCCESS;
}
