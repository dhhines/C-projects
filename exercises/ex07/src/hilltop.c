#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @author David Hines
 * @file hilltop.c
 * This program reads in the row and column sizes that will be used to create a
 * variable sized 2D array of integers.  The program then reads in the grid of
 * integers in the input file and inputs them into the proper array locations
 * as read from left to right and top to bottom.
 * 
 * Once the array is populated with values, the program then computes the local
 * maxima coordinates for the array and outputs those values to console.
 * 
 */ 
 

/**
 * This function reads in the grid of integers from the standard input and
 * adds them to the array that was created in main. 
 */ 
void readGrid( int rows, int cols, int grid[ rows ][ cols ] )
{
  // Add code to read in all the elements of grid from standard input.
  for(int i = 0; i < rows; i++){
    for(int k = 0; k < cols; k++){
      scanf("%d", &grid[i][k]);  //Remember to pass by reference array elements!
    }
  }
}

/**  
 * This function checks the neighbors on the provided row to see if the current grid element (i and k coordinate)
 * is greater that the neighbor elements in the row.  If the function finds that the current grid element 
 * is less than any neighbor it will return false to the calling function.  Otherwise, this function 
 * will return true.
 * 
 * Note:  This function checks to see if the neighbors exist on the same row as the current grid element
 * to ensure that it does not incorrectly attempt to check against itself and return false incorrectly
 * (since the element would not be greater that itself)
 * 
 * @param i  the i coordinate (row) for the current grid element being checked
 * @param k  the k coordinate (col) for the current grid element being checked
 * @param x  the row for the neighbor to be checked
 * @param rows  the number of rows in the array
 * @param cols  the number of cols in the array
 * @param grid  the array of elements being tested
 */
bool checkRowNeighbors(int i, int k, int x, int rows, int cols, int grid[rows][cols])
{
  if (k - 1 >= 0){  //checking to make sure we don't fall off array columns by going less than zero
    if(grid[i][k] < grid[x][k - 1])
      return false;
    }

    if (i != x){
      if(grid[i][k] < grid[x][k])  //no need to check column as same one as current element we are testing
        return false;
    }

    if (k + 1 < cols){  //checking to make sure we don't go past number of columns
      if(grid[i][k] < grid[x][k + 1])
        return false;
    } 

    return true; 
}

// Add parameters to to pass a variable-sized array to the following
// function.  It's the same as the previous function, but I want you
// to get a chance to type it in yourself.
void reportMaxima( int rows, int cols, int grid[rows][cols] )
{
  // Add code to find local maxima and print them out in row major order.

  for(int i = 0; i < rows; i++){
    for(int k = 0; k < cols; k++){  //Double nested loop gets the grid value to test for local maxima
        //This checks will look for neighbors on same row (if not < 0 or > cols)
        if (checkRowNeighbors(i, k, i, rows, cols, grid) == 0)
          continue;
        
        //This checks will look for neighbors on row above (if not < 0)
        if (i - 1 > 0){
          if (checkRowNeighbors(i, k, i - 1, rows, cols, grid) == 0)
            continue;     
        }

        //This checks will look for neighbors on row below (if not > rows)
        if (i + 1 < rows){
          if (checkRowNeighbors(i, k, i + 1, rows, cols, grid) == 0)
            continue;
        }

        //If passess all checks then local maxima and printf the array coordinates
        printf("%d %d\n", i, k);
      
    }
  }
}

int main()
{
  // Add code to read in the grid size from standard input.
  int r;
  int c;

  scanf("%d%d", &r, &c);

  // Declare a variable-sized array to hold the grid.
  int ary[r][c];

  // Call readGrid() to populate the array.
  readGrid(r, c, ary);

  // Call reportMaxima() to print out all local maxima.
  reportMaxima(r, c, ary);
  
  return EXIT_SUCCESS;
}
