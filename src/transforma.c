#include <math.h>
#include <stdlib.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"
#include "../include/transforma.h"
#include "../include/types.h"

// Creates a deterministic automata template based on a non-deterministic one
AFND *clone_tranform(AFND *afnd)
{
    int num_states = AFNDNumEstados(afnd) * 2; // Power set is the max
    int num_simbols = AFNDNumSimbolos(afnd); // Same as before

    AFND *afd = AFNDNuevo("af11_determinista", num_states, num_simbols);

    return afd;
}

AFND *AFNDTransforma(AFND *afnd)
{
    // Create template for deterministic transformation
    AFND *afd = clone_tranform(afnd);

    // Get initial state and insert it
    int initial_s = AFNDIndiceEstadoInicial(afnd);
    char *name = gen_name(afnd, &initial_s, 1);
    AFNDInsertaEstado(afd, name, INICIAL);
    free(name);

    int state_list[] = {0, 2, 1};
    char *test_name = gen_name(afnd, state_list, 3);
    printf("NAME > %s\n", test_name);

    /* Get transitions from initial state
    int *t_list = NULL;
    int nt = get_transitions(afnd, &t_list, initial_s, 0);

    // Get transitions from multiple states
    int states[] = {0, 1, 2};
    int nt = get_transitions_x(afnd, &t_list, states, 3, 1);
    for (int i = 0; i < nt; i++)
        printf("> Found %d\n", t_list[i]);
    */
    // Add transitions of the first state to afd
    //AFNDInsertaTransicion(afnd, initial_s, );

    //free(t_list);
    AFNDElimina(afd);

    return NULL;
}
