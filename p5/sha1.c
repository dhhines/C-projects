/**
 * @author David Hines
 * @file sha1.c
 *
 * The SHA1 component works on a buffer of byte values to create the SHA1 hash
 * of the buffer.  This program manages the state of the SHA1 algorith, creates
 * the buffer padding and tail values as well as handling the little-endian and
 * big-endian conversions pre and post SHA1 hash operations.
 */

#include "sha1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 8
#define WORDS 16
#define INTBITS 32
#define ITER 80
#define END_MSG 0x80
#define INIT_H0 0x67452301
#define INIT_H1 0xEFCDAB89
#define INIT_H2 0x98BADCFE
#define INIT_H3 0x10325476
#define INIT_H4 0xC3D2E1F0

/** Constants, to mix in some random-looking bits during the SHA1
    calculation.  80 constants for 80 iterations.  The constants for one
    round (iterations 0-19, 20-39, 40-59, 60-79) all have the same value. **/
static unsigned int k[ 80 ] =
    {
    0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999,
    0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1,
    0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC,
    0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6,
    };

/**
 * Function to left rotate the unigned interger value v by s bits and return
 * the updated unsigned integer value.
 *
 * @param v the unsigned integer value to be left rotated
 * @param s the number of bits to left rotate the unsigned integer value v
 * @return the left rotated unsigned integer value for v
 */
test_static unsigned int rotateLeft( unsigned int value, int s ){

    return (value << s) | (value >> (INTBITS - s));

}

/**
 * The SHA1 algorithm uses four different versions of a function named f, a different version for
 * each round. Each of these implements one of the versions.
 *
 * @param b the current value of the unsigned int b used in the SHA1 hashing functions
 * @param c the current value of the unsigned int c used in the SHA1 hashing functions
 * @param d the current value of the unsigned int d used in the SHA1 hashing functions
 * @return unsigned int value calculated using this version of the f function
 */
test_static unsigned int fVersion0( unsigned int b, unsigned int c, unsigned int d ){

    return (b & c) | (~b & d);
}

/**
 * The SHA1 algorithm uses four different versions of a function named f, a different version for
 * each round. Each of these implements one of the versions.
 *
 * @param b the current value of the unsigned int b used in the SHA1 hashing functions
 * @param c the current value of the unsigned int c used in the SHA1 hashing functions
 * @param d the current value of the unsigned int d used in the SHA1 hashing functions
 * @return unsigned int value calculated using this version of the f function
 */
test_static unsigned int fVersion1( unsigned int b, unsigned int c, unsigned int d ){

    return b ^ c ^ d;

}

/**
 * The SHA1 algorithm uses four different versions of a function named f, a different version for
 * each round. Each of these implements one of the versions.
 *
 * @param b the current value of the unsigned int b used in the SHA1 hashing functions
 * @param c the current value of the unsigned int c used in the SHA1 hashing functions
 * @param d the current value of the unsigned int d used in the SHA1 hashing functions
 * @return unsigned int value calculated using this version of the f function
 */
test_static unsigned int fVersion2( unsigned int b, unsigned int c, unsigned int d ){

    return (b & c) | (b & d) | (c & d);

}

/**
 * The SHA1 algorithm uses four different versions of a function named f, a different version for
 * each round. Each of these implements one of the versions.
 *
 * @param b the current value of the unsigned int b used in the SHA1 hashing functions
 * @param c the current value of the unsigned int c used in the SHA1 hashing functions
 * @param d the current value of the unsigned int d used in the SHA1 hashing functions
 * @return unsigned int value calculated using this version of the f function
 */
test_static unsigned int fVersion3( unsigned int b, unsigned int c, unsigned int d ){

    return b ^ c ^ d;

}

/**
 * This function implements an iteration of the SHA1 algorithm on a 64-byte block (interpreted
 * as 16 unsigned integers). The first parameter is the data block, the next five parameters
 * are the a, b, c, d, and e values from the SHA1 algorithm description, passed by reference so
 * the function can change them. The last parameter is the iteration number, a value between 0
 * and 79.
 *
 * @param data the 16 word block of data on which the sha1Iteration will be performed
 * @param a pointer to the current value of the unsigned int a
 * @param b pointer to the current value of the unsigned int b
 * @param c pointer to the current value of the unsigned int c
 * @param d pointer to the current value of the unsigned int d
 * @param e pointer to the current value of the unsigned int e
 * @param i interger value for the current iteration of SHA1 processing for this block of data
 */
test_static void sha1Iteration( unsigned int data[ 16 ], unsigned int *a, unsigned int *b,
unsigned int *c, unsigned int *d, unsigned int *e, int i ){

    // array of function pointers to the f0 - f3 SHA1 functions
    unsigned int (*f_func[])(unsigned int b, unsigned int c, unsigned int d) =
            {fVersion0, fVersion1, fVersion2, fVersion3};

    // Pointer to the function we need based on the round
    unsigned int (*f)(unsigned int b, unsigned int c, unsigned int d);

    if (i >= 0 && i <= 19)
        f = (*f_func[0]);
    if (i >= 20 && i <= 39)
        f = (*f_func[1]);
    if (i >= 40 && i <= 59)
        f = (*f_func[2]);
    if (i >= 60 && i <= 79)
        f = (*f_func[3]);

    // Unsigned int array for initial 16 words from 64 byte block and remaining words calculated
    unsigned int w[ITER];

    // copy in the 16 words derived from the 64 byte block of unsigned char
    memmove(w, data, sizeof(unsigned int) * WORDS);

    // Now generate the remaining words in the w[] array
    for (int i = 16; i < 80; i++){
        w[i] = rotateLeft( ( w[i - 16] ^ w[i - 14] ^ w[i - 8] ^ w[i - 3] ), 1);
    }

    // Calculate the new values of a, b, c, d, e for iteration i
    unsigned int temp;
    temp = *e + rotateLeft(*a, 5) + w[i] + k[i] + f(*b, *c, *d);
    *e = *d;
    *d = *c;
    *c = rotateLeft(*b, 30);
    *b = *a;
    *a = temp;
}

void swapBytes( unsigned int *v ){

    char *p = ( char * )v;

    char temp = p[0];
    p[0] = p[3];
    p[3] = temp;

    temp = p[1];
    p[1] = p[2];
    p[2] = temp;
}

void initState( SHA1State *state ){

    state->h0 = INIT_H0;
    state->h1 = INIT_H1;
    state->h2 = INIT_H2;
    state->h3 = INIT_H3;
    state->h4 = INIT_H4;
}

void padBuffer( Buffer *b ) {

    // Capture the length of the buffer before we add end of message or padd with zeros
    int msgLen = b->len;

    //fprintf(stdout, "Original message length before any appends: %d\n", b->len);

    // Add the byte 0x80 value to the end of the last block of the buffer and increment len
    appendBuffer(b, END_MSG);

    // Determine the length of last 64 byte block so know what to pad
    int r = ( b->len % SHA1_BLOCK );

    // Zero byte value used to pad the buffer with the appendBuffer function
    unsigned char zeroPad = 0x00;

    // Pad the last block of the buffer up to the last 8 bytes with 0x00
    while ( r < SHA1_BLOCK - LENGTH ){
        appendBuffer( b, zeroPad );
        r++;
    }

    // Calculate the 8 byte values for last block from the length of the original message length
    unsigned long l = msgLen * LENGTH;

    //fprintf(stdout, "\n\nValue for r to show how much padding needed: %d\n", r);

    // Cast the unsigned long integer l to an 8 byte array of unsigned char
    unsigned char bytes[LENGTH];

    bytes[0] = (l >> 56) & 0xFF;
    bytes[1] = (l >> 48) & 0xFF;
    bytes[2] = (l >> 40) & 0xFF;
    bytes[3] = (l >> 32) & 0xFF;
    bytes[4] = (l >> 24) & 0xFF;
    bytes[5] = (l >> 16) & 0xFF;
    bytes[6] = (l >> 8) & 0xFF;
    bytes[7] = l & 0xFF;

    // Loop through the 8 byte array and append to last block of buffer
    for ( int i = 0; i < LENGTH; i++ ){
        appendBuffer( b, bytes[i] );
    }
}

void sha1Encode( unsigned char digest[ SHA1_DIGEST ], SHA1State *state){

    for (int i = 0; i < SHA1_DIGEST; i += 4) {
        if (i >= 0 && i <= 3){
            digest[i] = (state->h0 >> 24) & 0xFF;
            digest[i + 1] = (state->h0 >> 16) & 0xFF;
            digest[i + 2] = (state->h0 >> 8) & 0xFF;
            digest[i + 3] = (state->h0) & 0xFF;
        }
        if (i >= 4 && i <= 7){
            digest[i] = (state->h1 >> 24) & 0xFF;
            digest[i + 1] = (state->h1 >> 16) & 0xFF;
            digest[i + 2] = (state->h1 >> 8) & 0xFF;
            digest[i + 3] = (state->h1) & 0xFF;
        }
        if (i >= 8 && i <= 11){
            digest[i] = (state->h2 >> 24) & 0xFF;
            digest[i + 1] = (state->h2 >> 16) & 0xFF;
            digest[i + 2] = (state->h2 >> 8) & 0xFF;
            digest[i + 3] = (state->h2) & 0xFF;
        }
        if (i >= 12 && i <= 15){
            digest[i] = (state->h3 >> 24) & 0xFF;
            digest[i + 1] = (state->h3 >> 16) & 0xFF;
            digest[i + 2] = (state->h3 >> 8) & 0xFF;
            digest[i + 3] = (state->h3) & 0xFF;
        }
        if (i >= 16 && i <= 19){
            digest[i] = (state->h4 >> 24) & 0xFF;
            digest[i + 1] = (state->h4 >> 16) & 0xFF;
            digest[i + 2] = (state->h4 >> 8) & 0xFF;
            digest[i + 3] = (state->h4) & 0xFF;
        }
    }
}

void sha1Block( unsigned char data[ SHA1_BLOCK ], SHA1State *state ) {

    // Copy the initial state of h0 - h4 to the local unsigned int variables a - e
    unsigned int a, b, c, d, e;
    a = state->h0;
    b = state->h1;
    c = state->h2;
    d = state->h3;
    e = state->h4;

    unsigned int *words = (unsigned int *) data;

    // Loop for the 80 iterations
    for (int i = 0; i < ITER; i++) {
        sha1Iteration(words, &a, &b, &c, &d, &e, i);
    }

    state->h0 += a;
    state->h1 += b;
    state->h2 += c;
    state->h3 += d;
    state->h4 += e;
}
