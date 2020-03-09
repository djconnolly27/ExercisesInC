/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
*
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {
    Node *curr = *list;
    if (curr == NULL) {
      return -1;
    }
    int val = curr->val;
    *list = curr->next;
    return val;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {
    Node *prev_head = *list;
    Node *new = make_node(val, prev_head);
    *list = new;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {
    Node *prev = NULL;
    Node *curr = *list;
    int num_removed = 0;
    while (curr != NULL) {
      // Node *n = curr->next;
      if (curr->val == val) {
        if (prev == NULL) {
          *list = curr->next;
        } else {
          prev->next = curr->next;
        }
        num_removed++;
        free(curr);
        break;
      }
      if (prev == NULL) {
        prev = *list;
      } else {
        prev = prev->next;
      }
      curr = curr->next;
    }
    return num_removed;
}


/* Reverses the elements of the list.
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
    Node *curr = *list;
    Node *nxt = curr->next;
    curr->next = NULL;
    while (nxt != NULL) {
      Node *temp = nxt->next;
      nxt->next = curr;
      curr = nxt;
      nxt = temp;
    }
    *list = curr;
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);
    head->next->next->next->next = make_node(5, NULL);

    Node **list = &head;
    print_list(list);

    int retval = pop(list);
    // printf("%i\n", retval);
    print_list(list);

    push(list, retval+10);
    print_list(list);

    remove_by_value(list, 3);
    print_list(list);

    remove_by_value(list, 2);
    print_list(list);

    reverse(list);
    print_list(list);
}
