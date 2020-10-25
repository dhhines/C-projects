/**
 * @author David Hines
 * @file catalog.h
 *
 * Header file for the catalog.c functionality so those functions, variables
 * and preprocessor constants can be used by other components of the program.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TITLE 38

#define MAX_AUTHOR 20

#define INIT_CPCTY 5

/**
 * Catalog struct type declaration
 */
typedef struct Catalog_Struct Catalog;

/**
 * Book struct type declaration
 */
typedef struct Book_Struct Book;

/**
 * Function that adds the Book with matching ID number to the reading list from
 * the Catalog. If the book with the provided ID does not exist in the Catalog
 * then it will print a message back to the console letting the user know the book
 * is not present and returns to cmd> prompt.
 * @param func is a char value that tells the mngList function to add ('a') or remove('r') a book
 * @param *cat pointer to the catalog
 * @param *list pointer to the reading list
 * @param id the id of the book to add to the list
 */
void mngList(const char func, const Catalog *cat, Catalog *list, const int id);

/**
 * Function to print all of the books on the reading list as well as the average reading
 * level and total words for all books.
 * @param *list pointer to the current reading list
 */
void printlist(Catalog *list);

/**
 * Function to dynamically allocate storage for the catalog and initializes
 * the fields to store a resizeable array for the books and returns a pointer
 * to the catalog memory location.
 *
 * @return pointer to the Catalog created by this function
 */
Catalog *makeCatalog();

/**
 * Frees the memory allocated to the catalog, the books and the resizeable
 * array holding pointers to the books.
 *
 * @param *cat  pointer to the current Catalog for the application
 */
void freeCatalog(Catalog *cat);

/**
 * Frees the memory allocated to the reading list and the resizeable array
 * of pointers to the books in the list.
 * @param *list  pointer to the reading list
 */
void freeList(Catalog *list);


/**
 *
 *
 * @param *cat  pointer to the current Catalog for the application
 * @param pointer to a catalog file of books to be added
 */
void readCatalog(Catalog *cat, char const *filename);


/**
 *
 *
 * @param *cat  pointer to the current Catalog for the application
 */
void listAll(Catalog *cat);


/**
 *
 *
 * @param *cat  pointer to the current Catalog for the application
 * @param min minimum reading level for books to list
 * @param max maximum reading level for books to list
 */
void listLevel(Catalog *cat, double min, double max);

/**
 *
 *
 * @param *cat  pointer to the current Catalog for the application
 * @param *subject  pointer to the string of subjects to search and list books that match
 */
void listSubject(Catalog *cat, char const *subject);


/**
 *
 *
 * @param *cat  pointer to the current Catalog for the application
 * @param test  pointer to the function test
 * @param *data  pointer to an arbitrary block of memory to identify books to print out
 */
void listCatalog(Catalog *cat, bool test(Book const *book, void const *data), void const *data);
