#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"

// Function that given a state and a symbol returns a list of the states where it goes

int get_transitions(AFND *afnd, int ** list)
{
    int transitions = 0; 

    int num_states = AFNDNumEstados(afnd);
    int num_simbolos = AFNDNumSimbolos(afnd);
   int i, j, k;

    for( i=0; i<num_states; i++){
        
        for (j=0; j<num_simbolos; j++){
            
            for (k=0; k<num_states; k++){
                
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, j, k) == 1){
                    list[i][j] = k;
                    transitions++; 
                  
                }  
                else {
                    if((AFNDCierreLTransicionIJ(afnd,i, k) == 1) && (i!=k)){
                      list[i][j] = 0;
               }
                } 
            }
        }
       
    }

    
    return transitions;
}



/*

void imprime_funcion_transicion(FILE *fd, AFND *p_afnd){
    int i, j, k;

    if (p_afnd==NULL){
        return;
    }

    for (i=0; i<p_afnd->num_estados; i++){
        for (j=0; j<p_afnd->num_simbolos; j++){
            for (k=0; k<p_afnd->num_estados; k++){
                if (VectorIndicesGetI(p_afnd->funcion_transicion[i][j], k)==1){
                    fprintf (fd, "\n        f(%s,%d)={%s}", get_nombre(p_afnd->estados[i]),  j, get_nombre(p_afnd->estados[k]));
                }
            }   
        }       
    }
    fprintf(fd, "\n");

    return;

}*/
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

