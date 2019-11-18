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

    // Get initial state
    int *initial_list = NULL;
    int initial_list_n = get_states_connected(afnd, &initial_list, AFNDIndiceEstadoInicial(afnd));

#ifdef DEBUG
    printf(P_INFO "Initial state list: [");
    for (int i = 0; i < initial_list_n; i++)
        printf("%d, ", initial_list[i]);
    printf("]\n");
#endif

    // Insert the initial state to have something inside the list
    char *initial_name = gen_name(afnd, initial_list, initial_list_n);
    f_states[f_states_n].name = calloc(strlen(initial_name) + 1, sizeof(char));
    f_states[f_states_n].type = get_type(afnd, initial_list, initial_list_n);
    f_states_n++;
#ifdef DEBUG
    printf(P_INFO "Initial state is called \"%s\" and has type %d\n", initial_name, get_type(afnd, initial_list, initial_list_n));
#endif
    free(initial_name);

    // Main loop
    int *state_list = initial_list;
    int state_list_n = initial_list_n;
    for (int current_state = 0; current_state < f_states_n; current_state++)
    {
        char *state_name = gen_name(afnd, state_list, state_list_n);
#ifdef DEBUG
        printf(P_INFO "Checking transitions of %s\n", state_name);
#endif

        // Get all transitions and insert if new
        for (int i = 0; i < AFNDNumSimbolos(afnd); i++)
        {
            // Get transitions of the state
            int *t_list = NULL;
            int t_list_n = get_transitions_x(afnd, &t_list, state_list, state_list_n, i);
            char *transition_name = gen_name(afnd, t_list, t_list_n);

            // If we don't know this state, insert it
            if (contains(f_states, f_states_n, transition_name) == false)
            {
                // Insert into our list of states
                f_states[f_states_n].name = calloc(strlen(transition_name) + 1, sizeof(char));
                strcpy(f_states[f_states_n].name, transition_name);
                f_states[f_states_n].type = get_type(afnd, t_list, t_list_n);

                // Get more space for transitions
                f_states = realloc(f_states, (f_states_n + 1) * sizeof(state));
                
                f_states_n++;
            }

#ifdef DEBUG
            printf(P_INFO "Transition to \"%s\" with \"%s\": [", transition_name, AFNDSimboloEn(afnd, i));
            for (int j = 0; j < t_list_n; j++)
                printf("%d, ", t_list[j]);
            printf("]\n");
            printf(P_INFO "New state found \"%s\"\n", transition_name);
#endif
            free(t_list);
            free(transition_name);
        }

#ifdef DEBUG
        for (int i = 0; i < f_states_n; i++)
            printf(P_INFO "[%10s][%d]\n", f_states[i].name, f_states[i].type);
#endif
        // Free the current state list
        free(state_list);
        free(state_name);
        break;
    }

    // Free everything
    for (int i = 0; i < f_states_n; i++)
        free(f_states[i].name);
    free(f_states);
    for (int i = 0; i < f_transitions_n; i++)
        free(f_transitions[i].name);
    free(f_transitions);

    return NULL;
}
