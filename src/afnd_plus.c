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

// Convert a list of non-determinictic to deterministic
transition *compress_transitions(AFND *afnd, transition *t_list, int nt)
{
	//nt is the number of transitions that is equal to the size of the list
	int transitions=0;
	int num_symbols = AFNDNumSimbolos(afnd);
	transition *t_new_list = calloc(num_symbols, sizeof(transition));

	for(int i = 0; i < nt; i++)
	{	// qi (Initial state)
		(*t_new_list)[i].destiny = (*t_list)[i].destiny; 
		(*t_new_list)[i].symbol = (*t_list)[i].symbol; 

		for(int j = 0; j < nt; j++)
		{	// qj (Next states with we will compare qi)
			(*t_new_list)[j].destiny = (*t_list)[j].destiny; 
			(*t_new_list)[j].symbol = (*t_list)[j].symbol; 
			//Lambda transitions


			//Search for what transitions have qi different from qi,
			// or qi different from the elements that are in the new list
			if( (*t_list)[i].destiny != *t_list){

			}

			if((*t_new_list)[j].destiny != (*t_list)[i].destiny){

			}

		}
	}
    return 0;
}

char *gen_name(AFND *afnd, int *states, int num_states)
{
    char *name = calloc(num_states * 3, sizeof(char));

    for (int i = 0; i < num_states; i++)
    {
        char tmp[4];
        sprintf(tmp, "q%c-", states[i] + 48);
        strncat(name, tmp, 3);
    }

    // Remove last dash
    name[num_states * 3 - 1] = '\0';

    return name;
}