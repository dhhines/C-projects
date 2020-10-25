/**
 * @author David Hines
 * @file arguments.c
 * Dynamically allocate a 2D array that holds the same set of strings as
 * the command line arguments then print those arguments to the console
 * using a function that takes our 2D array as parameter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function that takes the 2D array of characters which now holds the 
 * command line argument strings and prints those strings to the console
 * @param rows  number of rows in the 2D array
 * @param cols  number of columns in the 2D array
 * @param args[][cols]  the 2D array holding the command line arguments
 */
void printArguments( int rows, int cols, char args[][ cols ] )
{
  // Each row of the args array contains a string.  Print out each of the
  // strings.

  for (int i = 0; i < rows; i++){
    printf("%s\n", args[i]);
  }
}

/**
 * Start of our program in main 
 * @param argc  integer for the number of command line arguments
 * @param *argv[]  array of character points to the command line arguments in static memory
 */
int main( int argc, char *argv[] )
{
  // Figure out the length of the longest command-line argument.
  int longest = 0;
  for (int i = 0; i < argc; i++){
    if (longest < strlen(argv[i]))
      longest = strlen(argv[i]);
  }

  // Dynamically allocate a 2D array of characers, with one row for every
  // command-line argument and (exactly) enough columns to hold a copy of the
  // widest command-line argument (including the null terminator at the end).
  char (*words)[ longest + 1 ];

  //Note that the (char (*)[longest + 1] in front of malloc is the type cast for the pointer type
  //The notes from class indicate that the type cast is not required...  Tested and both ways work
  words = (char (*)[longest + 1])malloc(argc * (longest + 1) * sizeof(char));

  // Copy each command-line argumetn to a row of this new array.
  
  for (int i = 0; i < argc; i++){
    strcpy(words[i], argv[i]); 
  }

  // Call a function that's expecting the command-line arguments as a 2D array
  // (not as an array of pointers).
  printArguments( argc, longest + 1, words );

  //Can't forget to free the heap memory or will be a leak!
  free(words);
  //Just to be clean about things setting words pointer to NULL to prevent dangling pointer
  words = NULL;

  return EXIT_SUCCESS;
}
