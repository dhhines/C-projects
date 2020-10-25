/**
   @file arithmetic.c
   @author David Hines (dhhines)
   A program that sums all integers from 1 to 1000000000
*/

#include <stdio.h>

/**
   Starting point for the progam.
   @return exit status
*/

int main()
{
  
  long sum = 0;
  for (int i = 0; i <= 1000000000; i++)
    {
      sum += i;    
    }

  printf( "%ld\n", sum );

  // Return with successful exit status.

  return 0;
}
