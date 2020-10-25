/**
 * @author David Hines
 * @file input.c
 *
 * The input program has a single function that will read a single line of
 * input from an input file and returns that string as a block of dynamically
 * allocated memory to the calling function.
 */

#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *readLine(FILE *fp)
{
    //create a resizeable array using malloc and realloc and a capacity integer
    int capacity = INIT_CPCTY;
    char *buffer = (char *) malloc (capacity * sizeof(char) + 1);
    int len = 0;
    char ch;
    int matches = 0;

    while ((matches = (fscanf(fp, "%c", &ch) == 1))){
        if (len >= capacity){
            capacity *= 2;
            buffer = (char *) realloc (buffer, capacity * sizeof(char) + 1);
            if (!buffer){
                free(buffer);
                exit(EXIT_FAILURE);
            }
        }
        if (ch != '\n')
            buffer[len++] = ch;
        else
            break;
    }

    if (matches > 0){
        buffer[len] = '\0';
        return buffer;
    }

    free(buffer);
    return NULL;

}
