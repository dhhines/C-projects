/**
 * @author David Hines
 * @file text.c
 *
 * This program defines the array of strings used to represent the lines and columns of
 * text from the input file.  This program is also responsible for opening the file to
 * ingest the text and then writing the output file for the updated text.
 */

#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


//Global variable for number of lines in the text
int numLines = 0;

//Dynamically allocated array for our text representation
char (*textRep)[MAX_CHAR];


void readFile( FILE *fp)
{
    char ch;
    int column = 0;

    while (fscanf(fp, "%c", &ch) != EOF){
        //check to see if the lines exceed the maximum and exit if true
        if (numLines >= MAX_LINE){
            fprintf(stderr, "Too many lines\n");
            exit(1);
        }

        //check to see if the number of characters in a line exceed the maximum and exit if true
        if (column >= MAX_CHAR){
            fprintf(stderr, "Line too long\n");
            exit(1);
        }
        else if (ch == '\n'){
            //TODO Might have to loop through to end of the row and add in null terminators
            textRep[numLines][column] = '\0';
            column = 0;
            numLines++;
        }
        else{
            textRep[numLines][column] = ch;
            column++;
        }
    }
}


void writeFile( FILE *fp)
{

    //Loop through the array by lines and print each row as a string to the output file
    for (int i = 0; i < numLines; i++){
        fprintf(fp, "%s\n", textRep[i]);
    }

}
