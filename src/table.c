#include "../include/table.h"

struct _table
{
    int *simbols;                // List of simbols
    char *states[MAX_NAME];      // List of all states
    char *transitions[MAX_NAME]; // List of all transitions
};

table *create_table(int *simbols, int num_simbols)
{
    table *t = calloc(1, sizeof(table));

    t->simbols = calloc(num_simbols, sizeof(int));
    t->states = calloc(num_simbols, MAX_NAME * sizeof(char));
    t->transitions = calloc(num_simbols, MAX_NAME * sizeof(char));

    return t;
}

void free_table(table *t);
int add_state(table *t, char *s);
char *get_transition(table *t, char *s, int simbol);
bool check_if_created(table *t, char *s);