/**
 * @author David Hines
 * @file sha1.h
 *
 * This header file provides the SHA1State struct definition as well as exposing the
 * prototypes for the various SHA1 hashing algorithm functions.
 */

#ifndef _SHA1_H_
#define _SHA1_H_

#include "buffer.h"

/* Mechanism to conditionally expose static functions to other components.  For
   production, we can make make them static, but for testing we can disable
   the static keyword and expose functions to the test driver. */
#ifdef TESTABLE
#define test_static
#else
#define test_static static
#endif

/** Number of bytes in a block used in the SHA1 calculation. */
#define SHA1_BLOCK 64

/** Number of bytes in an SHA1 digest */
#define SHA1_DIGEST 20

/** Representation for the state of the SHA1 computation.  It's just 5
    unsigned 32-bit integers. Client code can create an instance
    (statically, on the stack or on the heap), but initState() needs
    to initialize it before it can be used. */
typedef struct {
  /** Fields h0 through h4 of the SHA1 state.  */
  unsigned int h0;
  unsigned int h1;
  unsigned int h2;
  unsigned int h3;
  unsigned int h4;
} SHA1State;

#endif

/**
 * Static function to convert from little-endian to big-endian and vice versa
 * for the blocks read in from the input file and for the hash values before output
 * to the console.
 *
 * @param v pointer to an unsigned int to be converted
 */
void swapBytes( unsigned int *v );

/**
 * Given the address of a SHA1State, this function initializes its fields, filling
 * them in with the five constant values given in the SHA1 algorithm.
 *
 * @param state the SHA1State struct to be initialized
 */
void initState( SHA1State *state );


/**
 * This function pads the given buffer, bringing its length up to a multiple of 64 bytes,
 * adding byte values as described in the SHA1 algorithm.
 *
 * @param b the Buffer struct containing the input to be buffered before SHA1 hashing
 */
void padBuffer( Buffer *b );


/**
 * This function performs 80 SHA1 iterations on the given block of bytes, updating the given state.
 *
 * @param data the 64byte block of data to be processed
 * @param state the SHA1State struct state information to be used during processing
 */
void sha1Block( unsigned char data[ SHA1_BLOCK ], SHA1State *state );


/**
 * This function is used to create the final hash value (also known as a "digest"). It transfers
 * the 20 bytes in the h0, h1, h2, h3, and h4 state variables into a 20 byte unsigned char array,
 * in big-endian order. i.e., digest[0] through digest[3] contains the value of h0 in big-endian
 * order, digest[4] through digest[7] contains h1 in big-endian order, etc.
 *
 * @param digest the target array for the SHA1State variables h0 - h4
 * @param state the SHA1State struct holding the final values for h0 - h4 post SHA1 processing
 */
void sha1Encode( unsigned char digest[ SHA1_DIGEST ], SHA1State *state);
