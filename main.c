#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/afnd.h"
#include "../include/afnd_plus.h"
#include "../include/transforma.h"
#include "../include/lambda_parser.h"
#include "../include/types.h"

int main(int argc, char **argv)
{

	AFND *p_afnd;
	//AFND *afd;
	

	p_afnd = AFNDNuevo("af11", 6, 3);

	AFNDInsertaSimbolo(p_afnd, "+");
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, ".");

	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
	AFNDInsertaTransicion(p_afnd, "q3", "0", "q3");
	AFNDInsertaTransicion(p_afnd, "q4", ".", "q3");

	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q3", "q5");
	AFNDCierraLTransicion(p_afnd);

	AFNDImprime(stdout, p_afnd);

	int i, j;
	int num_states = AFNDNumEstados(p_afnd);
	int num_simbols = AFNDNumSimbolos(p_afnd);
 	

 	int **list = (int**) malloc(num_states * sizeof(int*));
 	for(i = 0; i < num_states; i++){
  		list[i] = (int*)malloc(num_simbols * sizeof(int));
 	}
 	int t = get_transitions(p_afnd,list);
    printf("Transiciones totales:%d\n",t );
    for(i=0; i<num_states; i++){
		for (j=0; j< num_simbols; j++){
			printf("|%d|",list[i][j] );
		}
		printf("\n");
	}


	
	/*afd = AFNDTransforma(p_afnd);
	if (afd == NULL)
	{
		printf(P_ERROR"AFNDTransforma returned NULL\n");
		return ERROR;
	}
	AFNDADot(afd);
	AFNDElimina(afd);*/

	
	// Id of the states
	/*int iIni = AFNDIndiceDeEstado(p_afnd, "q3");
	
 	int num_states = AFNDNumEstados(p_afnd);
	int *list = get_transitions(p_afnd, iIni, 1);
	printf("El estado %d\n", iIni);
	
	}*/
	/*-----------------------------------------------------------------*/

	AFNDElimina(p_afnd);

	return OK;
}
