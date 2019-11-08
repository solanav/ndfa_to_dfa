#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"



// Function that given a state and a symbol returns a list of the states where it goes

int * get_transitions(AFND *afnd, int state_index, int symbol)
{
    int transition_i = 0; 
    int num_states = AFNDNumEstados(afnd);
    int *list = NULL;
    list = (int*)malloc(sizeof(int)*num_states);
   
    for(int i=0; i<num_states; i++)
    {
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, state_index, symbol, i) == 0)
        {
            list[transition_i] = 0;
            
            if(AFNDCierreLTransicionIJ(afnd, state_index, i) == 1  && state_index != i)
            {
                list[transition_i] = 2; 
            }
            transition_i++;
        }else{
       
            list[transition_i] = 1;
            transition_i++;
        }    
    } 
    return list;
}

// Calls the previous x times to look at the array of states instead of 1

int * get_transitions_for_x_states(AFND *afnd, int * states,  int symbol)
{
    int num_states = AFNDNumEstados(afnd);
    int *listOflist = NULL;
    int i;
    for(i = 0; i < num_states; i++)
    {
       int *list = get_transitions(afnd, states[i], 1);
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
}