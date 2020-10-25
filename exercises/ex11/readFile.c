#include <stdio.h>
#include <stdlib.h>

/**
 * @author David Hines
 * @file readFile.c
 * 
 * Program to read in all available text from an input file and place it in a dynamically
 * allocated string array (that includes a null terminator).  The array will be increased
 * by 2 times whenever all capacity is used so that the program can continue to ingest all
 * text from the input file.  Once done, the program will print the total size of the file
 * in characters and then print the entire file to standard output.
 */


/**
 * Start of our program
 */
int main()
{
  // Check command-line arguments and open the input file.
  FILE *fp;
  if ( ( fp = fopen( "input.txt", "r" ) ) == NULL ) {
    fprintf( stderr, "Can't open file: input.txt\n" );
    exit( EXIT_FAILURE );
  }

  // Allocate a string with a small, initial capacity.
  int capacity = 5;
  char *buffer = (char *) malloc(capacity * sizeof(char) + 1);

  // Number of characters we're currently using.
  int len = 0;
  
  // Read from this file until we reach end-of-file, storing all characters
  // in buffer. Keep enlarging the buffer as needed until it contails the
  // contents of the whole file.  This took me 9 lines of code.
  char ch;
  while(fscanf(fp, "%c", &ch) != EOF){
    if(len >= capacity){  
      
      //double the capacity of array
      capacity *= 2;
      
      //expand capacity of existing array using realloc
      buffer = (char *) realloc(buffer, capacity * sizeof(char) + 1);      
    }

    buffer[len++] = ch;
  }
  
  //add the null terminator to the end of the array but not including it in length value
  buffer[len + 1] = '\0';

  // Print out the total size of the file, in characters.
  printf( "%d\n", len );

  // Print out the whole file, it's one big string.
  printf( "%s", buffer );

  // Don't leak memory or leave open files.
  fclose(fp);
  free(buffer);

  // Set buffer to NULL just to be clean about things and not leave dangling pointers
  buffer = NULL;
  
  return EXIT_SUCCESS;
}
