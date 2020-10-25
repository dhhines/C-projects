/**
 * @author David Hines
 * @file text.h
 *
 * Header file for the text component that contains preprocessor constants as well as
 * any needed extern variables or function prototypes.
 */

#include <stdio.h>

#define MAX_CHAR 101

#define MAX_LINE 10000

//Global variable for number of lines in the text
extern int numLines;

//Dynamically allocated array for our text representation
extern char (*textRep)[MAX_CHAR];

/**
 * Reads the text from a given input and stores the it in the global 2D array
 * variable for the text representation.
 *
 * @param *fp the pointer to an input file or standard input (stdin)
 */
void readFile( FILE *fp);

/**
 * Writes the text from the global 2D array variable to the given output file.
 *
 * @param *fp the pointer to an output file or standard output (stdout)
 */
void writeFile( FILE *fp);
