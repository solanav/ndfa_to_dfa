#include <stdlib.h>
#include <string.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"
#include "../include/transforma.h"
#include "../include/types.h"

typedef struct _state
{
    char *name;
    int type;
} state;

bool contains(state *transitions, int transitions_n, char *state_name)
{
    for (int i = 0; i < transitions_n; i++)
    {
        if (strcmp(transitions[i].name, state_name) == 0)
            return true;
    }

    return false;
}

AFND *AFNDTransforma(AFND *afnd)
{
    // Temporal list of states of final automata
    int f_states_n = 0;
    int f_transitions_n = 0;
    state *f_states = calloc(1, sizeof(state));
    state *f_transitions = calloc(1, sizeof(state));

    // Get initial state and insert it
    int *initial_list = NULL;
    int initial_list_n = get_states_connected(
        afnd,
        &initial_list,
        AFNDIndiceEstadoInicial(afnd));
#ifdef DEBUG
    printf(P_INFO "Initial state list: [");
    for (int i = 0; i < initial_list_n; i++)
        printf("%d, ", initial_list[i]);
    printf("]\n");
#endif

    // Create name for the initial state
    char *name = gen_name(afnd, initial_list, initial_list_n);
#ifdef DEBUG
    printf(P_INFO "Initial state is called: %s\n", name);
#endif

    // Get transitions from initial state
    for (int i = 0; i < AFNDNumSimbolos(afnd); i++)
    {
        int *t_list = NULL;
        int t_list_n = get_transitions_x(afnd, &t_list, initial_list, initial_list_n, i);
        char *tmp_name = gen_name(afnd, t_list, t_list_n);

        // Check if state already exists
        if (contains(f_transitions, f_transitions_n, tmp_name) == false)
        {
            // Insert into our list of states
            f_transitions[f_transitions_n].name = calloc(strlen(tmp_name) + 1, sizeof(char));
            strcpy(f_transitions[f_transitions_n].name, tmp_name);
            f_transitions[f_transitions_n].type = -1;
            f_transitions_n++;

            // Get more space for transitions
            f_transitions = realloc(f_transitions, (f_transitions_n + 1) * sizeof(state));
        }

#ifdef DEBUG
        printf(P_INFO "Transitions of \"%s\" with \"%s\": [", name, AFNDSimboloEn(afnd, i));
        for (int j = 0; j < t_list_n; j++)
            printf("%d, ", t_list[j]);
        printf("]\n");
        printf(P_INFO "New state found \"%s\"\n", tmp_name);
#endif
        free(t_list);
        free(tmp_name);
    }

#ifdef DEBUG
    for (int i = 0; i < f_transitions_n; i++)
        printf(P_INFO"[%10s][%d]\n", f_transitions[i].name, f_transitions[i].type);
#endif

    // Free everything
    free(initial_list);
    free(f_states);
    for (int i = 0; i < f_transitions_n; i++)
        free(f_transitions[i].name);
    free(f_transitions);
    free(name);

    return NULL;
}
