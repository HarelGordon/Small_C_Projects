#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The main function that drives the program. 
 * It initializes the sets and the user input loop.
 */


int main()
{	
	/* Initialize the sets and set pointers */
	set SETA = { 0 }, SETB = { 0 }, SETC = { 0 }, SETD = { 0 }, SETE = { 0 }, SETF = { 0 };
	set *sets_array[6];
	/* Array of function names for validation */
	char *functions[] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set"}; 

	char *line = NULL;
	char *temp = NULL;
	int len = 100;
	char deli[3] = " ,\t";
	char *token = NULL;
	char *func_name = NULL;
	char **parameters = NULL;
	int count_token;
	/* Assign sets to the set array */
	sets_array[0] = &SETA;
	sets_array[1] = &SETB;
	sets_array[2] = &SETC;
	sets_array[3] = &SETD;
	sets_array[4] = &SETE;
	sets_array[5] = &SETF;
	/* Main loop to continuously accept user input */
	while (1)
	{
		/* Allocate memory for the input line */
		line = (char *)malloc(len * sizeof(char));
		if (line == NULL)
		{
		    fprintf(stderr, "Memory allocation failed\n");
		    return 1;
		}
		printf("Enter command please: ");
		/* Read the input line from the user */
		while (1)
		{
			if (fgets(line, len, stdin) == NULL)
			{
				if (feof (stdin)) /*EOF*/
					printf ("EOF without stop command.\n");
				else
					printf ("Error reading input\n");
				free(line);
				return 1;
			}
			len = strlen (line);
			if (line[len - 1] == '\n')
			{ 
			        line[len - 1] = '\0';
			        break;
			}
			/* Reallocate memory if the input line is longer than expected */
			len += 20;
			temp = (char *)realloc(line, len * sizeof(char));
			if (temp == NULL)
			{
		        	fprintf(stderr, "Memory reallocation failed\n");
		        	free(line);
		        	return 1;
			}
			line = temp;
		}
		printf ("You entered: %s\n", line);
		/* Check for empty input line */
		if (strcmp(line, "") == 0)
		{
			printf ("You entered an empty line.\n");
			free (line);
			len = 100;
			continue;
		}
		/* Check for syntax errors related to commas */
		if (check_comma (line))
		{
			free (line);
			len = 100;
			continue;
		}
		/* Tokenize the input line to extract the function name and parameters */
		token = strtok (line, deli);
		if (token == NULL)
		{
			printf ("You entered spaces and/or tabs\n");
			free (line);
			len = 100;
			continue;
		}
		count_token = 1;
		func_name = token;
		parameters = (char **) malloc (sizeof(char *) * 2);
		token = strtok(NULL, deli);
		while (token != NULL)
		{
			parameters[count_token - 1] = token;
			count_token++;
			parameters = (char **) realloc (parameters, sizeof(char *) * (count_token));
			if (parameters == NULL)
				printf ("alocation parameters failed\n");
			token = strtok(NULL, deli);
		}

		/* Execute the corresponding function based on the user input */
		if (strcmp(func_name, "stop") == 0)
		{
			if (check_parameters_stop (count_token - 1) == 0)			
				break;
		}
		else if (strcmp(func_name, functions[0]) == 0) /*read_set*/
		{
			if (check_parameters_read_set (parameters, count_token - 1, sets_array) == 0)
				read_set (parameters, count_token - 1, sets_array);			
		}
		else if (strcmp(func_name, functions[1]) == 0) /*print_set*/
		{
			if (check_parameters_print_set (parameters, count_token - 1, sets_array) == 0)
			{
				printf ("%s after print_set: ", parameters[0]);
				print_union (print_set (string_to_set (parameters[0], sets_array)));
			}
		}
		else if (strcmp(func_name, functions[2]) == 0) /*union_set*/
		{
			if (check_parameters_union_intersect_sub_symdiff_set (parameters, count_token - 1, sets_array) == 0)
				union_set (sets_array, parameters);
		}
		else if (strcmp(func_name, functions[3]) == 0) /*intersect_set*/
		{
			if (check_parameters_union_intersect_sub_symdiff_set (parameters, count_token - 1, sets_array) == 0)
				intersect_set (sets_array, parameters);
		}
		else if (strcmp(func_name, functions[4]) == 0) /*sub_set*/
		{
			if (check_parameters_union_intersect_sub_symdiff_set (parameters, count_token - 1, sets_array) == 0)
				sub_set (sets_array, parameters);
		}
		else if (strcmp(func_name, functions[5]) == 0) /*symdiff*/
		{
			if (check_parameters_union_intersect_sub_symdiff_set (parameters, count_token - 1, sets_array) == 0)
				symdiff_set (sets_array, parameters);
		}
		else
			printf ("Undefined command name\n");
		/* Free the allocated memory for the line and parameters */
		free (line);
		len = 100;
		free (parameters);
	}
	return 0;
}

