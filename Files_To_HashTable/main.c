#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "node.h"

/*
 * Function: main
 * ----------------------------
 *   The entry point of the program. Processes input files and tracks occurrences
 *   of numbers in a hash table of linked lists.
 *
 *   Parameters:
 *   - int argc: The number of command-line arguments.
 *   - char **argv: The array of command-line arguments.
 *
 *   Returns: int
 *
 *   The function initializes a hash table, processes each input file to count
 *   occurrences of numbers, and prints the results.
 */
int main(int argc, char **argv) {
/*
 * Paramters:
 * argc: The number of command-line arguments.
 * argv: An array of strings representing the command-line arguments.
 * hash: An instance of the hash_table struct containing an array of linked lists (nodes).
 * num: An integer representing the number extracted from the input file.
 * ch: A character variable used for reading characters from the input file.
 * num_str: A dynamically allocated string used to store the number read from the input file.
 * fd: A file pointer used for opening and reading the input files.
 */
    hash_table hash;
    int i, j, num;
    char ch;
    char *num_str = NULL;
    FILE *fd;

    /* Check if there are no arguments passed to the program. */
    if (argc == 1) {
        fprintf(stderr, "No arguments passed\n");
        exit(0);
    }
    
    /* Initialize the hash table's node array to NULL. */
    for (i = 0; i < 29; i++) {
        hash.node_array[i] = NULL;
    }

    /* Process each input file passed as an argument. */
    for (i = 1; i < argc; i++) {
        /* Open the current file for reading. */
        if (!(fd = fopen(argv[i], "r"))) {
            fprintf(stderr, "Can't open file %s\n", argv[i]);
            exit(0);
        }
        /* Read the file character by character. */
        while (!feof(fd)) {
            /* Allocate memory for a string to store the number read from the file. */
            num_str = (char *) malloc(3 * sizeof(char));
            if (!num_str) {
                fprintf(stderr, "Allocation failed\n");
                exit(0);
            }
            ch = (char) fgetc(fd);
            j = 0;
            /* Skip whitespace characters. */
            if (isspace(ch))
                continue;
            /* Read characters until a whitespace or end-of-file is encountered. */
            while ((!isspace(ch)) && (!feof(fd))) {
                /* Ensure the number does not exceed 99. */
                if (j > 1) {
                    fprintf(stderr, "ERROR: In the file, there is number bigger than 99 or characters\n");
                    exit(0);
                }
                num_str[j] = ch;
                j++;
                ch = (char) fgetc(fd);
            }
            num_str[j] = '\0';
            /* Skip empty strings. */
            if (num_str[0] == '\0')
                continue;
            /* Convert the string to an integer. */
            num = atoi(num_str);
            /* Ensure the number is within the valid range. */
            if ((num > 28) || (num < 0)) {
                fprintf(stderr, "ERROR: Number greater than 28 or less than 0\n");
                exit(0);
            }
            /* Add the number to the hash table. */
            add(&hash.node_array[num], argv[i]);
            /* Free the allocated memory for the number string. */
            free(num_str);
        }
        /* Close the current file. */
        fclose(fd);
    }

    /* Print the results for each number in the hash table. */
    for (i = 0; i < 28; i++) {
        if (hash.node_array[i]) {
            fprintf(stdout, "%d appears in ", i);
            print(hash.node_array[i]);
        }
        /* Free the linked list associated with the current number. */
        free_node(hash.node_array[i]);
    }
    return 0;
}

