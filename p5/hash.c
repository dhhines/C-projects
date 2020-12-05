/**
 * @author David Hines
 * @file hash.c
 *
 * C implementation of the SHA1 hashing alogrithm which takes input file as command
 * line argument and outputs the hash of that input.  User can optionally provide
 * an HMAC key using the -hmac optional command line argument and the key in
 * enclosing "" which will then compute the HMAC-SHA1 hash on the input.
 */

#include "buffer.h"
#include "hmac-sha1.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static void invalid()
{
    fprintf( stderr, "usage: hash [-hmac <key>] <filename>\n" );
    exit( EXIT_FAILURE );
}

int main( int argc, char *argv[] )
{

    // Buffer type pointer for receiving the message stored in Buffer struct
    Buffer *msg;

    // Check for 2 or 4 parameters and create msg buffer or key and msg buffer for hmac.
    if ( argc == 2 ){
        // Attempt to get pointer to msg Buffer struct, exit status 1 if NULL
        msg = readFile( argv[ 1 ]);
        if ( !msg ) {
            fprintf( stderr, "Can't open file: %s\n", argv[ 1 ] );
            freeBuffer(msg);
            exit(EXIT_FAILURE);
        }

        // SHA1State Struct declaration and initialization to dynamic memory
        SHA1State *state = (SHA1State *) malloc (sizeof(SHA1State));

        // Initialize the state of the SHA1State struct
        initState(state);

        // Pad the buffer with the end of message value, zeros and length bytes
        padBuffer(msg);

        int numInts = msg->len / WORD;
        unsigned int *swap2BE = (unsigned int *) msg->data;
        for (int i = 0; i < numInts; i++){
            swapBytes(&swap2BE[i]);
        }

        // Iterate through the msg 64byte blocks and process thru sha1Block function
        for (int i = 0; i < msg->len / SHA1_BLOCK; i++){
            unsigned char block[SHA1_BLOCK];
            memcpy( block, msg->data + (i * SHA1_BLOCK), sizeof(unsigned char) * SHA1_BLOCK );
            sha1Block(block, state);
        }

        // unsigned char array to hold the final digest of the input data blocks
        unsigned char digest[SHA1_DIGEST];
        sha1Encode( digest, state );

        // Print out the SHA1 hashing result (digest) to the console
        for ( int i = 0; i < SHA1_DIGEST; i++ ) {
            fprintf( stdout, "%02X", digest[ i ] );
            if ( i == 19 )
                fprintf( stdout, "\n" );
        }

        free( state );
        freeBuffer(msg);

    } else if ( argc == 4 ) {

        // String for the key input on the command line argument after -hmac
        char key[SHA1_BLOCK];

        // Check for the -hmac option string and the key (also string)
        if ( strcmp(argv[ 1 ], "-hmac" ) == 0){

            // Put up to 64 bytes of the key input into the key char array
            strncpy(key, argv[2], SHA1_BLOCK);

            // Create the msg buffer from the input file
            msg = readFile( argv[ 3 ] );
            if ( !msg ) {
                fprintf( stderr, "Can't open input file %s\n", argv[ 2 ] );
                freeBuffer(msg);
                exit( EXIT_FAILURE );
            }
        }
        else {
            invalid();
        }

        // Unsigned char array to hold the final digest of the input data blocks
        unsigned char digest[SHA1_DIGEST];

        // Call to the HMACSHA1 hashing algorithm
        // NOTE: the buffer msg is padded within the hmacSHA1 function
        hmacSHA1( key, msg, digest );

        // Print out the SHA1 hashing result (digest) to the console
        for ( int i = 0; i < SHA1_DIGEST; i++ ) {
            fprintf( stdout, "%02X", digest[ i ] );
            if ( i == 19 )
                fprintf( stdout, "\n" );
        }

        freeBuffer(msg);

    } else {
        // This is to catch any other situations of incorrect paramaters
        invalid();
    }
    return EXIT_SUCCESS;
}
