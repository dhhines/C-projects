/**
 * @author David Hines
 * @file chop.c
 *
 * This program takes the text input from a file and uses a series of command line
 * arguments from standard input to perform manipulation actions on the text.  The
 * arguments from the command line define how columns and lines of the input text
 * should be extracted and then printed to standard output.  Order of the command
 * line arguments matters and will impact the resultant output file.
 *
 * This program will accept any input text but is meant to be run on text that has
 * well defined rows and columns.  Also, if the user specifices an input file that
 * cannot be opened then an error will be printed to the console.  If the command
 * line arguments to not follow the perscribed convention then the program will exit
 * with a status of 1 along with an error to the console with the argument syntax.
 *
 * Finally, there are limits to this program and any line that exceeds 100 characters
 * (not counting null terminators) will generate an error the console and exit the
 * program with a status of 1.  As well, if the number of lines of text exceed 10000
 * lines then the program will generate an error to the console and exit with a
 * status of 1.
 *
 * This is the main program for the project and utilizes the edit.c, edit.h, text.c,
 * text.h components to perform the file operations, text to array creation and the
 * edit functions performend on the input text.
 */

#include "edit.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Function to print error message to screen when invalid arguments are passed
 * in via the command line.
 */
void invalidArgs()
{
    fprintf(stderr, "invalid arguments\n");
    fprintf(stderr, "usage: chop command* (infile|-) (outfile|-)\n" );
    exit(1);
}


/**
 * Start of the chop program
 *
 * @param argc  the number of command line argurments passed via standard input
 * @param *argv[]  the point to an array containing the strings
 */
int main ( int argc, char *argv[] )
{

    //Initialize the dynamically allocated textRep 2D array for storing our text
    textRep = (char (*)[MAX_CHAR]) malloc(MAX_LINE * MAX_CHAR * sizeof(char));

    //------------- Text Input section of Main --------------------------------------------------

    //File stream to be used when obtain the input text file from command line args
    FILE *fpInput;

    //Flag for identifying if used stdin versus input file; ipf = 0 is stdin, ipf = 1 is file
    int ipf;

    //Obtain the input file from command line arguments or throw error
    if (*argv[argc - 2] == '-'){
        //if '-' is specificed then we use stdin as the source
        fpInput = stdin;
        ipf = 0;
        readFile(fpInput);
    }
    else {
        //checking for ability to open file and assigning to fpInput pointer to open file with read
        if ((fpInput = fopen(argv[argc - 2], "r"))){
            ipf = 1;
            readFile(fpInput);
        }
        else{
            //Print error if we can't open the provided file
            fprintf(stderr, "Can't open file: %s\n", argv[argc - 2]);
            exit(1);
        }
    }

    //------------- Line and Col argument parsing section of Main -------------------------------

    //Temporary variablees used for the line and column ranges read from command line args
    int colS;
    int colF;
    int linS;
    int linF;

    //loop through all of the command line arguments calling text edit functions in order
    for (int i = 1; i < argc - 2; i++){
        if (strcmp(argv[i], "line") == 0){
            if (atoi(argv[i + 1]) > 0 && atoi(argv[i + 1]) <= MAX_LINE)
                linS = atoi(argv[i + 1]);
            else
                invalidArgs();

            //when line is passed we know it is only one value so start and finish are same
            linF = linS;

            //call the removeLines function
            removeLines(linS, linF);

            //increment past the argc right after the line command
            i++;
        }
        else if (strcmp(argv[i], "lines") == 0){
            //capture the first argument after lines
            if (atoi(argv[i + 1]) >= 1 && atoi(argv[i + 1]) <= MAX_LINE)
                linS = atoi(argv[i + 1]);
            else
                invalidArgs();
            //capture the second argument after lines
            if (atoi(argv[i + 2]) >= atoi(argv[i + 1]) && atoi(argv[i + 2]) <= MAX_LINE)
                linF = atoi(argv[i + 2]);
            else
                invalidArgs();

            //validate that the arguments are in the correct order smaller to larger
            if (linS > linF)
                invalidArgs();

            //call the removeLines function
            removeLines(linS, linF);

            //increment past the 2 argc after lines command since we already captured their values
            i += 2;
        }
        else if (strcmp(argv[i], "col") == 0){
            if (atoi(argv[i + 1]) >= 1 && atoi(argv[i + 1]) <= MAX_LINE)
                colS = atoi(argv[i + 1]);
            else
                invalidArgs();

            //when col is passed we know only one value so start and finish are same
            colF = colS;

            //Loop through the editLines function with the current colS and colF values
            for (int k = 0; k < numLines; k++){
                editLines(k, colS, colF);
            }

            //increment past the argc right after the col command
            i++;
        }
        else if (strcmp(argv[i], "cols") == 0){
            if (atoi(argv[i + 1]) >= 1 && atoi(argv[i + 1]) <= MAX_LINE)
                colS = atoi(argv[i + 1]);
            else
                invalidArgs();

            if (atoi(argv[i + 2]) >= 1 && atoi(argv[i + 2]) <= MAX_LINE)
                colF = atoi(argv[i + 2]);
            else
                invalidArgs();

            //validate that the arguments are in the correct order smaller to larger
            if (colS > colF)
                invalidArgs();

            //Loop through the editLines function with the current colS and colF values
            for (int i = 0; i < numLines; i++){
                editLines(i, colS, colF);
            }

            //increment past the 2 argc right after the cols command
            i += 2;
        }
        else {
            //TODO catch garbage here and exit program with status 1
            invalidArgs();
        }
    }

    //------------- Text Output section of Main ------------------------------------------------

    //File stream to be used when writing the output text to file specified in command line args
    FILE *fpOutput;

    //Flag for identifying if used stdout versus output file; opf = 0 is stdout, opf = 1 is file
    int opf;

    //Obtain the output file target from command line arguments or throw error
    if (*argv[argc - 1] == '-'){
        //if '-' is specificed then we use stdout as the output target
        fpOutput = stdout;
        opf = 0;
        writeFile(fpOutput);
    }
    else {
        //checking for ability to open file and assign to fpOutput pointer to open file with write
        if ((fpOutput = fopen(argv[argc - 1], "w"))){
            opf = 1;
            writeFile(fpOutput);
        }
        else{
            //Print error if we can't open the provided file
            fprintf(stderr, "Can't open file: %s", argv[argc - 1]);
            exit(1);
        }
    }

    //Free up the dynamic memory allocated array to prevent memory leak
    free(textRep);

    //TODO Need to check for stdin or stdout as the targets before trying to close them!
    if (ipf == 1)
        fclose(fpInput);
    if (opf == 1)
        fclose(fpOutput);

}
cd /cygdrive/d/Dropbox/Training\ Material/CSC230-CandSoftwareTools/