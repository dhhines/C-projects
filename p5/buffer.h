/**
 * @author David Hines
 * @file buffer.h
 *
 * Header file for the buffer component which contains the Buffer struct
 * definition and type definition.  This header also exposes functions needed
 * to create the Buffer struct from the user provided input file.
 */

#define MSG_BLOCK 64
#define WORD 4

#ifndef _BUFFER_H_
#define _BUFFER_H_

/** Representation for the contents of an input file, copied to memory. */
typedef struct {
  /** Array of bytes from the file (not stored as a string - no NULL termination). */
  unsigned char *data;

  /** Number of currently used bytes in the data array. */
  unsigned int len;

  /** Capacity of the data array (it's typically over-allocated. */
  unsigned int cap;
} Buffer;

#endif

/**
 * This function dynamically allocates a Buffer struct, initializes its fields
 * (a typical representation for a resizable array).
 * @return pointer to the Buffer struct created in dynamic memory
 */
Buffer *makeBuffer();


/**
 * This function adds a single byte to the end of the given buffer, enlarging the
 * data array if necessary.
 * @param b pointer to the Buffer struct to which the byte will be appended
 * @param byte the byte value to be appended to the Buffer struct
 */
void appendBuffer( Buffer *b, unsigned char byte );


/**
 * This function frees all the memory for the given buffer.
 * @param b pointer to the Buffer struct that needs to be freed
 */
void freeBuffer( Buffer *b );

/**
 * This function creates a new buffer, reads the contents of the file with the
 * given name, stores it in the buffer and returns a pointer to the buffer.
 * If the file can't be opened, it just returns NULL.
 * @param filename pointer to the filename to process
 * @return pointer to the Buffer struct containing the file input
 */
Buffer *readFile( const char *filename );
