#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"

// Function that given a state and a symbol returns a list of the states where it goes


int get_transitions(AFND *afnd, int *vector, int state){
    int i, j, transitions=0;

    int num_states = AFNDNumEstados(afnd);
    int num_symbols = AFNDNumSimbolos(afnd);
    for(i = 0; i < num_states; i++){
        for(j = 0; j < num_symbols; j++){
            if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, state, j, i) == 1){
                vector[i] = i;
                transitions++;
                printf("%d\n",vector[i]);   
            }

        }  
    }
   
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

