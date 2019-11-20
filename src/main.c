#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/afnd.h"
#include "../include/transforma.h"
#include "../include/types.h"

void AFND1()
{
	AFND *p_afnd;
	AFND *afd;
	p_afnd = AFNDNuevo("af1", 6, 3);

	// SIMBOLOS
	AFNDInsertaSimbolo(p_afnd, "+,-");
	AFNDInsertaSimbolo(p_afnd, "0,1,...,9");
	AFNDInsertaSimbolo(p_afnd, ".");

	// ESTADOS
	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);

	// Q0
	AFNDInsertaTransicion(p_afnd, "q0", "+,-", "q1");

	// Q1
	AFNDInsertaTransicion(p_afnd, "q1", "0,1,...,9", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "0,1,...,9", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");

	// Q2
	AFNDInsertaTransicion(p_afnd, "q2", "0,1,...,9", "q3");

	// Q3
	AFNDInsertaTransicion(p_afnd, "q3", "0,1,...,9", "q3");

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
		printf(P_ERROR "AFNDTransforma returned NULL\n");
		AFNDElimina(p_afnd);
		return;
	}
	AFNDADot(afd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);
}

void AFND2()
{

	AFND *p_afnd;
	AFND *afd;
	p_afnd = AFNDNuevo("af2", 3, 2);

	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, "1");

	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q0");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q2");

	// There are not lambda transitions in this example
	AFNDCierraLTransicion(p_afnd);

	AFNDImprime(stdout, p_afnd);

	afd = AFNDTransforma(p_afnd);
	if (afd == NULL)
	{
		printf(P_ERROR "AFNDTransforma returned NULL\n");
		return;
	}
	AFNDADot(afd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);
}

void AFND3()
{

	AFND *p_afnd;
	AFND *afd;
	p_afnd = AFNDNuevo("af2", 3, 2);

	// SIMBOLOS
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, "1");

	//ESTADOS
	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", FINAL);

	// Q0
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q0");
	AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "0", "q2");
	// Q1
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q1");
	// Q2
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "1", "q2");

	// LAMBDAS
	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q1", "q2");
	AFNDCierraLTransicion(p_afnd);

	AFNDImprime(stdout, p_afnd);

	afd = AFNDTransforma(p_afnd);
	if (afd == NULL)
	{
		printf(P_ERROR "AFNDTransforma returned NULL\n");
		return;
	}
	AFNDADot(afd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);
}

void AFND4()
{

	AFND *p_afnd;
	AFND *afd;
	p_afnd = AFNDNuevo("af2", 5, 2);

	// SIMBOLOS
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd, "1");

	//ESTADOS
	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", FINAL);

	// Q1
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q3");
	// Q2
	AFNDInsertaTransicion(p_afnd, "q2", "1", "q3");
	// Q3
	AFNDInsertaTransicion(p_afnd, "q3", "1", "q4");

	// LAMBDAS
	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q0", "q2");
	AFNDCierraLTransicion(p_afnd);

	AFNDImprime(stdout, p_afnd);

	afd = AFNDTransforma(p_afnd);
	if (afd == NULL)
	{
		printf(P_ERROR "AFNDTransforma returned NULL\n");
		return;
	}
	AFNDADot(afd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);
}

int main(int argc, char **argv)
{
	// AFND practica
	AFND1();
	// AFND transparencias
	AFND2();
	// https://www.geeksforgeeks.org/program-implement-nfa-epsilon-move-dfa-conversion/
	AFND3();
	// Example 1 -> https://www.javatpoint.com/automata-conversion-from-nfa-with-null-to-dfa
	AFND4();

	return 0;
}