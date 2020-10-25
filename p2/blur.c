#include <stdlib.h>
#include <stdio.h>
#include "image.h"

/**
 * @author David Hines
 * @file blur.c
 *
 * This program takes a PPM file and applies a 3x3 Gaussian blur to the
 * PPM input image.  The intensity values for the colors of each pixel are
 * recalculated using the weighted sum of each of the colors for the current
 * pixel and its up to 8 neighbors.
 *
 * This program utilizes the image.h functions and preprocessor
 * constants to validate a PPM file as well as read the file input
 * data and write the data out to standard output.
 */

//highest weight for the Guassian blur calculations
#define HIGH_WGHT 4

//middle weight for the Guassian blur calculations
#define MID_WGHT 2

/**
 * This function does the calculation for the Guassian blur on the current pixel in an array
 * by using the surrounding pixels and a weighted average.  Each pixel color blur value is
 * calculate and updated independently for the array.
 *
 * @param i this is the current row of the pixel in an array to be blurred
 * @param k this is the current column of the pixel in an array to be blurred
 * @param height this is the height of the image so we know the boundaries
 * @param width this is the width of the image so we know the boundaries
 * @param pix this is the array of pixels to be used in the blur calculations
 */
void blurPix(int i, int k, int height, int width,
            unsigned char pix[height][width][DEPTH], unsigned char pixCpy[height][width][DEPTH])
{

    //top center pix i - 1, k has weight of 2
    //top left pix i - 1, k - 1 has weight of 1
    //top right pix i - 1, k + 1 has weight of 1
    //center pix i,k has weight of 4
    //center left pix i, k - 1 has weight of 2
    //center right pix i, k + 1 has weight of 2
    //bottom center pix i + 1, k has weight of 2
    //bottom left pix i + 1, k - 1 has weight of 1
    //bottom right pix i + 1, k + 1 has weight of 1

    int blur = 0;
    int count = 0;
    for (int z = 0; z < DEPTH; z++){

        //weight calc for top row pixels
        if (i > 0){
            blur += (pixCpy[i - 1][k][z] * MID_WGHT);  //top center
            count += MID_WGHT;
            if (k > 0){
                blur += pixCpy[i - 1][k - 1][z];  //top left
                count++;
            }
            if (k < width - 1){
                blur += pixCpy[i - 1][k + 1][z];  //top right
                count++;
            }
        }

        //weight calc for center row pixels
        blur += (pixCpy[i][k][z] * HIGH_WGHT);
        count += HIGH_WGHT;
        if (k > 0){
            blur += (pixCpy[i][k - 1][z] * MID_WGHT);
            count += MID_WGHT;
        }
        if (k < width - 1){
            blur += (pixCpy[i][k + 1][z] * MID_WGHT);
            count += MID_WGHT;
        }

        //weight calc for bottom row pixels
        if (i < height - 1){
            blur += (pixCpy[i + 1][k][z] * MID_WGHT);  //bottom center
            count += MID_WGHT;
            if (k > 0){
                blur += pixCpy[i + 1][k - 1][z];  //bottom left
                count++;
            }
            if (k < width - 1){
                blur += pixCpy[i + 1][k + 1][z];  //bottom right
                count++;
            }
        }

        //update the current pixel color (z) with the calculated blur value
        pix[i][k][z] = blur / count;

        //reset the count value to 0 for next loop iteration
        count = 0;
        blur = 0;
    }
}

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

    //create an array copy so can reference pixels before changes in blurPix function
    unsigned char pixCpy[height][width][DEPTH];
    for (int i = 0; i < height; i++){
        for (int k = 0; k < width; k++){
            for (int z = 0; z < DEPTH; z++){
                pixCpy[i][k][z] = pix[i][k][z];
            }
        }
    }
    
    //call to the blurPix function for each pixel in the image
    for (int i = 0; i < height; i++){
        for (int k = 0; k < width; k++){
            blurPix(i, k, height, width, pix, pixCpy);
        }
    }

    writeImage(height, width, pix);

    return EXIT_SUCCESS;
}
