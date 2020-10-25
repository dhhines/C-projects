/**
  @author David Hines
  @file digits.c
  Do some I/O and math with unsigned types.  
  */ 

#include <stdlib.h>
#include <stdio.h>

/**
  Add up all the digits in the value, x, and return the sum.
  @param x  an unsigned long value
  @return the integer value of the sum of all the digits for x
 */
unsigned int digitSum( unsigned long x )
{
  unsigned long temp = x;
  int sum = 0;

  while (temp != 0){
    sum += temp % 10;
    temp /= 10;
  }

  return sum;
}

/**
  Main function for our program where execution starts
 */
int main()
{
  // Range of values we're supposed to check.
  unsigned long low, high;

  // Target sum we're supposed to look for.
  unsigned int target;

  // Read the range of values from the user.
  
  int matches = scanf("%lu%lu", &low, &high);
  if (matches != 2)
    EXIT_FAILURE;

  // Read the digit sum we're supposed to look for.
  int match = scanf("%u", &target);
  if (match != 1)
    EXIT_FAILURE;

  // Check all values from low up to high (inclusive), and report the ones
  // that have the given digit sum.
  // ...
  for (unsigned long i = low; i <= high; i++){
    if (digitSum(i) == target){
      printf("%lu\n", i);
    }
  }

  return EXIT_SUCCESS;
}
