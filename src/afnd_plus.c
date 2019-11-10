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

	// Reservamos memoria para las transiciones
	*t_list = calloc(num_symbols, sizeof(transition));

	for (int next_state = 0; next_state < num_states; next_state++) {
		for (int symbol = 0; symbol < num_symbols; symbol++) {
			if (AFNDTransicionIndicesEstadoiSimboloEstadof(
				    afnd, state, symbol, next_state) == 1) {

				(*t_list)[transitions].destiny = next_state;
				(*t_list)[transitions].symbol = symbol;

				transitions++;

				printf("Found > from %d through %s to %d\n",
				       state, AFNDSimboloEn(afnd, symbol), next_state);
			}
		}
	}

    printf("Finished\n");

	return transitions;
}

// Calls the previous x times to look at the array of states instead of 1

/*int * get_transitions_for_x_states(AFND *afnd, int * states,  int symbol)
{
    int num_states = AFNDNumEstados(afnd);
    int *listOflist = NULL;
    int *list = NULL;
    int i;
    for(i = 0; i < num_states; i++)
    {
        * list = get_transitions(afnd, states[i], 1);
        printf("El estado %d\n", i);
        printf("%d\n",list[i] );
        if(list[i] == 1)
        {
            printf("Tiene conexion con el estado q%d mediante ese simbolo\n", i);
        }
        if(list[i] == 2)
        {
            printf("Tiene conexion con el estado q%d mediante LAMBDA\n", i);
        }
        listOflist[i] = list; 
    }
    return listOflist;
}*/
