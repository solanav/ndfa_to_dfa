#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"

// Function that given a state and a symbol returns a list of the states where it goes

int get_transitions(AFND *afnd, int **t_list, int state, int symbol_i)
{
	int transitions = 0; // Count the number of transitions
	int num_states = AFNDNumEstados(afnd);
	int num_symbols = AFNDNumSimbolos(afnd);

	// Get memory for the max number of transitions we can have
	*t_list = calloc(num_symbols, sizeof(int));

	for (int i = 0; i < num_states; i++)
	{
		if (AFNDTransicionIndicesEstadoiSimboloEstadof(
				afnd, state, symbol_i, i) == 1)
		{
			(*t_list)[transitions] = i;

			transitions++;
			printf("Found > from %d through %s to %d\n",
				   state, AFNDSimboloEn(afnd, symbol_i),
				   i);
		}
	}

	// Realloc to get only the space we need
	*t_list = realloc(*t_list, transitions * sizeof(int));

	printf("Finished (total: %d)\n", transitions);

	return transitions;
}

// Calls the previous x times to look at the array of states instead of 1
int get_transitions_x(AFND *afnd, int **t_list, const int *states, int num_states, int symbol_i)
{
	int transitions = 0; // Total number of transitions
	int num_symbols = AFNDNumSimbolos(afnd);

	// Get memory for the max number of transitions we can have
	printf("Total space > %ld bytes\n", num_symbols * num_states * sizeof(int));
	*t_list = calloc(num_symbols * num_states, sizeof(int));
	memset(*t_list, -1, num_symbols * num_states * sizeof(int));

	// For each state, get the transition list
	for (int i = 0; i < num_states; i++)
	{
		int *tmp_t_list;
		int num_transitions =
			get_transitions(afnd, &tmp_t_list, states[i], symbol_i);

		// Copy new transitions
		for (int j = 0; j < num_transitions; j++)
		{
			// Check we are not repeating
			int repeated = 0;
			for (int k = 0; k < num_symbols * num_symbols && repeated == 0; k++)
				repeated = tmp_t_list[j] == (*t_list)[k] ? 1 : 0;

			// If not repeated: insert, else don't
			if (repeated == 0)
				(*t_list)[transitions + j] = tmp_t_list[j];
			else
				num_transitions--;
		}
		free(tmp_t_list);

		transitions += num_transitions;
	}

	*t_list = realloc(*t_list, transitions * sizeof(int));

	return transitions;
}

char *gen_name(AFND *afnd, int *states, int num_states)
{
	char *name = calloc(num_states * 3, sizeof(char));

	for (int i = 0; i < num_states; i++)
	{

			// Insert the name
			char tmp[4];
			sprintf(tmp, "q%c-", states[i] + 48);
			strncat(name, tmp, 3);
	}

	// Remove last dash
	name[num_states * 3 - 1] = '\0';

	return name;
}