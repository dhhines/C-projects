/**
 * @author David Hines
 * @file insertion.c
 *
 * Program to insert a linked list Node at the proper location in a sorted list.
 * The program takes integer values obtained from standard input, creates a node
 * with the interger value and then inserts that new node in the proper location
 * in the sorted list (from smallest integer value to largest).
 * The list contents are printed to the console in the list order
 */

// Code to read numbers from standard input inserting them into a list
// in sorted order as we read them.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node for building our linked list.
struct NodeStruct {
  // Value in this node.
  int value;

  // Pointer to the next node.
  struct NodeStruct *next;
};

// A short type name to use for a node.
typedef struct NodeStruct Node;

/*
  Create a node for the given value and insert it into the given list
  in the proper location to keep the list sorted.  Return an updated
  head pointer.  The head should only need to change if this value gets
  inserted at the front of the list.  Otherwise, you can just return
  the old head pointer.
*/
Node *insert( Node *head, int val )
{
  //create the new node with the value provided
  Node *n = (Node *) malloc( sizeof(Node));
  n->value = val;

  if (head){ //make sure the list is not NULL
    if (n->value < head->value){ //insert at the beginning of list
        n->next = head;
        return n; //new head of list
    }
    for (Node *c = head; c; c = c->next){  //traverse list to find spot for insertion
      if (c->next && n->value >= c->value && n->value < c->next->value){  //not inserting at end of list
        n->next = c->next;
        c->next = n;
        return head;
      }
      else if (n->value >= c->value && !c->next){ //hit the end of the list
        c->next = n;
        return head;
      }
    }
  }
  else { //special case where list is empty and return new head of list
    n->next = head;
    return n;
  }
  return head;

}

int main()
{
  // Pointer to the head node.
  Node *head = NULL;

  // Read a list of numbers from building a sorted list as we
  // read them.
  int x;
  while ( scanf( "%d", &x ) == 1 ){
    // Insert the new value, and get back the (possibly updated) head pointer.
    head = insert( head, x );
  }

  // Print out the list.
  Node *cursor = head;
  while(cursor){
    printf("%d ", cursor->value);
    cursor = cursor->next;
  }
  printf("\n");

  // Free all the nodes starting with head and use new Node to replace head at each step
  while (head){
    Node *next = head->next;
    free(head);
    head = next;
  }

  return EXIT_SUCCESS;
}
