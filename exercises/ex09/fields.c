#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
  // Open the input file and print an error message if we're unsuccessful.
  // (the error message is mostly to help you with debugging.  We won't test
  // this behavior).
  FILE *stream = fopen("./input.txt", "r");
  if(!stream){
    printf("Can't open input.txt file\n");
    exit(1);
  }

  // Counting input lines, so we can report errors.
  int lineCount = 1;
  int matches;
  char fname[12];
  char lname[12];
  char id[9];
  char p1[4];
  char p2[4];
  char p3[5];

  // Keep reading input lines until we reach the end-of-file.
  // Write an output line or an error message for each one.
  while( (matches = fscanf(stream, "%11s%11s %*[0-9] %8[a-z]%*[a-z@.] %*[A-Z] %3[0-9] %*[-] %3[0-9] %*[-] %4[0-9]", fname, lname, id, p1, p2, p3)) != EOF){
    
    if (matches < 6){
      // printf("Invald input, line %d\n", lineCount);
      fprintf(stderr, "Invalid input, line %d\n", lineCount);
      fscanf(stream, "%*[^\n]");
      fscanf(stream, "%*c");
    }
    else {
      printf("%8s %11s %11s %s%3s%s%3s%s%4s\n", id, fname, lname, "(", p1, ")", p2, "-", p3);
      fscanf(stream, "%*[^\n]");
      fscanf(stream, "%*c");
    }
    lineCount++;
  }

  fclose(stream);

  return EXIT_SUCCESS;
}
