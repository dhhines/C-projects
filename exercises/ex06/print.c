#include "print.h"
#include <stdio.h>

/**
 * @author David Hines
 * @file print.c
 * Print function definition that reads in each character from
 * standard input, counts spaces and then prints each characters
 * to standard output except for spaces which are replaced by
 * the '-' character.
 */

// Add a new global variable to keep a count of the spaces we print.
int spaceCount;

// Print the given character, counting spaces as we print and
// replacing each space with a '-'. The parameter type is char here,
// since we don't expect EOF to be passed to the function, just legal
// characters.
void dashesForSpaces( char ch )
{
   // Fill in the body of this function.    
   if(ch == 32){
      spaceCount++;
      putchar('-');
   } 
   else {
      putchar(ch);
   }   
}
