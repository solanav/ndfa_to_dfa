#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"
#include "../include/types.h"

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
		}
	}

	// Realloc to get only the space we need
	*t_list = realloc(*t_list, transitions * sizeof(int));

	return transitions;
}

int get_transitions_x(AFND *afnd, int **t_list, const int *states, int num_states, int symbol_i)
{
	int transitions = 0; // Total number of transitions
	int num_symbols = AFNDNumSimbolos(afnd);

	// Get memory for the max number of transitions we can have
	*t_list = calloc(num_symbols * num_states, sizeof(int));
	memset(*t_list, -1, num_symbols * num_states * sizeof(int));

	// For each state, get the transition list
	for (int i = 0; i < num_states; i++)
	{
		int *tmp_t_list;
		int num_transitions = get_transitions(
			afnd,
			&tmp_t_list,
			states[i],
			symbol_i
		);
		
		// If there are lambda transitions
		// num_transitions =+ get_states_connected(afnd, &tmp_t_list, states[i]);


		// For each transition
		for (int j = 0; j < num_transitions; j++)
		{
			// Check we are not repeating
			int repeated = 0;
			for (int k = 0; k < num_symbols * num_states && repeated == 0; k++)
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
	if (num_states == 0)
	{
#ifdef DEBUG
		printf(P_ERROR"Input error [%s]\n", __func__);
#endif
		exit(EXIT_FAILURE);
	}

	char *name = calloc(num_states * 3 + 1, sizeof(char));
	int *sorted_states = calloc(num_states, sizeof(int));

	// Copy states to tmp array
	memcpy(sorted_states, states, num_states * sizeof(int));

	// Sort the states
	for (int i = 0; i < num_states; i++)
	{
		for (int j = 0; j < num_states; j++)
		{
			if (sorted_states[j] > sorted_states[i])
			{
				// Swap both
				int tmp = sorted_states[i];
				sorted_states[i] = sorted_states[j];
				sorted_states[j] = tmp;
				
				break;
			}		
		}	
	}

	// Create the name
	for (int i = 0; i < num_states; i++)
		sprintf(name + i*3, "q%d-", sorted_states[i]);

	// Remove last dash
	name[num_states * 3 - 1] = '\0';

	free(sorted_states);

	return name;
}

int get_states_connected(AFND *afnd, int **states, int state)
{
	int total_states = AFNDNumEstados(afnd);
	*states = calloc(total_states, sizeof(int));

	int num_states = 0;
	for (int i = 0; i < total_states; i++)
	{
		if (AFNDCierreLTransicionIJ(afnd, state, i) == 1)
		{
			(*states)[num_states] = i;
			num_states++;
		}
	}

	*states = realloc(*states, num_states * sizeof(int));

	return num_states;
}

int gen_type(AFND *afnd, int *states, int state_n)
{
	static int initial = 0;
	int type = NORMAL;

	for (int i = 0; i < state_n; i++)
	{
		int tmp_type = AFNDTipoEstadoEn(afnd, states[i]);

		if (tmp_type == INICIAL && initial == 0)
		{
			type = INICIAL;
			initial++;
		}

		else if (tmp_type == FINAL && type == NORMAL)
			type = FINAL;

		else if (tmp_type == FINAL && type == INICIAL)
			return INICIAL_Y_FINAL;
	}

	return type;
}

int add_lambdas(AFND *afnd, int **lstates, const int *states, int states_n)
{
	return 1;
}