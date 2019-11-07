#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"



/*Funcion que dado un stado y un simbolo me devuelve una lista de los estados donde va*/

int get_transitions(AFND *afnd, int **transitions, int state_index, int symbol)
{
    int total_transitions = 0;
    // Initialize list
    int num_states = AFNDNumEstados(afnd);
    // Get enough memory for all possible transitions
    *transitions = calloc(num_states, sizeof(int));

    for(i=0; i<num_states; i++)
    {
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, state_index, symbol, i) == 0){
            printf("No hay transicion entre el estado %d  y  %d\n",state_index, i);
        }
        else if(AFNDCierreLTransicionIJ(AFND *p_afnd, int i, int j) == 0){
            printf("No hay transicion LAMBDA entre el estado %d  y  %d\n",state_index, i);
        }else{
        //Push states at list
         (*transitions)[transition_i] = i;
            transition_i++;
            total_transitions++;


    // Reduce the transition list to only what we need
    *transitions = realloc(*transitions, sizeof(int) * total_transitions);

        }
    }
   
    return total_transitions;

}

/*Funcion que llama a la anterior x veces para mirar el array de estados en vez de 1*/

int get_transitions_for_x_states(AFND *afnd, int **transitions, int * states, int symbol)
{

    for(i=0; i<; i++){
        get_transitions(afnd, int **transitions, i, symbol);
    }
  
}