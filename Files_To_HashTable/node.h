#ifndef C_Node_H
#define C_Node_H

/* the node struct. have value, file name and pointer to next node */
typedef struct Node {
    int value;
    char *file;
    struct Node *next;
} Node;
/* hash table struct. array of 29 nodes */
typedef struct hash_table {
    Node *node_array[29];
} hash_table;

void add(Node **head, char *file);
void print(Node *head);
void free_node(Node *head);

#endif
