#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"
#include "../include/lambda_parser.h"
#include "../include/types.h"

int lambda_parse_afnd(AFND *afnd, AFND *afd)
{
    int *transition_list;
    int num_transitions = get_transitions(afnd, &transition_list, 0);
    
    for (int i = 0; i < num_transitions; i++)
	    printf("Transition to %d\n", transition_list[i]);

    free(transition_list);

    return ERROR;
}

