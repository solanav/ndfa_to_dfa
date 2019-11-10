#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"

// Function that given a state and a symbol returns a list of the states where it goes

int get_transitions(AFND *afnd, transition **t_list, int state)
{
	int transitions = 0;
	int num_states = AFNDNumEstados(afnd);
	int num_symbols = AFNDNumSimbolos(afnd);

	// Get memory for the max number of transitions we can have
	*t_list = calloc(num_symbols, sizeof(transition));

	for (int next_state = 0; next_state < num_states; next_state++) {
		for (int symbol = 0; symbol < num_symbols; symbol++) {
			if (AFNDTransicionIndicesEstadoiSimboloEstadof(
				    afnd, state, symbol, next_state) == 1) {
				(*t_list)[transitions].destiny = next_state;
				(*t_list)[transitions].symbol = symbol;

				transitions++;

				printf("Found > from %d through %s to %d\n",
				       state, AFNDSimboloEn(afnd, symbol),
				       next_state);
			}
		}
	}

	// Realloc to get only the space we need
	*t_list = realloc(*t_list, transitions * sizeof(transition));

	printf("Finished\n");

	return transitions;
}

// Calls the previous x times to look at the array of states instead of 1
int get_transitions_x(AFND *afnd, transition **t_list, int *states, int num_states)
{
	int transitions = 0; // Total number of transitions
	int num_symbols = AFNDNumSimbolos(afnd);

	// Get memory for the max number of transitions we can have
    printf("Total space > %ld bytes\n", num_symbols * num_states * sizeof(transition));
	*t_list = calloc(num_symbols * num_states, sizeof(transition));

	// For each state, get the transition list
	for (int i = 0; i < num_states; i++) {
		transition *tmp_t_list;
		int num_transitions =
			get_transitions(afnd, &tmp_t_list, states[i]);

        printf("Copying %ld bytes\n", num_transitions * sizeof(transition));

        for (int j = 0; j < num_transitions; j++)
            (*t_list)[transitions + j] = tmp_t_list[j];

        free(tmp_t_list);

		transitions += num_transitions;
	}

    *t_list = realloc(*t_list, transitions * sizeof(transition));

	return transitions;
}
