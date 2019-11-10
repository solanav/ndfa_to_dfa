#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>
#include "../include/types.h"

typedef struct _table table;

#define MAX_NAME 16

/**
 * Creates a table of size num_simbols
 *
 * simbols: list of the indexes of the simbols
 * num_simbols: total number of simbols in the automata
 * 
 * Return: the table or NULL on error
 */
table *create_table(int *simbols, int num_simbols);
void free_table(table *t);

/**
 * Adds a new state to the table
 * 
 * Uses realloc to add space to the main array
 * 
 * state: char to identify the new state
 * 
 * Return: OK or ERROR
 */
int add_state(table *t, char *s);

/**
 * Gets the next state if you follow the transition
 * 
 * state: the state you want to get the transition to
 * simbol: the simbol to check
 * 
 * Return: char* with the name of the next state or NULL on error
 */
char *get_transition(table *t, char *s, int simbol);

/**
 * Checks if the state already exists in the table
 * 
 * state: name of the state to check
 * 
 * Return: true or false
 */
bool check_if_created(table *t, char *s);

#endif