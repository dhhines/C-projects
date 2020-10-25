/**
 * @author David Hines
 * @file <insert_progam_file_name>.c
 *
 * This is a template .c file for CSC230 to simplify the start of any programming
 * project for the course.  The purpose of the program and any relevant details
 * regarding this programs interaction with other headers or object files should
 * be described in this section.
 */

#include "input.h"
#include "catalog.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAB_SIZE 4


// definition of the Book struct and type
struct Book_Struct {
    int id;
    char title[MAX_TITLE + 1];
    char author[MAX_AUTHOR + 1];
    double level;
    int words;
    char *subjects;
};

// definition of the Catalog struct and type
struct Catalog_Struct {
    Book **books;
    int count;
    int capacity;
};

// declaration and defintion of comparison struct for data to compare
typedef struct Comp_Struct{
    double min;
    double max;
    const char *keyword;
} Comp;

/**
 * comparison function for providing qsort how to sort the Books by IDs
 * @param *ptr1 void pointer cast inside the compare function to pointer to pointer to Book
 * @param *ptr2 void pointer cast inside the compare function to pointer to pointer to Book
 * @return integer value of -1, 1 or 0 depending on comparison
 */
static int idComp( const void *ptr1, const void *ptr2 ){

    const Book *p1 = *(Book **)ptr1;
    const Book *p2 = *(Book **)ptr2;

    if (p1->id < p2->id)
        return -1;
    else if (p1->id > p2->id)
        return 1;
    else
        return 0;
}

/**
 * comparison function for providing qsort how to sort the Books by level.  If the level of
 * the compared books are the same, the ID will be used for the sort.
 * @param *ptr1 void pointer cast inside the compare function to pointer to pointer to Book
 * @param *ptr2 void pointer cast inside the compare function to pointer to pointer to Book
 * @return integer value of -1, 1 or 0 depending on comparison
 */
static int lvlComp( const void *ptr1, const void *ptr2 ){

    const Book *p1 = *(Book **)ptr1;
    const Book *p2 = *(Book **)ptr2;

    if (p1->level < p2->level)
        return -1;
    else if (p1->level > p2->level)
        return 1;
    else if (p1->level == p2->level){
        if (p1->id < p2->id)
            return -1;
        else if (p1->id > p2->id)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

/**
 * Test function that simply returns true regardless of the
 * book and data passed for comparison.  This ensures that all
 * books are printed from the source catalog.
 *
 * @param *book const pointer to a book object to be tested
 * @param *data to use for testing against the object - unused for this function
 * @return true for all books passed to the test function
 *
 */
static bool printAll(Book const *book, void const *data){
    return true;
}

/**
 * Test function that returns true if the book is between the min
 * and max levels provided to the test function.
 *
 * @param *book const pointer to a book object to be tested
 * @param *data to use for testing against the object - unused for this function
 * @return true for all books passed to the test function
 */
static bool printLvl(Book const *book, void const *data){
    const Comp testData = *(Comp *)data;

    if (book->level >= testData.min && book->level <= testData.max)
        return true;
    else
        return false;
}

/**
 * Test function that returns true if the book has subject keywords that match
 * the input subject keyword by the user.
 *
 * @param *book const pointer to a book object to be tested
 * @param *data to use for testing against the object - subject keyword for this function
 * @return true for all books passed to the test function
 */
static bool printSubject(Book const *book, void const *data){
    const char *testData = (char *)data;

    const char *str = strstr(book->subjects, testData);

    if (str)
        return true;
    else
        return false;

}

void mngList(const char func, const Catalog *cat, Catalog *list, const int id){

    //Only run this block of code if the intent is to add a book
    if (func == 'a') {
        //first check to see if this id is already in the reading list
        for (int i = 0; i < list->count; i++){
            if (list->books[i]->id == id){
                printf("Book %d is already on the reading list\n", id);
                return;
            }
        }

        //loop through the catalog and add the book to list if found
        for (int i = 0; i < cat->count; i++){
            if (cat->books[i]->id == id){
                //verify books array memory has enough to hold additional books or expand
                if (list->capacity <= list->count){
                    list->capacity *= 2;
                    list->books = (Book **) realloc(list->books, list->capacity * sizeof(Book));
                }
                list->books[list->count] = cat->books[i];
                list->count++;
                return;
            }
        }

        //if it gets this far then the ID is not in the
        printf("Book %d is not in the catalog\n", id);
    }

    //Only run this block of code if the intent is to remove a book
    if (func == 'r'){
        for (int i = 0; i < list->count; i++){
            if (list->books[i]->id == id){
                for (int k = i; k < list->count -1; k++){
                    list->books[k] = list->books[k + 1];
                }
                list->count--;
                return;
            }
        }
        printf("Book %d is not on the reading list\n", id);
    }
}

void printlist(Catalog *list){

    if (list->count > 0){
        int wordCnt = 0;
        double avgLvl = 0;
        Comp dataTemp = {avgLvl, avgLvl};
        listCatalog(list, printAll, &dataTemp);

        for (int i = 0; i < list->count; i++){
            wordCnt += list->books[i]->words;
            avgLvl += list->books[i]->level;
        }
        avgLvl = avgLvl / list->count;
        printf("%71.1lf %7d", avgLvl, wordCnt);
    } else
    {
        printf("List is empty");
    }
}

Catalog *makeCatalog()
{
    Catalog *cat = (Catalog *) malloc (sizeof( Catalog));
    cat->books = (Book **) malloc(sizeof(Book *) * INIT_CPCTY);
    cat->count = 0;
    cat->capacity = INIT_CPCTY;

    return cat;
}

void freeCatalog(Catalog *cat)
{
    //need to rotate through books first AND make sure to free up the Subjects pointers as well
    for (int i = 0; i < cat->count; i++){
        free(cat->books[i]->subjects);
        free(cat->books[i]);
    }

    //then free up the books array and catalog itself
    free(cat->books);
    free(cat);
}

void freeList(Catalog *list){
    free(list->books);
    free(list);
}

void readCatalog(Catalog *cat, char const *filename)
{
    //read in the file and create the list of books
    //pointer to a string in dynamnically allocated memory returned by readLine
    char *lineText;

    FILE *fp = fopen(filename, "r");

    if (!fp){
        fprintf(stderr, "Can't open file: %s\n", filename);
        freeCatalog(cat);
        exit(EXIT_FAILURE);
    }

    while ((lineText = readLine(fp))){
        //create temporary book to hold information before adding to catalog
        Book *newBook = (Book *) malloc(sizeof(Book));

        //verify books array memory has enough to hold additional books or expand
        if (cat->count >= cat->capacity){
            cat->capacity *= 2;
            cat->books = (Book **) realloc(cat->books, cat->capacity * sizeof(Book *));
        }

        int val = 0;  //storing %n value
        int cursor = 0; //cummulative cursor location
        int match = 0; //number of matches

        //capture the Book ID from the text block
        match = sscanf(lineText, "%d%n", &newBook->id, &val);

        if (match != 1){
            //invalidBookList(filename);
            fprintf(stderr, "Invalid book list: %s\n", filename);
            free(newBook);
            free(cat);
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < cat->count; i++){
            if (cat->books[i]->id == newBook->id){
                fprintf(stderr, "Duplicate book id: %d\n", newBook->id);
                free(newBook);
                free(cat);
                exit(EXIT_FAILURE);
            }
        }
        cursor += val;  //move cursor tracking to where left off after getting ID

        //capture the Book Title from the text block and pick up from after ID field
        match = sscanf(lineText + cursor, " %39[^\t]%n", newBook->title, &val);

        cursor += val;  //move cursor tracking to where left off but don't add tab size yet

        if (match != 1){
            fprintf(stderr, "Invalid book list: %s\n", filename);
            free(newBook);
            free(cat);
            exit(EXIT_FAILURE);
            //invalidBookList(filename);
        }
        if (strlen(newBook->title) > MAX_TITLE){
            newBook->title[MAX_TITLE - 2] = '.';
            newBook->title[MAX_TITLE - 1] = '.';
            newBook->title[MAX_TITLE] = '\0';
            //throw away any of the title longer than 38 characters
            sscanf(lineText + cursor - 1, "%*[^\t]%n", &val);
            cursor += val;  //increment cursor to account to move forward and tab size
        }

        //capture the Book Author from the text block and pick up from after Author field
        match = sscanf(lineText + cursor, " %21[^\t]%n", newBook->author, &val);

        cursor += val;  //move cursor tracking to where left off but don't add tab size yet

        if (match != 1){
            fprintf(stderr, "Invalid book list: %s\n", filename);
            free(newBook);
            free(cat);
            exit(EXIT_FAILURE);
            //invalidBookList(filename);
        }

        if (strlen(newBook->author) > MAX_AUTHOR){
            newBook->author[MAX_AUTHOR - 2] = '.';
            newBook->author[MAX_AUTHOR - 1] = '.';
            newBook->author[MAX_AUTHOR] = '\0';
            //throw away any of the title longer than 20 characters
            sscanf(lineText + cursor - 1, "%*[^\t]%n", &val);
            cursor += val;  //increment cursor to account to move forward and tab size
        }

        //capture the Book Level from the text block and pick up from after Author field
        match = sscanf(lineText + cursor, " %lf%n", &newBook->level, &val);
        if (match != 1){
            fprintf(stderr, "Invalid book list: %s\n", filename);
            free(newBook);
            free(cat);
            exit(EXIT_FAILURE);
            //invalidBookList(filename);
        }
        cursor += val;  //increment past level and update cursor

        //capture the Book Words from the text block and pick up from after Level field
        match = sscanf(lineText + cursor, " %d%n", &newBook->words, &val);
        if (match != 1){
            fprintf(stderr, "Invalid book list: %s\n", filename);
            free(newBook);
            free(cat);
            exit(EXIT_FAILURE);
            //invalidBookList(filename);
        }
        cursor += val;  //increment past words and update cursor

        //capture the Book Subjects from the text block and pick up from after Words field
        char ch;  //used to collect all characters from the line text
        int cap = INIT_CPCTY;  //used to resize the capacity of the memory for the subjects
        int len = 0;  //used for keeping length of array and adding capacity as needed
        //create init heap mem for subjects
        newBook->subjects = (char *) malloc(cap * sizeof(char) + 1);
        while (sscanf(lineText + cursor, "%c%n", &ch, &val) == 1){
            if (len >= cap){
                cap *=2;
                newBook->subjects = (char *) realloc(newBook->subjects, cap * sizeof(char) + 1);
            }
            if (ch == '\0')
                break;
            newBook->subjects[len++] = ch;
            cursor += val;
        }
        newBook->subjects[len] = '\0'; //add the null terminator at the end of Subjects string

        cat->books[cat->count] = newBook;
        cat->count++;

        free(lineText);
    }
    fclose(fp);
}

void listAll(Catalog *cat)
{
    Comp *data1;
    qsort(cat->books, cat->count, sizeof( cat->books), idComp);
    listCatalog(cat, printAll, &data1);
}

void listLevel(Catalog *cat, double min, double max)
{
    Comp data = {min, max};
    qsort(cat->books, cat->count, sizeof( cat->books), lvlComp);
    listCatalog(cat, printLvl, &data);
}

void listSubject(Catalog *cat, char const *subject)
{
    qsort(cat->books, cat->count, sizeof( cat->books), idComp);
    listCatalog(cat, printSubject, subject);
}

void listCatalog(Catalog *cat, bool test(Book const *book, void const *data), void const *data)
{
    int numBooks = 0;
    //need to verify that there is at least 1 book matching the test or print alternate output
    for (int i = 0; i < cat->count; i++){
        if (test(cat->books[i], data)){
            numBooks++;
        }
    }

    if (numBooks == 0){
        printf("No matching books\n");
    } else{
        //print the column headers for the book list to print
        printf("%5s%39s%21s%6s%8s\n", "ID", "Title", "Author", "Level", "Words");

        for (int i = 0; i < cat->count; i++){
            if (test(cat->books[i], data)){
                printf("%5d%39s%21s%6.1lf%8d\n", cat->books[i]->id, cat->books[i]->title,
                cat->books[i]->author, cat->books[i]->level, cat->books[i]->words);
            }
        }
    }
}
