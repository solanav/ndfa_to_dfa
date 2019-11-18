#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/afnd.h"
#include "../include/transforma.h"
#include "../include/types.h"

int main(int argc, char **argv)
{
	AFND *p_afnd;
	AFND *afd;

	p_afnd = AFNDNuevo("af11", 3, 2);

    // SIMBOLOS
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, "1");

    // ESTADOS
	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", FINAL);

    // Q0
	AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q0");

    // Q1
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q2");

    // CIERRE
	AFNDCierraLTransicion(p_afnd);

	AFNDImprime(stdout, p_afnd);

	afd = AFNDTransforma(p_afnd);
	if (afd == NULL)
	{
		printf(P_ERROR"AFNDTransforma returned NULL\n");
		AFNDElimina(p_afnd);
		return ERROR;
	}
	AFNDADot(afd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return OK;
}