/**
 * @author David Hines
 * @file input.h
 *
 * This is the header file for the input.c function to make its capabilities
 * accessible to other parts of the reading list application.
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INIT_CPCTY 5

/**
 * This function reads a single line of input text from the file stream and then
 * returns the text as a string in a block of dynamically allocated memory.
 *
 * @param *fp pointer to the input file stream to be parsed
 * @return pointer to the dynamic memory block holding the text of a single line
 *  from input file (or user command)
 */
char *readLine(FILE *fp);
