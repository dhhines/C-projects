/**
 * @author David Hines
 * @file edit.c
 *
 * This program is responsible for editing the contents of the array of strings created
 * by the text.c program.  It will use the command line arguments passed the edit functions
 * to remove the proper columns and lines of text within the array.
 */

#include "edit.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void removeLines( int start, int end)
{

    int linesRmvd;
    if (end > numLines){
        linesRmvd = numLines - (start - 1);
    }
    else{
        linesRmvd = end - (start - 1);
    }


    for (int i = start - 1; i < numLines; i++){
        strcpy(textRep[i], textRep[end]);
        end++;
    }

    numLines = numLines - linesRmvd;
}

void editLines( int lno, int start, int end)
{

    for (int i = start - 1; i < MAX_CHAR; i++){
        textRep[lno][i] = textRep[lno][end];
        end++;
    }

}
