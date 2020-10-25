/**
 * @author David Hines
 * @file <insert_progam_file_name>.c
 *
 * This is a template .c file for CSC230 to simplify the start of any programming
 * project for the course.  The purpose of the program and any relevant details
 * regarding this programs interaction with other headers or object files should
 * be described in this section.
 */

#include "catalog.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_CMD 8

/**
 * Function to print error message to screen when invalid arguments are passed
 * in via the command line.
 */
static void invalidCmd()
{
    printf("Invalid command\n" );
}

/**
 * Start of the reading list program
 * @param argc the number of arguments passed in from the user at console
 * @param *argv pointer to the string values for each of the console inputs
 */
int main(int argc, char *argv[])
{
    //create the catalog
    Catalog *cat = makeCatalog();

    //if there are no command line arguments then exit
    if (argc <= 1){
        fprintf(stderr, "usage: reading <book-list>*\n");
        free(cat);
        exit(EXIT_FAILURE);
    }

    //create the catalog until the files are empty
    for (int i = 1; i < argc; i++){
        readCatalog(cat, argv[i]);
    }

    //create a catalog of books that are in the reading list
    Catalog *readList = makeCatalog();

    //initial command prompt for the user
    printf("cmd> ");
    char *cmdString;
    while ((cmdString = readLine(stdin)) != NULL){

        int cursor = 0;
        int matches = 0;
        int val;
        double min;
        double max;
        int id;
        char cmd[MAX_CMD] = "cmd";
        char temp[MAX_CMD] = "tmp";

        if (!(sscanf(cmdString, " %7[a-z]%n", cmd, &val))){
            invalidCmd();
            break;
        }

        cursor += val;

        //Echo the cmd back to the console
        printf("%s\n", cmdString);
        if (strcmp(cmd, "catalog") == 0){
            if ((matches = sscanf(cmdString + cursor, "%s", temp)) >= 1) {
                temp[0] = '\0';
                assert(matches < 1);
                invalidCmd();
            }
            listAll(cat);
        }
        else if (strcmp(cmd, "level") == 0){
            char temp[MAX_CMD];
            if ((matches = sscanf(cmdString + cursor, "%lf%lf%n", &min, &max, &val)) != 2)
                invalidCmd();
            else if (min > max)
                invalidCmd();
            else if ((matches = sscanf(cmdString + cursor + val, "%s", temp)) >= 1) {
                temp[0] = '\0';
                invalidCmd();
            }
            else
                listLevel(cat, min, max);
        }
        else if (strcmp(cmd, "subject") == 0){
            int keysize = strlen(cmdString);
            char keyword[keysize];
            if ((matches = sscanf(cmdString + cursor, "%s%n", keyword, &val)) != 1)
                invalidCmd();
            else if ((matches = sscanf(cmdString + cursor + val, "%s", temp)) >= 1) {
                temp[0] = '\0';
                invalidCmd();
            }
            else
                listSubject(cat, keyword);
        }
        else if (strcmp(cmd, "add") == 0){
            if ((matches = sscanf(cmdString + cursor, "%d%n", &id, &val)) != 1)
                invalidCmd();
            else if ((matches = sscanf(cmdString + cursor + val, "%s", temp)) >= 1) {
                temp[0] = '\0';
                invalidCmd();
            }
            else
                mngList('a', cat, readList, id);
        }
        else if (strcmp(cmd, "remove") == 0){
            if ((matches = sscanf(cmdString + cursor, "%d%n", &id, &val)) != 1)
                invalidCmd();
            else if ((matches = sscanf(cmdString + cursor + val, "%s", temp)) >= 1) {
                temp[0] = '\0';
                invalidCmd();
            }
            else
                mngList('r', cat, readList, id);
        }
        else if (strcmp(cmd, "list") == 0){
            printlist(readList);
            printf("\n");
        }
        else if (strcmp(cmd, "quit") == 0){
            free(cmdString);
            freeList(readList);
            freeCatalog(cat);
            exit(EXIT_SUCCESS);
        }
        else
            invalidCmd();

        printf("\ncmd> ");
        free(cmdString);
    }

    //free(cmdString);
    freeList(readList);
    freeCatalog(cat);

    return EXIT_SUCCESS;
}
