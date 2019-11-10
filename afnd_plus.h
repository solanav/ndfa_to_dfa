#ifndef AFND_PLUS_H
#define AFND_PLUS_H

#include <stdbool.h>
#include "../include/afnd.h"

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
int get_transitions(AFND *afnd, int **list);

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

int* get_transitions_for_x_states(AFND *afnd, int * states, int symbol);

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