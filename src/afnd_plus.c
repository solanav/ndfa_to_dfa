#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"

int get_transitions(AFND *afnd, int **transitions, int state_index)
{
    int num_states = AFNDNumEstados(afnd);

    // Get enough memory for all possible transitions
    *transitions = calloc(num_states, sizeof(int));

    int total_transitions = 0;
    int transition_i = 0;
    for (int i = 0; i < num_states; i++)
    {
        if (AFNDLTransicionIJ(afnd, state_index, i) == 1)
        {
            // Save the transition index (where you are going)
            (*transitions)[transition_i] = i;
            
            transition_i++;
            total_transitions++;
        }
    }

    // Reduce the transition list to only what we need
    *transitions = realloc(*transitions, sizeof(int) * total_transitions);

    return total_transitions;
}


bool contains_lambda(AFND *afnd, int state_index)
{
    return false;
}


int * actualStates(AFND *afnd)
{
    AFNDIndiceEstadoInicial(afnd);
    return NULL;
}

bool matrix()
{
    int rows, columns;
    for (i = 0; i < rows; i++){
      for (j = 0; j < columns; j++){

      }
    }
    return NULL;
}


