#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // For NULL, although we don't need it.

/**
 * @author David Hines
 * @file passByReference.c
 * This program is for testing pointers through pass by reference. The program will
 * take pass by reference parameters (or pass by value) and manipulate the associated
 * variables then output the results to the console. 
 */


/**
 * Takes pointers a, b, and c as well as a 4th integer parameter then increments
 * the pointer references by the 4th parameter.
 * @param *a    first pointer
 * @param *b    second pointer
 * @param *c    third pointer
 * @param inc   value to increment the other pointer references
 */
void incrementAll(int *a, int *b, int *c, int inc)
{
  *a += inc;
  *b += inc;
  *c += inc;
}

/**
 * This function takes the pointers a, b and c as parameters and will copy the 
 * values of b -> a, c -> b, and a -> c.
 * @param *a  first pointer
 * @param *b  second pointer
 * @param *c  third pointer
 */
void rotate(int *a, int *b, int *c)
{
  int temp;

  temp = *a;
  *a = *b;  //*a now holds the value for *b reference point
  *b = *c;  //*b now holds the value for *c reference point
  *c = temp; //*c now holds the value for the *a reference point

}

/**
 * This function takes the pointer addresses of the a, b and c pointers
 * and determines which one is largest value.  The largest pointer address
 * is returned by the function. 
 * @param *a  first pointer
 * @param *b  second pointer
 * @param *c  third pointer
 * @return the largest pointer address
 */
int *getLargest(int *a, int *b, int *c)
{

  if(*a > *b){
    if (*a > *c)
      return a;
    return c;
  }
  else{
    if (*b > *c)
      return b;
    return c;
  }  
}


int main()
{
  int a = 100;
  int b = 50;
  int c = 25;

  // Get initial values for a, b and c.
  printf( "a = %d b = %d c = %d\n", a, b, c );

  // Call a function to increment all the values by the given constant
  // (10 here)
  incrementAll( &a, &b, &c, 10 );

  // Report current values for a, b and c.
  printf( "a = %d b = %d c = %d\n", a, b, c );

  // Simultaneously move the value from b to a, from c to b and from a
  // to c.
  rotate( &a, &b, &c );

  // Report current values for a, b and c.
  printf( "a = %d b = %d c = %d\n", a, b, c );

  // Get back a pointer to the largest value.
  int *largest = getLargest( &a, &b, &c );

  // Make this value smaller.  We do need the parentheses here.
  (*largest)--;

  // Report final values for a, b and c.
  printf( "a = %d b = %d c = %d\n", a, b, c );

  return EXIT_SUCCESS;
}
