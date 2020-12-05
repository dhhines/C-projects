/**
 * @author David Hines
 * @file buffer.c
 *
 * The buffer component is responsible for processing the input file and creating the
 * properly organized Buffer struct from the input.  This Buffer struct will then
 * be used for the SHA1 or HMAC-SHA1 hashing functions.
 */

#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>




// This function dynamically allocates a Buffer struct, initializes its fields
// (a typical representation for a resizable array).
Buffer *makeBuffer(){

    // Allocating the Buffer struct memory and exit if NULL
    Buffer *b = (Buffer *) malloc (sizeof(Buffer));
    if (! b) {
        free(b);
        exit(EXIT_FAILURE);
    }

    // Initializing the Buffer fields and allocating the memory for data array
    // Verify data array allocated or if NULL then exit failure
    b->data = (unsigned char *) malloc (sizeof(unsigned char) * MSG_BLOCK);
    if ( !b->data ) {
        freeBuffer( b );
        exit( EXIT_FAILURE );
    }

    b->cap = MSG_BLOCK;
    b->len = 0;

    return b;
}

// This function adds a single byte to the end of the given buffer, enlarging
// the data array if necessary.
void appendBuffer( Buffer *b, unsigned char byte ){
    if ( b->len >= b->cap ) {
        b->cap *= 2;
        b->data = ( unsigned char * ) realloc ( b->data, sizeof(unsigned char) * b->cap );
        if ( !b->data ){
            freeBuffer(b);
            exit(EXIT_FAILURE);
        }
    }

    b->data[b->len] = byte;
    b->len++;
}

// This function frees all the memory for the given buffer.
void freeBuffer( Buffer *b ){
    if ( b ){
        free( b->data );
        free( b );
    }
}

// This function creates a new buffer, reads the contents of the file with the
// given name, stores it in the buffer and returns a pointer to the buffer.
// If the file can't be opened, it just returns NULL.
Buffer *readFile( const char *filename ){

    // Pointer to the buffer to be created from file input
    Buffer *buffer = makeBuffer();

    // Open filename as FILE stream and exit failure if unable to open
    FILE *input = fopen(filename, "r");
    if ( !input ){
        freeBuffer( buffer );
        return NULL;
    }

    // To hold each byte read in from input file
    unsigned char block;

    // read in the bytes from input file to the buffer Struct data field
    while ( (fread( &block, 1, 1, input ) ) ) {

        appendBuffer( buffer, block );
    }

    fclose( input );
    return buffer;
}
