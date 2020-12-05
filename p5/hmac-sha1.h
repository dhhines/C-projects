/**
 * @author David Hines
 * @file hmac-sha1.h
 *
 * Header file for the hmac-sha1 implementation function.  This function is
 * incorporated into the existing SHA1 implementation to provide additional
 * security through the inclusion of a user proviced HMAC key.
 */

#include "buffer.h"
#include "sha1.h"

/**
 * This function performs the HMAC-SHA1. It takes a key as a string of characters,
 * a pointer to a Buffer struct, and a pointer to an area of memory to store the digest
 * (using sha1Encode()). Note that you will likely not want the Buffer to have the padding,
 * as the computation requires you to put the ipad before the Buffer contents
 * (e.g., by making a new buffer and copying from the passed Buffer).
 *
 * @param kstr the user provide HMAC key as pointer to string of characters
 * @param b the buffer holding the message to be hashed as a pointer to Buffer struct
 * @param digest the 20 byte array to hold the digest of the buffer with HMAC key
 */
void hmacSHA1( char *kstr, Buffer *b, unsigned char digest[ SHA1_DIGEST ]);




