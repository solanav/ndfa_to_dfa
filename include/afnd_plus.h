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

#endif