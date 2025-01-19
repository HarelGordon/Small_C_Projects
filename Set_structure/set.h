
typedef struct set
{
    char array[16];
} set;

typedef enum {integer, character} Types;

typedef struct
{
	Types type;
	union
	{
		int num;
		char c;		
	} data;
} Data;

set *string_to_set(char *, set **);
int check_comma(char *);
int check_parameters_read_set(char **, int, set **);
int check_parameters_print_set (char **, int, set **);
void print_union (Data *);
int check_parameters_union_intersect_sub_symdiff_set (char **, int, set **);
int check_parameters_stop (int parameters_length);

void read_set(char **, int, set **);
Data *print_set (set *);
void union_set(set **, char **);
void intersect_set(set **, char **);
void sub_set(set **, char **);
void symdiff_set(set **, char **);

