#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/afnd.h"
#include "../include/lambda_parser.h"
#include "../include/types.h"

int get_transitions(AFND *afnd, int *transitions, int num_states, int state_index)
{
    int tmp_transitions[num_states];
    int num_transitions = 0;

    int pos = 0;
    for (int i = 0; i < num_states; i++)
    {
	if (AFNDLTransicionIJ(afnd, state_index, i) == 1)
	{
	    // Save the transition index (where you are going)
	    tmp_transitions[pos] = i;
	    
	    pos++;
	    num_transitions++;
	}
    }
    
    transitions = calloc(num_transitions, sizeof(int));
    memcpy(transitions, tmp_transitions, sizeof(transitions));

    return num_transitions;
}

int lambda_parse_afnd(AFND *afnd, AFND *afd)
{
    int num_states = AFNDNumEstados(afnd);
    int num_simbols = AFNDNumSimbolos(afnd);
    
    int *transition_list;
    int num_transitions = get_transitions(afnd, transition_list, num_states, 0);
    
    for (int i = 0; i < num_transitions; i++)
	printf("Transition to %d\n", transition_list[i]);

    free(transition_list);

    return ERROR;
}

