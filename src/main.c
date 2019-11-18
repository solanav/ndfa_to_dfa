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

	p_afnd = AFNDNuevo("af11", 6, 3);

    // SIMBOLOS
	AFNDInsertaSimbolo(p_afnd, "+");
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, ".");

    // ESTADOS
	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);

    // Q0
	AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");

    // Q1
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");

    // Q2
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");

    // Q3
	AFNDInsertaTransicion(p_afnd, "q3", "0", "q3");

    // Q4
	AFNDInsertaTransicion(p_afnd, "q4", ".", "q3");

    // LAMBDAS
    AFNDInsertaLTransicion(p_afnd, "q0", "q1");
    AFNDInsertaLTransicion(p_afnd, "q3", "q5");
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