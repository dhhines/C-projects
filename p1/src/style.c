/**
 @file style.c
 @author David Hines
 Program to reinforce the style guidelines to be used in CSC230 and
 also outputs a series of characters to the terminal then exits with 
 a success status.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 72

/**
 Prints a number of random lower case letters to the terminal based
 on the number passed as a parameter to the function
 @param x  the integer passed that determines number of characters to print
 */
void printWord( int x )
{
    for ( int i = 0; i < x; i++ ){
            // Print a random lower-case letter.
            printf( "%c", 97 + rand() % 26 );
    }
}


/**
 Prints a line of words up to a limited length and returns
 to the calling function the count of those words
 @return count of the words printed during the function execution 
 */
int printLine() {
	int count = 0, pos = 0, space = 0;
	int len = 1 + rand() % 10;
	// Print a line of words up to a limited length.
	while ( pos + len + space < MAX_LENGTH ) {
		if ( space > 0 ) {
			printf( " " );
                }
		printWord( len );
		pos += len + space;
		len = 1 + rand() % 10;
		space = 1;
		count += 1;
	}
	printf( "\n" );
	return count;
}

/**
 Prints a number of lines of output to the terminal based on the integer parameter
 passed to the function and returns the total number of words for all lines to calling function.
 @param n the number of lines of output to print
 @return the total number of words output to the terminal
 */
int printParagraph( int n )
{
    int total = 0;
    for ( int i = 0; i < n; i++ )
        total += printLine();
    
    return total;
}

/**
 Main method for executing our program and uses the printf function to format the 
 total number of words printed to the terminal as decimal integer with a newline at the end.
 @return 0 if the execution was successful 
 */
int main()
{
    int w = printParagraph(10);
    printf("Words: %d\n",w);
    return 0;
}



