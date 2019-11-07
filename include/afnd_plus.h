#ifndef AFND_PLUS_H
#define AFND_PLUS_H

#include <stdbool.h>
#include "../include/afnd.h"

/**
 * Generates a list of transitions
 * 
 * afnd: afnd to get the transitions from
 * transitions: list to the transitions (memory is allocated inside)
 * num_states: total number of states of the automata
 * state_index: index of the state you want the transitions from
 * 
 * Returns the number of transitions in the given state
 */
int get_transitions(AFND *afnd, int **transitions, int state_index);

/**
 * Checks if the given state contains a lambda
 * 
 * afnd: afnd to check
 * state_index: index of the state to check
 * 
 * Returns true if has a lambda and false if not or in case of error
 */
bool contains_lambda(AFND *afnd, int state_index);

/**
 * Generates a list of symbols
 * 
 * afnd: afnd to get the transitions from
 * symbols: list to the symbols (memory is allocated inside)
 * 
 * Returns the total symbols of the automata in a list
 */
int get_symbols(AFND *afnd, char **symbols);

/**
 * Generates a list of accesible transitions with lambda
 * 
 * afnd: afnd to get the transitions from
 * transitions: list to the transitions (memory is allocated inside)
 * num_states: total number of states of the automata
 * state_index: index of the state you want the transitions from
 * 
 * Returns the number of transitions in the given state
 */
int get_transitionsLambda(AFND *afnd, int **transitions, int state_index);

/**
 * Generates a list of accesible states with lambda
 * 
 * afnd: afnd to get the states
 * state_index: index of the initial state 
 * 
 * Returns a list of states that are reached with Lambda
 */
int get_statesLambda(AFND *afnd, int state_index);

/**
 * Generates an array of states (current status + status reached by "lambda")
 * 
 * afnd: afnd to get the transitions from
 * 
 * Returns an array with states
 */
int actualStates(AFND *afnd, int **transitions);

/**
 * Generates a matrix with the states (y) symbols (x) and transitions
 * 
 * afnd: afnd to check
 * state_index: index of the state to check
 * 
 * Returns true if done correctly and false if not
 */
bool matrix(AFND *afnd, int *states, int * transitions);

/**
 * Create the AD by extracting the data from the matrix
 * 
 * name: automata name
 * matrix: the data is taken from there
 * 
 * Returns the new AD
 */
AFND *AFD(char *name, int **matrix);



#endif