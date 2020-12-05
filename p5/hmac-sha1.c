/**
 * @author David Hines
 * @file hmac-sha1.c
 *
 * HMAC implementation to increase the security of the SHA1 hashing algorithm through
 * the use of a user provide key.  The single function includes the additional HMAC
 * processing steps in combination with the existing SHA1 processing steps.
 */

#include "hmac-sha1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IPAD_VAL 0x36
#define OPAD_VAL 0x5c

// This function performs the HMAC-SHA1. It takes a key as a string of characters,
// a pointer to a Buffer struct, and a pointer to an area of memory to store the digest
// (using sha1Encode()). Note that you will likely not want the Buffer to have the padding,
// as the computation requires you to put the ipad before the Buffer contents
// (e.g., by making a new buffer and copying from the passed Buffer).
void hmacSHA1( char *kstr, Buffer *b, unsigned char digest[ SHA1_DIGEST ] ){

    // START FIRST SHA1 PROCESSING WITH IPAD AND MESSAGE BUFFER
    // SHA1State Struct declaration and initialization to dynamic memory
    SHA1State *state = ( SHA1State * ) malloc ( sizeof( SHA1State ) );

    // Initialize the state of the SHA1State struct
    initState(state);

    // Char arrays to hold the key ^ ipad and opad
    unsigned char ipadKey[SHA1_BLOCK];
    unsigned char opadKey[SHA1_BLOCK];

    for ( int i = 0; i < SHA1_BLOCK; i++ ){

        ipadKey[i] = kstr[i] ^ IPAD_VAL;
        opadKey[i] = kstr[i] ^ OPAD_VAL;
    }

    // Start with creating the concatenated message with ipad and b Buffer
    // Create a new buffer to hold the concatenated mesesage
    Buffer *iMsg = makeBuffer();
    for ( int i = 0; i < SHA1_BLOCK; i++ )
        appendBuffer( iMsg, ipadKey[i] );
    for (int i = 0; i < b->len; i++)
        appendBuffer( iMsg, b->data[i] );

    // Now pad the concatenated message with 0x80, 0x00 and length bytes
    padBuffer(iMsg);

    // Shift the bytes of the b Buffer data to Big-Endian order before HMACSHA1 processing
    int numInts = iMsg->len / WORD;
    unsigned int *swap1 = (unsigned int *) iMsg->data;
    for (int i = 0; i < numInts; i++){
        swapBytes(&swap1[i]);
    }

    // Iterate through the msg 64byte blocks and process thru sha1Block function
    for (int i = 0; i < iMsg->len / SHA1_BLOCK; i++){
        unsigned char blockI[SHA1_BLOCK];
        memcpy( blockI, iMsg->data + (i * SHA1_BLOCK), sizeof(unsigned char) * SHA1_BLOCK );
        sha1Block(blockI, state);
    }

    // Get the digest of the state after ipad + message iMsg buffer hash processing
    //sha1Encode(digest, state);
    sha1Encode(digest, state);

    // START SECOND SHA1 PROCESSING WITH OPAD AND FIRST SHA1 DIGEST

    // Reinitialize the State struct state as if starting brand new SHA1 process
    initState(state);

    // Start with creating the concatenated message with oMsg buffer and opad char bytes
    // Create a new buffer to hold the concatenated mesesage

    Buffer *oMsg = makeBuffer();
    for ( int i = 0; i < SHA1_BLOCK; i++ )
        appendBuffer( oMsg, opadKey[i] );
    for (int i = 0; i < SHA1_DIGEST; i++)
        appendBuffer( oMsg, digest[i] );

    // Pad the oMsg buffer before processing through SHA1
    padBuffer(oMsg);

    // Swap LE to BE byte order before processing the new oMsg buffer
    numInts = oMsg->len / WORD;
    unsigned int *swap3 = (unsigned int *) oMsg->data;
    for (int i = 0; i < numInts; i++){
        swapBytes(&swap3[i]);
    }

    // Iterate through the msg 64byte blocks and process thru sha1Block function
    for (int i = 0; i < oMsg->len / SHA1_BLOCK; i++){
        unsigned char blockO[SHA1_BLOCK];
        memcpy( blockO, oMsg->data + (i * SHA1_BLOCK), sizeof(unsigned char) * SHA1_BLOCK );
        sha1Block(blockO, state);
    }

    // Get the digest of the state after opad + message oMsg buffer hash processing
    sha1Encode(digest, state);

    // free Buffer iMsg as it is no longer needed
    freeBuffer(iMsg);
    // free Buffer oMsg as it is no longer needed
    freeBuffer(oMsg);
    // free state as no longer needed now that final digest is complete
    free(state);
}
