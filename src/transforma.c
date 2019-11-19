#include <stdlib.h>
#include <string.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"
#include "../include/transforma.h"
#include "../include/types.h"

typedef struct _state
{
    char *name;     // Name of the state
    int type;       // Type of the state
    int *i_list;    // Index of the states contained in the original afnd
    int i_n;        // Size of i_list
} state;

#ifdef DEBUG
void print_state(const state *s)
{
    char type_str[16] = {0};

    if (s->type == 0)
        strcpy(type_str, "inicial");
    else if (s->type == 1)
        strcpy(type_str, "final");
    else if (s->type == 2)
        strcpy(type_str, "inicial y final");
    else if (s->type == 3)
        strcpy(type_str, "normal");
    else
        strcpy(type_str, "      ");
    
    if (s->name != NULL)
    {
        printf(P_INFO "\"%8s\", %7s, [", s->name, type_str);

        for (int i = 0; i < s->i_n; i++)
            printf("%d, ", s->i_list[i]);
        printf("]\n");
    }
    else
        printf(P_INFO "          , %7s, [ ]\n", type_str);
}
#endif

#define save_state(afnd, sl, i, il, iln) {\
    sl[i].name = gen_name(afnd, il, iln);\
    sl[i].type = gen_type(afnd, il, iln);\
    sl[i].i_list = calloc(iln, sizeof(int));\
    memcpy(sl[i].i_list, il, iln * sizeof(int));\
    sl[i].i_n = iln;\
}

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
    int states[] = {0, 2, 4};
    int *lstates = NULL;
    int lstates_n = add_lambdas(afnd, &lstates, states, 3);
    
    for (int i = 0; i < lstates_n; i++)
        printf("%d\n", lstates[i]);
    
    exit(0);

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
    save_state(afnd, f_states, f_states_n, initial_list, initial_list_n);
#ifdef DEBUG
    print_state(&f_states[f_states_n]);
    printf("\n");
#endif
    f_states_n++;

    // Main loop
    for (int current_state = 0; current_state < f_states_n; current_state++)
    {
        // Get all transitions and insert if new
        for (int i = 0; i < AFNDNumSimbolos(afnd); i++)
        {
            // Get transition data
            int *t_list = NULL;
            int t_list_n = get_transitions_x(
                afnd,
                &t_list,
                f_states[current_state].i_list,
                f_states[current_state].i_n,
                i
            );

            if (t_list_n == 0)
            {
                f_transitions = realloc(f_transitions, (f_transitions_n + 1) * sizeof(state));
                f_transitions[f_transitions_n].type = -1;
                f_transitions_n++;
                continue;
            }

            char *transition_name = gen_name(afnd, t_list, t_list_n);

            // Insert into the transition array
            f_transitions = realloc(f_transitions, (f_transitions_n + 1) * sizeof(state));
            save_state(afnd, f_transitions, f_transitions_n, t_list, t_list_n);
            f_transitions_n++;
#ifdef DEBUG
            printf(P_INFO "Inserted transition (%s):\n", AFNDSimboloEn(afnd, i));
            print_state(&f_transitions[f_transitions_n-1]);
            printf("\n");
#endif

            // Insert into the states array
            if (contains(f_states, f_states_n, transition_name) == false)
            {
                f_states = realloc(f_states, (f_states_n + 1) * sizeof(state));
                save_state(afnd, f_states, f_states_n, t_list, t_list_n);
                f_states_n++;
            }

            free(t_list);
            free(transition_name);
        }
    }

    // Print what we got
#ifdef DEBUG
    printf("\n"P_INFO"All the states:\n");
    for (int i = 0; i < f_states_n; i++)
    {
        printf("\t");
        print_state(&f_states[i]);
    }

    printf("\n"P_INFO"All the transitions:\n");
    for (int i = 0; i < f_transitions_n; i++)
    {
        printf("\t");
        print_state(&f_transitions[i]);
    }
    printf("\n");
#endif

    // Free everything
    for (int i = 0; i < f_states_n; i++)
    {
        if (f_states[i].type != -1)
        {
            free(f_states[i].name);
            free(f_states[i].i_list);
        }
    }
    free(f_states);

    for (int i = 0; i < f_transitions_n; i++)
    {   
        if (f_transitions[i].type != -1)
        {
            free(f_transitions[i].name);
            free(f_transitions[i].i_list);
        }
    }
    free(f_transitions);

    return NULL;
}
