#include <stdlib.h>
#include <stdio.h>
#include "image.h"

/**
 * @author David Hines
 * @file border.c
 *
 * This program takes a PPM file and adds a 4 pixel black border to
 * the outside top, bottom, left and right of the image while maintaining
 * the integrity of the source image inside that new border.  When writing
 * the new image file to output the size of the image will be adjusted in
 * the PPM header to take into account the additional pixels for height and
 * width.
 *
 * This program utilizes the image.h functions and preprocessor
 * constants to validate a PPM file as well as read the file input
 * data and write the data out to standard output.
 */


/** The size of the border to put around the image. */
#define PADDING 4

/**
 * Main function for the border.c program
 * @return exit success status
 */
int main()
{

    int width;
    int height;

    checkType();

    width = readDimension();
    height = readDimension();

    checkRange();

    unsigned char pix[height][width][DEPTH];
    readPixels(height, width, pix);

    int widthBrdr = width + 2 * PADDING;
    int hghtBrdr = height + 2 * PADDING;

    //created larger array with additional pixels in height and width
    unsigned char pixBrdr[hghtBrdr][widthBrdr][DEPTH];

    //fill in the pixel border at top
    for (int i = 0; i < PADDING; i++){
        for (int k = 0; k < widthBrdr; k++){
            for (int z = 0; z < DEPTH; z++){
                pixBrdr[i][k][z] = 0;
            }
        }
    }

    //fill in the pixel borders at bottom
    for (int i = hghtBrdr - 1; i >= hghtBrdr - PADDING; i--){
        for (int k = 0 - 1; k < widthBrdr; k++){
            for (int z = 0; z < DEPTH; z++){
                pixBrdr[i][k][z] = 0;
            }
        }
    }

    //copy the original image pixels into new array and add border to beginning and end
    for (int i = PADDING; i < hghtBrdr - PADDING; i++){
        for (int k = 0; k < widthBrdr; k++){
            if (k < PADDING || k >= widthBrdr - PADDING){
                for (int z = 0; z < DEPTH; z++){
                    pixBrdr[i][k][z] = 0;
                }
            }
            else{
                for (int z = 0; z < DEPTH; z++){
                    pixBrdr[i][k][z] = pix[i - PADDING][k - PADDING][z];
                }
            }


        }
    }

    writeImage(hghtBrdr, widthBrdr, pixBrdr);

    return EXIT_SUCCESS;
}
