#include <stdlib.h>
#include <stdio.h>
#include "image.h"

/**
 * @author David Hines
 * @file brighten.c
 *
 * This program takes a PPM file and increases the intensity of the
 * pixel values by 32.  If the value is already at maximum of 255
 * then the pixel value is unchanged.
 *
 * This program utilizes the image.h functions and preprocessor
 * constants to validate a PPM file as well as read the file input
 * data and write the data out to standard output.
 */

/** How much to add to the intensity values of a pixel. */
#define DELTA 32

/**
 * Main function for the program
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

    //increasing the intensity of each pixel by the DELTA value
    for (int i = 0; i < height; i++){
        for (int k = 0; k < width; k++){
            for (int z = 0; z < DEPTH; z++){
                if (pix[i][k][z] + DELTA > STD_RANGE)
                    pix[i][k][z] = STD_RANGE;
                else
                    pix[i][k][z] += DELTA;
            }
        }
    }

    writeImage(height, width, pix);

    return EXIT_SUCCESS;
}
