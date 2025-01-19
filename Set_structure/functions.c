#include "set.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* 
 * Converts a string representation of a set to the corresponding set pointer.
 * Parameters:
 * - set_in_string: A string representing the set name.
 * - sets_array: An array of set pointers.
 * Returns: A pointer to the corresponding set or NULL if the set name is invalid.
 */

set *string_to_set(char *set_in_string, set **sets_array) {
	if (strcmp(set_in_string, "SETA") == 0)
		return sets_array[0];
	else if (strcmp(set_in_string, "SETB") == 0)
		return sets_array[1];
	else if (strcmp(set_in_string, "SETC") == 0)
		return sets_array[2];
	else if (strcmp(set_in_string, "SETD") == 0)
		return sets_array[3];
	else if (strcmp(set_in_string, "SETE") == 0)
		return sets_array[4];
	else if (strcmp(set_in_string, "SETF") == 0)
		return sets_array[5];
	return NULL;
}


/* 
 * Checks the syntax of commas in a given line.
 * Ensures no comma at the end, no consecutive commas, and correct spacing around commas.
 * Parameters:
 * - line: A string to be checked.
 * Returns: 1 if the syntax is incorrect, otherwise 0.
 */

int check_comma (char *line)
{
	int i;
	int j = 1;
	int comma_count = 0, count_non_blank_char = 0, count_sets = 0, is_S = 0;

	/*Check if the command ends with a comma.*/
	while ((line [strlen (line) - j] == ' ') || (line [strlen (line) - j] == '\t'))
		j++;
	if (line[strlen (line) - j] == ',')
	{
		printf ("The command ends with ','\n");
		return 1;
	}
	/* Check for consecutive commas.*/
	for (i = 0; i < strlen (line) - 1; i++)
	{
		if ((line[i] == ',') && (line[i+1] == ','))
			comma_count ++;
	}
	if (comma_count > 0)
	{
		printf ("There are 2 commas one after the other\n");
		return 1;
	}
	j = 1;
	for (i = 0; i < strlen (line); i++)
	{
		/* Check the spacing between the command and the first set.*/
		if ((line[i] == 'S') && (count_sets == 0))
		{
			count_sets++;
			while (line[i-j] != 't')
			{
				if ((i-j) < 0)
				{
					printf ("Between command and set, must be only spaces or tabs\n");
					return 1;
				}
				if ((line[i-j] != ' ') && (line[i-j] != '\t'))
				{
					printf ("Between command and set, must be only spaces or tabs\n");
					return 1;
				}
				j++;
			}
		}
		/* Check for spaces and tabs between sets separated by commas.*/
		if (line[i] == ',')
		{
			j = 1;
			while (line[i + j] != ',')
			{
				if ((i + j) == strlen (line) - 1)
					break;
				if ((line[i + j] != ' ') && (line[i + j] != '\t'))
					count_non_blank_char ++;
				j++;	
			}
			if (count_non_blank_char == 0)
			{
				printf ("You entered comma, blank characters, and comma again\n");
				return 1;
			}
		}
	}
	/* Check for missing commas.*/
	i = 0;
	while (i < strlen (line))
	{
		if (is_S == 0)
		{
			while (line[i] != 'S')
			{
				if (i > strlen (line) - 1)
					return 0;
				i++;
			}
			is_S ++;
		}
		while ((line[i] != ' ') && (line[i] != '\t'))
		{
			if (i > strlen (line) - 1)
				return 0;
			i++;
		}
		if (line[i-1] != ',')
		{
			while ((line[i] == ' ') || (line[i] == '\t'))
			{
				if (i > strlen (line) - 1)
					return 0;
				i++;
			}
			if (line[i] != ',')
			{
				printf ("Missing comma\n");
				return 1;
			}
		}
		else
		{
			while ((line[i] == ' ') || (line[i] == '\t'))
			{
				if (i > strlen (line) - 1)
					return 0;
				i++;
			}
		}
		i++;
	}
	return 0;
}


/* 
 * Validates the parameters for the read_set command.
 * Ensures the first parameter is a valid set and subsequent parameters are valid integers within range.
 * Parameters:
 * - parameters: Array of strings representing the command parameters.
 * - parameters_length: Length of the parameters array.
 * - sets_array: Array of set pointers.
 * Returns: 1 if there is an error in the parameters, otherwise 0.
 */

int check_parameters_read_set (char **parameters, int parameters_length, set **sets_array)
{
	int i, j, num;
	int not_sets_count = 0;
	/* Verify if the first parameter is a valid set.*/
	for (i=0; i<6; i++)
	{
		if (string_to_set (parameters[0], sets_array) != sets_array[i])
			not_sets_count ++;
	}
	if (not_sets_count == 6)
	{
		printf ("Enter valid set please\n");
		return 1;
	}
	/* Check if the subsequent parameters are valid integers and within range.*/
	i = 1;
	while (1)
	{
		if (i == parameters_length)
		{
			printf ("You must end read_set with '-1'\n");
			return 1;
		}
		num = atoi (parameters[i]);
		if (num == -1)
		{
			i++;
			break;
		}
		for (j=0; j<strlen (parameters[i]); j++)
		{
			if (!((parameters[i][j] >= '0') && (parameters[i][j] <= '9')))
			{
				printf ("read_set gets only integers after set, and they must be positive\n");
				return 1;
			}
		}
		if ((num < 0) || (num > 127))
		{
			printf ("Invalid set member – value out of range\n");
			return 1;
		}
		i++;
	}
	/* Check for extraneous text after the command.*/
	if (i < parameters_length)
	{
		printf ("Extraneous text after end of command\n");
		return 1;
	}
	return 0;
}


/* 
 * Validates the parameters for the print_set command.
 * Ensures there is only one parameter and it is a valid set.
 * Parameters:
 * - parameters: Array of strings representing the command parameters.
 * - parameters_length: Length of the parameters array.
 * - sets_array: Array of set pointers.
 * Returns: 1 if there is an error in the parameters, otherwise 0.
 */

int check_parameters_print_set (char **parameters, int parameters_length, set **sets_array)
{
	int i;
	int not_sets_count = 0;
	/* Ensure only one parameter is provided.*/
	if (parameters_length > 1)
	{
		printf ("Extraneous text after end of command\n");
		return 1;
	}
	/* Verify if the parameter is a valid set.*/
	for (i=0; i<6; i++)
	{
		if (string_to_set (parameters[0], sets_array) != sets_array[i])
			not_sets_count ++;
	}
	if (not_sets_count == 6)
	{
		printf ("Enter valid set please\n");
		return 1;
	}
	return 0;
}


/* 
 * Prints the elements of a set in a formatted manner.
 * Parameters:
 * - str: An array of Data structures representing the set elements.
 */

void print_union (Data *str)
{
	int i;
	int count = str[0].data.num;
	for (i = 1; i < count + 1; i++)
	{
		switch (str[i].type)
		{
			case integer:
				printf ("%d", str[i].data.num);
				break;
			case character:
				printf ("%c", str[i].data.c);
				break;
		}
		if ((i % (16 * 3)) == 0)
			printf ("\n");
	}
	if (count == 0)
		printf ("The set is empty.");
	printf ("\n");
}


/* 
 * Validates the parameters for the union, intersect, sub, and symdiff set operations.
 * Ensures the parameters are valid sets and there are no extraneous parameters.
 * Parameters:
 * - parameters: Array of strings representing the command parameters.
 * - parameters_length: Length of the parameters array.
 * - sets_array: Array of set pointers.
 * Returns: 1 if there is an error in the parameters, otherwise 0.
 */

int check_parameters_union_intersect_sub_symdiff_set (char **parameters, int parameters_length, set **sets_array)
{
	int i, j;
	int not_sets_count = 0;
	/* Ensure there are no more than three parameters.*/
	if (parameters_length > 3)
	{
		printf ("Extraneous text after end of command\n");
		return 1;
	}
	/* Verify if each parameter is a valid set.*/
	for (i=0; i<3; i++)
	{
		for (j=0; j<6; j++)
		{
			if (string_to_set (parameters[i], sets_array) != sets_array[j])
				not_sets_count ++;
		}
		if (not_sets_count == 6)
		{
			printf ("Enter valid set please\n");
			return 1;
		}
		not_sets_count = 0;
	}
	return 0;
}


/* 
 * Validates the parameters for the stop command.
 * Ensures there are no extraneous parameters.
 * Parameters:
 * - parameters_length: Length of the parameters array.
 * Returns: 1 if there are extraneous parameters, otherwise 0.
 */

int check_parameters_stop (int parameters_length)
{
	if (parameters_length > 0)
	{
		printf ("Extraneous text after end of command\n");
		return 1;
	}
	return 0;
}

