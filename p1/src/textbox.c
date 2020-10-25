/**
 @author David Hines
 @file textbox.c
 Program that takes lines of input and places them in a box of
 characters designated by a preprocessor directive. 
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Width of each line of text in the box. */
#define LINE_WIDTH 60

/** Symbol used to draw the border around the box. */
#define BORDER '*'

/**
 This function reads in a single line of text and then prints it inside the border.
 If there is no line of text to print then the function returns false to
 the calling function.  Text to be printed is read from standard input and printed
 via standard output.  All text is padded if it is not long enough to fill the line 
 and truncated if it would extend beyond the line length maximum. 
 @return false if there is no line text to print 
  */
bool paddedLine()
{
    int ch;
    int count = 0;
    while ( (ch = getchar()) != EOF){
        if (count == 0 && ch != '\n'){
            printf("*");
            putchar(ch);
            count++;
        }
        else if (count < LINE_WIDTH){
            if (ch == '\n'){
                if (count == 0)
                    printf("*");
                while(count < LINE_WIDTH){
                    printf(" ");
                    count++;
                }
                printf("*\n");
                count = 0;
            }
            else {
                putchar(ch);          
                count++;
            }
        }
        else if (count >= LINE_WIDTH){
            if (ch != '\n'){
                count++;
            }
            else {
                printf("*\n");
                count = 0;
            }
        }
        else  {
            
            count = 0;
        }        
    }
    
    return 0;
    
}

/**
 This function prints a line of multiple copies of a given character with the number
 of copies determined by the count parameter.  The line of characters is followed by a
 newline.
 @param ch  character to be printed multiple times on the line
 @param count  number of characters to print on the line
  */
void lineOfChars( char ch, int count )
{
    
    for (int i = 0; i < count + 2; i++){
        printf("%c", ch);
    }
    printf("\n");
    
}

/**
 Main function for the textbox program
 @return EXIT_SUCCESS (0) or EXIT_FAILURE (any other integer) based on program success of failure
  */
int main()
{
    
    lineOfChars(BORDER, LINE_WIDTH);    
    
    paddedLine();    
    
    lineOfChars(BORDER, LINE_WIDTH);    
    
    return EXIT_SUCCESS;
}
