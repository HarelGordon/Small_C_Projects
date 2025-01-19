#include "set.h"
#include <stdlib.h>

/*
 * Function: read_set
 * ------------------
 * Reads a set from the given parameters and stores the values in the specified set.
 * 
 * parameters: Array of strings representing the set name and the values to be added.
 * parameters_length: Length of the parameters array.
 * sets_array: Array of pointers to sets.
 */

void read_set (char ** parameters, int parameters_length, set **sets_array)
{
	int i, num;
	set *p_temp = string_to_set (parameters[0], sets_array);
	/* Initialize the set to zero */
	for (i=0; i<16; i++)
		p_temp->array[i] = 0;
	/* Convert each parameter to an integer and set the corresponding bit in the set */
	for (i = 1; i < parameters_length; i++)
	{
		num = atoi(parameters[i]);
		p_temp->array[num / 8] |= (1 << (num % 8));
	}
}


/*
 * Function: print_set
 * -------------------
 * Prints the values of the given set.
 * 
 * s: Pointer to the set to be printed.
 * 
 * Returns: A pointer to an array of Data structures containing the set elements.
 */

Data *print_set (set *s)
{
	int i, j;
	int count = 0;
	static Data str[218 * 3]; /*218 numbers, 218 spaces, 218 commas - MAX*/
	/* Iterate through the set and add each element to the output array */
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (s->array[i] & (1 << j))
			{
				count++;
				str[count].type = integer;
				str[count].data.num = (i * 8) + j;
				count++;
				str[count].type = character;
				str[count].data.c = ',';
				count++;
				str[count].type = character;
				str[count].data.c = ' ';
			}
		}
	}
	/* Remove the last comma and space */
	if (count != 0)
		count -= 2;
	str[0].type = integer;
	str[0].data.num = count;
	return str;
}


/*
 * Function: union_set
 * -------------------
 * Computes the union of two sets and stores the result in a third set.
 * 
 * sets_array: Array of pointers to sets.
 * parameters: Array of strings representing the names of the sets to be unioned and the result set.
 */

void union_set (set **sets_array, char ** parameters)
{
	int i;
	set *p_a, *p_b, *p_c;
	set s_temp;
	/* Convert parameter strings to set pointers */
	p_a = string_to_set (parameters[0], sets_array);
	p_b = string_to_set (parameters[1], sets_array);
	p_c = string_to_set (parameters[2], sets_array);
	/* Compute the union of the sets */
	for (i=0; i<16; i++)
	{
		s_temp.array[i] = p_a->array[i];
		s_temp.array[i] |= p_b->array[i];
		p_c->array[i] = s_temp.array[i];
	}
}

/*
 * Function: intersect_set
 * -----------------------
 * Computes the intersection of two sets and stores the result in a third set.
 * 
 * sets_array: Array of pointers to sets.
 * parameters: Array of strings representing the names of the sets to be intersected and the result set.
 */

void intersect_set (set **sets_array, char ** parameters)
{
	int i;
	set *p_a, *p_b, *p_c;
	set s_temp;
	/* Convert parameter strings to set pointers */
	p_a = string_to_set (parameters[0], sets_array);
	p_b = string_to_set (parameters[1], sets_array);
	p_c = string_to_set (parameters[2], sets_array);
	/* Compute the intersection of the sets */
	for (i=0; i<16; i++)
	{
		s_temp.array[i] = 0 | (p_a->array[i]);
		s_temp.array[i] &= p_b->array[i];
		p_c->array[i] = s_temp.array[i];
	}
}


/*
 * Function: sub_set
 * -----------------
 * Computes the difference of two sets and stores the result in a third set.
 * 
 * sets_array: Array of pointers to sets.
 * parameters: Array of strings representing the names of the sets to be subtracted and the result set.
 */

void sub_set (set **sets_array, char ** parameters)
{
	int i;
	set *p_a, *p_b, *p_c;
	set s_temp;
	/* Convert parameter strings to set pointers */
	p_a = string_to_set (parameters[0], sets_array);
	p_b = string_to_set (parameters[1], sets_array);
	p_c = string_to_set (parameters[2], sets_array);
	/* Compute the difference of the sets */
	for (i=0; i<16; i++)
	{
		s_temp.array[i] = 0 | (p_a->array[i]);
		s_temp.array[i] &= p_b->array[i];
		s_temp.array[i] ^= p_a->array[i];
		p_c->array[i] = s_temp.array[i];
	}
}

/*
 * Function: symdiff_set
 * ---------------------
 * Computes the symmetric difference of two sets and stores the result in a third set.
 * 
 * sets_array: Array of pointers to sets.
 * parameters: Array of strings representing the names of the sets for symmetric difference and the result set.
 */

void symdiff_set (set **sets_array, char ** parameters)
{
	int i;
	set *p_a, *p_b, *p_c;
	set s_temp;
	/* Convert parameter strings to set pointers */
	p_a = string_to_set (parameters[0], sets_array);
	p_b = string_to_set (parameters[1], sets_array);
	p_c = string_to_set (parameters[2], sets_array);
	/* Compute the symmetric difference of the sets */
	for (i=0; i<16; i++)
	{
		s_temp.array[i] = 0 | (p_a->array[i]);
		s_temp.array[i] ^= p_b->array[i];
		p_c->array[i] = s_temp.array[i];
		
	}	
}

