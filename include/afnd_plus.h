#ifndef AFND_PLUS_H
#define AFND_PLUS_H

#include <stdbool.h>
#include "../include/afnd.h"

typedef struct _transition {
    int symbol; // Indice del simbolo con el que nos moviemos
    int destiny; // A donde nos movemos
} transition;

void display(int *ageArray, AFND *afnd);

/**
 * Generate a list of transitions for a state
 * 
 * afnd: afnd to get the transitions from
 * transitions: list to the transitions (memory is allocated inside)
 * num_states: total number of states of the automata
 * state_index: index of the state you want the transitions from
 * 
 * Returns the number of transitions in the given state
 */
int get_transitions(AFND *afnd, transition **t_list, int state);

/**
 * Generate a list of transitions for several states
 * 
 * afnd: afnd to get the transitions from
 * transitions: list to the transitions (memory is allocated inside)
 * num_states: total number of states of the automata
 * state_index: index of the state you want the transitions from
 * 
 * Returns the number of transitions in the given state
 */

int get_transitions_x(AFND *afnd, transition **t_list, int *states, int num_states);

/**
 * Compress the list of transitions
 * 
 * Transforms a list of transitions of non-deterministic automata
 * into a deterministic one by compressing transitions that use the
 * same symbol
 * 
 * afnd: the afnd who's transitions we want compressed
 * t_list: list of transitions
 * nt: number of transitions in the list
 * 
 * Returns the new list of transitions
 */
transition *compress_transitions(AFND *afnd, transition *t_list, int nt);

/**
 * Generate a name for a new state
 * 
 * states: list of states to generate the name from
 * num_states: number of states in the list
 * 
 * Returns a string containing the new name
 */
char *gen_name(AFND *afnd, int *states, int num_states);

/**
 * Create the AD by extracting the data from the matrix
 * 
 * name: automata name
 * matrix: the data is taken from there
 * 
 * Returns the new AD
 */
AFND *AFD(char *name, int **matrix);

void imprime_funcion_transicion(FILE *fd, AFND *p_afnd);

#endif