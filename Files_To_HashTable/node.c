#include <stdlib.h>
#include <stdio.h>
#include "node.h"

/*
 * Parameters:
 * head: A pointer to the pointer of the first node in the linked list (the head of the list).
 * file: A string representing the file name to be added or checked in the list.
 */


/*
 * Function: add
 * ----------------------------
 *   Adds a new file node to the linked list or increments the count if it already exists.
 *
 *   head: A double pointer to the head of the linked list of nodes.
 *   file: The file name to be added or updated in the list.
 *
 *   Returns: void
 *
 *   The function allocates memory for a new node. If the file already exists in the list,
 *   it increments the node's value. Otherwise, it adds a new node to the end of the list or
 *   at the head if the list is empty.
 */
void add(Node **head, char *file) {
/*
 * Parameters:
 * p1: A pointer used to traverse the list to find a node or the end of the list.
 * p2: A pointer used to track the previous node during traversal.
 * new_Node: A pointer to a newly allocated node intended to be added to the list.
 */

    Node *p1, *p2, *new_Node;
    /* Allocate memory for a new node and check if the allocation was successful. */
    new_Node = (Node *) malloc(sizeof(Node));
    if (!new_Node) {
        fprintf(stderr, "Allocation failed\n");
        exit(0);
    }

    /* Initialize the new node's file with the given file name. */
    new_Node->file = file;

    /* Initialize pointers for traversal. */
    p1 = *head;
    p2 = NULL;

    /* Traverse the list to find if the file already exists. */
    while (p1 && (p1->file != file)) {
        p2 = p1;
        p1 = p1->next;
    }

    /* If the file does not exist in the list, add a new node. */
    if (p1 == NULL) {
        new_Node->value = 1;
        new_Node->next = NULL;

        /* If the list is empty, set the new node as the head. */
        if (p2 == NULL) {
            *head = new_Node;
        } else {
            /* Otherwise, add the new node to the end of the list. */
            p2->next = new_Node;
        }
    } else {
        /* If the file already exists, increment the node's value and free the new node. */
        p1->value++;
        free(new_Node);
    }
}

/*
 * Function: print
 * ----------------------------
 *   Prints the contents of the linked list of nodes.
 *
 *   head: A pointer to the head of the linked list of nodes.
 *
 *   Returns: void
 *
 *   The function iterates over the list and prints each node's file name and value.
 *   It handles singular and plural cases for the printed output.
 */
void print(Node *head) {
/*
 * Parameters:
 * temp: A pointer used to traverse the list for printing.
 */

    Node *temp = head;

    /* If the list is empty, return immediately. */
    if (!temp)
        return;

    /* Traverse the list and print each node's information. */
    while (temp) {
        if (temp->value == 1)
            fprintf(stdout, "file %s - %d time", temp->file, temp->value);
        else
            fprintf(stdout, "file %s - %d times", temp->file, temp->value);

        /* If there is another node, print a comma separator. */
        if (temp->next)
            fprintf(stdout, ", ");
        temp = temp->next;
    }
    fprintf(stdout, "\n");
}

/*
 * Function: free_node
 * ----------------------------
 *   Frees the memory allocated for the linked list of nodes.
 *
 *   head: A pointer to the head of the linked list of nodes.
 *
 *   Returns: void
 *
 *   The function iterates over the list and frees each node's memory.
 */
void free_node(Node *head) {
/*
 * Parameters:
 * p: A pointer used to temporarily hold the current node while freeing memory.
 */

    Node *p;

    /* Traverse the list and free each node. */
    while (head) {
        p = head;
        head = head->next;
        free(p);
    }
}

