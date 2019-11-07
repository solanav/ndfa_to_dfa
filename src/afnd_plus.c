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
    if(strcmp(AFNDSimboloEn(afnd, state_index), "lambda") == 0)
    {
        return true;
    }
    return false;
}


int get_symbols(AFND *afnd, char **symbols)
{
    int num_symbols = AFNDNumSimbolos(afnd);
    // Get enough memory for all possible transitions
    *symbols = calloc(num_symbols, sizeof(char));

    for(int i = 0; i < num_symbols; i++)
    {
        strcpy((*symbols)[i], AFNDSimboloEn(afnd, i));
    }
    return num_symbols;
}


int get_transitionsLambda(AFND *afnd, int **transitions, int state_index)
{
    int num_states = AFNDNumEstados(afnd);

    // Get enough memory for all possible transitions
    *transitions = calloc(num_states, sizeof(int));

    int total_transitions = 0;
    int transition_i = 0;
    for (int i = 0; i < num_states; i++)
    {
        if (AFNDLTransicionIJ(afnd, state_index, i) == 1  && contains_lambda(afnd, state_index) == true)
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


int actualStates(AFND *afnd, int **transitions)
{
    int now, after;
  
    now = AFNDIndiceEstadoInicial(afnd);
    // For the current state, it tells me the states that I reach with lambda and I store them in another array
    after = get_transitionsLambda(afnd, *transitions, now);
    // Here "transitions" is a String where the current state is stored + the states that are reached with lambda
    (*transitions)[after + 1] = now;
    return now;
}


bool matrix(AFND *afnd, int *states, int * transitions)
{
    int rows, columns, i, j, k=0;
    columns = AFNDNumSimbolos(afnd);
    // Missing number of rows, i initialize to 0 so that no warnings !!
    rows = 0;

    // Initialize matrix
    int **m = NULL;
    m = (int **)malloc(rows*sizeof(int*));
    for( i = 0; i<rows; i++)
    {
        m[i]=(int *)malloc(columns*sizeof(int));
    }
    // Initialize array of symbols
    char *symbols = (char *)malloc(columns * sizeof(char));
    get_symbols(afnd, symbols);
    
    //Insert the symbols
    i=0;
    k=0;
    for (j = 0; j < columns; j++)
    { 
       if( i == 0 && j == 0 )
       {
            m[i][j] = -1;
       }
       m[i][j] = symbols[k];
       k++;
    }
    // Missing complete matrix
    for (i = 0; i < rows; i++)
    {
      for (j = 0; j < columns; j++)
      {

      }
    }
    return false;
}


